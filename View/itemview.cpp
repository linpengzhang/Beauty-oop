#include "itemview.h"
#include "Model/hierarchy/makeup.h"
#include "Model/hierarchy/pulizia.h"
#include "Model/hierarchy/profumo.h"
#include "Model/hierarchy/strumento.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QModelIndex>
itemview::itemview(BeautyItem* _p,const QModelIndex& b, const QModelIndex& e, QWidget* parent) : QWidget(parent),p(_p), begin(b), end(e)
{
    QVBoxLayout* fieldsLayout = new QVBoxLayout(this);
    QHBoxLayout* tipoLayout = new QHBoxLayout();
    tipoLayout->addWidget(new QLabel("Tipo: "));
    tipoLayout->addWidget(tipo = new QLabel(QString::fromStdString(p->tipo())));
    fieldsLayout->addLayout(tipoLayout);
    QHBoxLayout* nomeLayout = new QHBoxLayout();
    nomeLayout->addWidget(new QLabel("Nome: "));
    nomeLayout->addWidget(nome = new QLineEdit(QString::fromStdString(p->getNome())));
    fieldsLayout->addLayout(nomeLayout);
    QHBoxLayout* marcaLayout = new QHBoxLayout();
    marcaLayout->addWidget(new QLabel("Marca: "));
    marcaLayout->addWidget(marca = new QLineEdit(QString::fromStdString(p->getMarca())));
    fieldsLayout->addLayout(marcaLayout);
    if(p->isConsumable()){
        QHBoxLayout* capacitaLayout = new QHBoxLayout();
        capacitaLayout->addWidget(new QLabel("Capacita: "));
        capacitaLayout->addWidget(capacita=new QLineEdit(QString::fromStdString(std::to_string(static_cast<ConsumableItem*>(p)->getCapacita()))));
        fieldsLayout->addLayout(capacitaLayout);
        QHBoxLayout* consumoLayout = new QHBoxLayout();
        consumoLayout->addWidget(new QLabel("Consumo: "));
        consumoLayout->addWidget(consumo=new QLineEdit(QString::fromStdString(std::to_string(static_cast<ConsumableItem*>(p)->getConsumo()))));
        fieldsLayout->addLayout(consumoLayout);
        if(p->tipo()=="MakeUp"){
            QHBoxLayout* coloreLayout = new QHBoxLayout();
            coloreLayout->addWidget(new QLabel("Colore: "));
            coloreLayout->addWidget(colore=new QLineEdit(QString::fromStdString(static_cast<MakeUp*>(p)->getColore())));
            fieldsLayout->addLayout(coloreLayout);
        } else if (p->tipo()=="Pulizia"){
            QHBoxLayout* parteDelCorpoLayout = new QHBoxLayout();
            parteDelCorpoLayout->addWidget(new QLabel("Parte del corpo: "));
            parteDelCorpoLayout->addWidget(parteDelCorpo=new QLineEdit(QString::fromStdString(static_cast<Pulizia*>(p)->getParteDelCorpo())));
            fieldsLayout->addLayout(parteDelCorpoLayout);
        } else if (p->tipo()=="Profumo"){
            QHBoxLayout* odoreLayout = new QHBoxLayout();
            odoreLayout->addWidget(new QLabel("Odore: "));
            odoreLayout->addWidget(odore=new QLineEdit(QString::fromStdString(static_cast<Profumo*>(p)->getOdore())));
            fieldsLayout->addLayout(odoreLayout);
        }
    } else {
        QHBoxLayout* materialeLayout = new QHBoxLayout();
        materialeLayout->addWidget(new QLabel("Materiale: "));
        materialeLayout->addWidget(materiale = new QLineEdit(QString::fromStdString(static_cast<NonConsumableItem*>(p)->getMateriale())));
        fieldsLayout->addLayout(materialeLayout);
        QHBoxLayout* contatoreLayout = new QHBoxLayout();
        contatoreLayout->addWidget(new QLabel("Contatore: "));
        contatoreLayout->addWidget(contatore = new QLineEdit(QString::fromStdString(std::to_string(static_cast<NonConsumableItem*>(p)->getContatore()))));
        fieldsLayout->addLayout(contatoreLayout);
        if(p->tipo()=="Strumento"){
            QHBoxLayout* parteDelCorpoLayout = new QHBoxLayout();
            parteDelCorpoLayout->addWidget(new QLabel("Parte del corpo: "));
            parteDelCorpoLayout->addWidget(parteDelCorpo=new QLineEdit(QString::fromStdString(static_cast<Strumento*>(p)->getParteDelCorpo())));
            fieldsLayout->addLayout(parteDelCorpoLayout);
        }
    }
    QPushButton* saveButton = new QPushButton(tr("Save"));
    saveButton->setToolTip(tr("Save your changes"));
    fieldsLayout->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveSettings()));
    setLayout(fieldsLayout);
}
void itemview::saveSettings(){
    p->setMarca(marca->text().toStdString());
    p->setNome(nome->text().toStdString());
    if(p->isConsumable()){
        static_cast<ConsumableItem*>(p)->setCapacita(capacita->text().toFloat());
        static_cast<ConsumableItem*>(p)->setConsumo(consumo->text().toFloat());
        if(p->tipo() == "MakeUp"){
            static_cast<MakeUp*>(p)->setColore(colore->text().toStdString());
        } else if (p->tipo()=="Pulizia"){
            static_cast<Pulizia*>(p)->setParteDelCorpo(parteDelCorpo->text().toStdString());
        } else if (p->tipo()=="Profumo"){
            static_cast<Profumo*>(p)->setOdore(odore->text().toStdString());
        }
    } else {
        static_cast<NonConsumableItem*>(p)->setContatore(contatore->text().toUInt());
        static_cast<NonConsumableItem*>(p)->setMateriale(materiale->text().toStdString());
        if(p->tipo()=="Strumento"){
            static_cast<Strumento*>(p)->setParteDelCorpo(parteDelCorpo->text().toStdString());
        }
    }
    emit dataChanged(begin, end);
}

