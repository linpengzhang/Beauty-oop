#include "insertwidget.h"
#include <QComboBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QLabel>
insertWidget::insertWidget(QWidget *parent) : QWidget(parent),
    tipoLabel(new QLabel("Cosa vuoi inserire?", this)), tipo(new QComboBox(this)),
    marcaLabel(new QLabel("Marca:", this)), nomeLabel(new QLabel("Nome:", this)),
    capacitaLabel(new QLabel("Contenuto totale (ml):",this)), consumoLabel(new QLabel("Consumo di un utilizzo (ml):",this)),
    materialeLabel(new QLabel("Materiale:", this)), contatoreLabel(new QLabel("Quante volte l'hai già usato?",this)),
    coloreLabel(new QLabel("Colore:", this)), odoreLabel(new QLabel("Odore:", this)), parteDelCorpoLabel(new QLabel("Dove si usa?",this)),
    marca(new QLineEdit(this)), nome(new QLineEdit(this)),
    capacita(new QLineEdit(this)), consumo(new QLineEdit(this)),
    materiale(new QLineEdit(this)), contatore(new QLineEdit(this)),
    colore(new QLineEdit(this)), odore(new QLineEdit(this)), parteDelCorpo(new QLineEdit(this)) //consumo(new QLineEdit(this)), contatore(new QLineEdit(this))
{
    QPushButton* insertButton = new QPushButton("Inserisci", this);
    tipo->addItem("MakeUp");
    tipo->addItem("Pulizia");
    tipo->addItem("Profumo");
    tipo->addItem("Strumento");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QVBoxLayout* fieldsLayout = new QVBoxLayout();
    QHBoxLayout* tipoLayout = new QHBoxLayout();
    QHBoxLayout* nomeLayout = new QHBoxLayout();
    QHBoxLayout* marcaLayout = new QHBoxLayout();
    QHBoxLayout* capacitaLayout = new QHBoxLayout();
    QHBoxLayout* consumoLayout = new QHBoxLayout();
    QHBoxLayout* materialeLayout = new QHBoxLayout();
    QHBoxLayout* contatoreLayout = new QHBoxLayout();
    QHBoxLayout* coloreLayout = new QHBoxLayout();
    QHBoxLayout* odoreLayout = new QHBoxLayout();
    QHBoxLayout* parteDelCorpoLayout = new QHBoxLayout();

    tipoLayout->addWidget(tipoLabel);
    tipoLayout->addWidget(tipo);
    marcaLayout->addWidget(marcaLabel);
    marcaLayout->addWidget(marca);
    nomeLayout->addWidget(nomeLabel);
    nomeLayout->addWidget(nome);
    capacitaLayout->addWidget(capacitaLabel);
    capacitaLayout->addWidget(capacita);
    consumoLayout->addWidget(consumoLabel);
    consumoLayout->addWidget(consumo);
    materialeLayout->addWidget(materialeLabel);
    materialeLayout->addWidget(materiale);
    contatoreLayout->addWidget(contatoreLabel);
    contatoreLayout->addWidget(contatore);
    coloreLayout->addWidget(coloreLabel);
    coloreLayout->addWidget(colore);
    odoreLayout->addWidget(odoreLabel);
    odoreLayout->addWidget(odore);
    parteDelCorpoLayout->addWidget(parteDelCorpoLabel);
    parteDelCorpoLayout->addWidget(parteDelCorpo);
    fieldsLayout->addLayout(marcaLayout);
    fieldsLayout->addLayout(nomeLayout);
    fieldsLayout->addLayout(coloreLayout);
    fieldsLayout->addLayout(odoreLayout);
    fieldsLayout->addLayout(parteDelCorpoLayout);
    fieldsLayout->addLayout(capacitaLayout);
    fieldsLayout->addLayout(consumoLayout);
    fieldsLayout->addLayout(materialeLayout);
    fieldsLayout->addLayout(contatoreLayout);
    mainLayout->addLayout(tipoLayout);
    mainLayout->addLayout(fieldsLayout);
    mainLayout->addWidget(insertButton);
    connect(tipo, SIGNAL(currentTextChanged(const QString&)), this, SLOT(setRightFields(const QString &)));
    connect(insertButton, SIGNAL(clicked()), this, SIGNAL(insertClicked()));
    setLayout(mainLayout);
    emit(tipo->currentTextChanged(tipo->currentText()));
}

void insertWidget::setRightFields(const QString& s){
    capacitaLabel->setVisible(false);
    capacita->setVisible(false);
    consumoLabel->setVisible(false);
    consumo->setVisible(false);
    materialeLabel->setVisible(false);
    materiale->setVisible(false);
    contatoreLabel->setVisible(false);
    contatore->setVisible(false);
    coloreLabel->setVisible(false);
    colore->setVisible(false);
    odoreLabel->setVisible(false);
    odore->setVisible(false);
    parteDelCorpoLabel->setVisible(false);
    parteDelCorpo->setVisible(false);
    if(s=="MakeUp"){
        capacitaLabel->setVisible(true);
        capacita->setVisible(true);
        consumoLabel->setVisible(true);
        consumo->setVisible(true);
        coloreLabel->setVisible(true);
        colore->setVisible(true);
    } else if (s=="Pulizia"){
        capacitaLabel->setVisible(true);
        capacita->setVisible(true);
        consumoLabel->setVisible(true);
        consumo->setVisible(true);
        parteDelCorpoLabel->setVisible(true);
        parteDelCorpo->setVisible(true);
    } else if (s=="Profumo"){
        capacitaLabel->setVisible(true);
        capacita->setVisible(true);
        consumoLabel->setVisible(true);
        consumo->setVisible(true);
        odoreLabel->setVisible(true);
        odore->setVisible(true);
    } else if (s=="Strumento"){
        materialeLabel->setVisible(true);
        materiale->setVisible(true);
        contatoreLabel->setVisible(true);
        contatore->setVisible(true);
        parteDelCorpoLabel->setVisible(true);
        parteDelCorpo->setVisible(true);
    }
}
std::string insertWidget::getTipo() const{ return tipo->currentText().toStdString(); }
std::string insertWidget::getMarca() const{ return marca->text().toStdString(); }
std::string insertWidget::getNome() const{ return nome->text().toStdString(); }
float insertWidget::getCapacita() const{ return capacita->text().toFloat(); }
float insertWidget::getConsumo() const{ return consumo->text().toFloat(); }
std::string insertWidget::getMateriale() const{ return materiale->text().toStdString(); }
unsigned int insertWidget::getContatore() const{ return contatore->text().toUInt(); }
std::string insertWidget::getColore() const{ return colore->text().toStdString(); }
std::string insertWidget::getOdore() const{ return odore->text().toStdString(); }
std::string insertWidget::getParteDelCorpo() const{ return parteDelCorpo->text().toStdString(); }

