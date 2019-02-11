#include "mainwindow.h"
#include "Model/qtablemodeladapter.h"
#include "Model/qfilterproxymodel.h"
#include "tableview.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QLineEdit>
#include <QCloseEvent>
#include <QComboBox>
#include <QFileDialog>
#include <QDebug>
#include "insertwidget.h"

MainWindow::MainWindow(QWidget *parent, bool load, int o) : QWidget(parent),
    offset(o),
    fileName(QString()),
    searchbar(new QLineEdit(this)),
    view(new TableView(this))
{
    move(QApplication::desktop()->screen()->rect().center() - rect().center()+QPoint(offset,offset));
    setWindowTitle(tr("No name - My Beauty")); //titolo applicazione
    setWindowIcon(QIcon(":/icon.svg")); // icona del programma
    setFixedSize(QSize(450, 650)); //dimensione fissa non ridimensionabile

    insertWidget* insert = new insertWidget();
    QComboBox* searchAttribute = new QComboBox();
    proxymodel = new QFilterProxyModel(this, searchAttribute);
    model = new QTableModelAdapter(this, insert);
    if(load)
        loadData(); //caricamento modello
    proxymodel->setSourceModel(model);
    view->setModel(proxymodel);     // fornisce alla view il modello dei dati che deve riflettere

    //RICERCA
    searchbar->setPlaceholderText("Ricerca");
    searchAttribute->addItem(QString("Nome"));
    searchAttribute->addItem(QString("Marca"));
    searchAttribute->addItem(QString("Tipo"));
    searchAttribute->addItem(QString("Materiale"));
    searchAttribute->addItem(QString("Colore"));
    searchAttribute->addItem(QString("Odore"));
    searchAttribute->addItem(QString("Parte del corpo"));
    //MENU
    QMenuBar* menuBar = new QMenuBar();
    QMenu* menu = new QMenu("File", menuBar);
    QAction* newAction = new QAction("Nuovo", menu);
    QAction* loadAction = new QAction("Apri", menu);
    QAction* saveAction = new QAction("Salva", menu);
    QAction* saveAsAction = new QAction("Salva con nome", menu);
    QAction* exitAction = new QAction("Esci", menu);
    menuBar->addMenu(menu);
    menu->addAction(newAction);
    menu->addAction(loadAction);
    menu->addAction(saveAction);
    menu->addAction(saveAsAction);
    menu->addAction(exitAction);
    //PULSANTI
    QPushButton* showButton = new QPushButton("Visualizza");
    showButton->setToolTip(tr("See more info about the selected item"));
    QPushButton* useButton = new QPushButton("Usa");
    useButton->setToolTip(tr("Use the selected item"));
    QPushButton* useResultsButton = new QPushButton("Usa sui risultati");
    useResultsButton->setToolTip(tr("Use all the items you see as result from a search. If you didn't search anything, all items in the beauty will be used."));
    QPushButton* removeButton = new QPushButton("Rimuovi");
    removeButton->setToolTip(tr("Remove the selected  item"));
    QPushButton* removeResultsButton = new QPushButton("Rimuovi i risultati");
    removeResultsButton->setToolTip(tr("Remove all the items you see as result from a search. If you didn't search anything, all items in the beauty will be removed."));
    QPushButton* clearSearchButton = new QPushButton("X");
    clearSearchButton->setToolTip(tr("Delete filters"));
    //LAYOUT
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    // Searchbar sottolayout
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchbar);
    searchLayout->addWidget(searchAttribute);
    searchLayout->addWidget(clearSearchButton);
    // Pulsanti sottolayout
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QHBoxLayout* buttonsResultsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(showButton);
    buttonsLayout->addWidget(useButton);
    buttonsLayout->addWidget(removeButton);
    buttonsResultsLayout->addWidget(useResultsButton);
    buttonsResultsLayout->addWidget(removeResultsButton);
    // Setup Main layout
    mainLayout->addWidget(menuBar);
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(view, 0, Qt::AlignCenter);
    mainLayout->addLayout(buttonsLayout, 50); // stretch = 50 per distanziare i bottoni
    mainLayout->addLayout(buttonsResultsLayout, 50); // stretch = 50 per distanziare i bottoni
    mainLayout->addWidget(insert);
    // CONNECT
    connect(newAction, SIGNAL(triggered()), this, SLOT(newBeauty()));
    connect(loadAction, SIGNAL(triggered()), this, SLOT(loadNewBeauty()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveData()));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAsData()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(showButton, SIGNAL(clicked()), this, SLOT(showMore()));
    connect(useButton, SIGNAL(clicked()), this, SLOT(use()));
    connect(useResultsButton, SIGNAL(clicked()), this, SLOT(useResults()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(remove()));
    connect(removeResultsButton, SIGNAL(clicked()), this, SLOT(removeResults()));
    connect(searchbar, SIGNAL(textChanged(const QString&)), this, SLOT(textFilterChanged()));
    connect(searchAttribute, SIGNAL(currentTextChanged(const QString&)), this, SLOT(textFilterChanged()));
    connect(clearSearchButton, SIGNAL(clicked()), searchbar, SLOT(clear()));
    connect(insert, SIGNAL(insertClicked()), this, SLOT(add()));
    textFilterChanged();
    setLayout(mainLayout);
}
QSize MainWindow::sizeHint() const {
    return QSize(500, 600);
}
void MainWindow::saveData() {
    if(!fileName.isEmpty()){
        try {
            model->saveToFile(fileName.toStdString());
        } catch (std::exception) {
            QMessageBox box(QMessageBox::Warning, "Errore di salvataggio", "Non è stato possibile scrivere sul file", QMessageBox::Ok);
            box.exec();
        }
    }
    else saveAsData();
}
void MainWindow::saveAsData() {
    fileName = QFileDialog::getSaveFileName(this,
                                            tr("Save to a file"), "",
                                            tr("XML (*.xml);;All Files (*)"));
    if(!fileName.isEmpty()){
        setWindowTitle(QFileInfo(fileName).fileName() + tr(" - My Beauty"));
        try {
            model->saveToFile(fileName.toStdString());
        } catch (std::exception) {
            QMessageBox box(QMessageBox::Warning, "Errore di salvataggio", "Non è stato possibile scrivere sul file", QMessageBox::Ok);
            box.exec();
        }
    }
}
void MainWindow::loadData() {
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Load from a file"), "",
                                            tr("XML (*.xml);;All Files (*)"));
    if(!fileName.isEmpty()){
        setWindowTitle(QFileInfo(fileName).fileName() + tr(" - My Beauty"));
        model->loadFromFile(fileName.toStdString());
    }
}
void MainWindow::add() const{
    proxymodel->insertRows(proxymodel->rowCount(), 1);
    view->clearSelection();
    view->selectionModel()->clearCurrentIndex();
    view->selectionModel()->select(proxymodel->index(model->rowCount() - 1, 0), QItemSelectionModel::Select);
}
void MainWindow::remove() const{
    // prende l'elenco degli elementi selezionati dalla view
    const QModelIndexList selection = view->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        proxymodel->removeRows(selection.at(0).row(), 1);
}
void MainWindow::use() {
    const QModelIndexList selection = view->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        if(!proxymodel->use(selection.at(0))){
            QMessageBox::StandardButton resBtn = QMessageBox::question( this, tr("My Beauty"),
                                                                        tr("The selected is terminated. Do you want to remove it?\n"),
                                                                        QMessageBox::No | QMessageBox::Yes,
                                                                        QMessageBox::Yes);
            if(resBtn==QMessageBox::Yes)
                remove();
        }
}
void MainWindow::showMore() const{
    const QModelIndexList selection = view->selectionModel()->selectedIndexes();
    if(selection.size() > 0)
        proxymodel->showMore(selection.at(0));
}
void MainWindow::textFilterChanged() const {
    QRegExp regex(searchbar->text(), Qt::CaseInsensitive, QRegExp::Wildcard);
    proxymodel->setFilterRegExp(regex);
}
void MainWindow::newBeauty() const {
    MainWindow* beauty = new MainWindow(nullptr, false, offset+20);
    beauty->setAttribute(Qt::WA_DeleteOnClose); //viene distrutto alla chiusura del nuovo beauty
    beauty->show();
}
void MainWindow::loadNewBeauty() const{
    MainWindow* beauty = new MainWindow(nullptr, true, offset+20);
    beauty->setAttribute(Qt::WA_DeleteOnClose); //viene distrutto alla chiusura del nuovo beauty
    beauty->show();
}
void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, tr("My Beauty"),
                                                                tr("Do you want to save?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if(resBtn==QMessageBox::Cancel)
        event->ignore();
    else {
        if(resBtn==QMessageBox::Yes)
            saveData();
        event->accept();
    }
}
void MainWindow::useResults() const{
    proxymodel->useResults();
}
void MainWindow::removeResults() const{
    proxymodel->removeResults();
}
