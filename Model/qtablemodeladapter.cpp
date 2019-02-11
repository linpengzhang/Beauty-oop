#include "qtablemodeladapter.h"
#include "model.h"
#include "hierarchy/makeup.h"
#include "hierarchy/pulizia.h"
#include "hierarchy/profumo.h"
#include "hierarchy/strumento.h"
#include <QFont>
#include <QColor>
#include <QBrush>
#include <QVariant>
#include <QPushButton>
#include <QRegExp>
#include <QDebug>
#include "View/insertwidget.h"
#include "View/itemview.h"

QTableModelAdapter::QTableModelAdapter(QObject* parent, const insertWidget* i) :
    QAbstractTableModel(parent),
    model(new Model()),
    insert(i){}

QTableModelAdapter::~QTableModelAdapter() { //insert distrutto dal main
    if(model) delete model;
}

int QTableModelAdapter::rowCount(const QModelIndex &) const {
    return model->count();
}
int QTableModelAdapter::columnCount(const QModelIndex &) const {
    return 4;
}
QVariant QTableModelAdapter::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if(role==Qt::FontRole)
    {
        // return QVariant(QBrush (QColor(Qt::white)));
        return QFont("Arial", 24, QFont::Bold);
    }
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Numero");
        case 1:
            return QString("Marca");
        case 2:
            return QString("Nome");
        case 3:
            return QString("Tipo");
        default:
            return QVariant();
        }
    }
    return QVariant();
}
QVariant QTableModelAdapter::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() >= model->count() || index.row()<0)
        return QVariant();
    switch(role){
    case Qt::BackgroundColorRole:
        return QVariant(QBrush(QColor(Qt::gray)));
    case Qt::TextAlignmentRole:
        return QVariant ( Qt::AlignVCenter | Qt::AlignHCenter );
    case Qt::SizeHintRole:
        return QSize( 500, 0 );
    case Qt::EditRole:
    case Qt::DisplayRole:
    {
        switch(index.column())
        {
        case 0:
            return index.row()+1;
        case 1:
            return QString::fromStdString(model->getBeautyItem(static_cast<unsigned int>(index.row()))->getMarca());
        case 2:
            return QString::fromStdString(model->getBeautyItem(static_cast<unsigned int>(index.row()))->getNome());
        case 3:
            return QString::fromStdString(model->getBeautyItem(static_cast<unsigned int>(index.row()))->tipo());
        default:
            return QVariant();
        }
    }
    case Qt::FontRole:
        if (model->getBeautyItem(static_cast<unsigned int>(index.row()))->isConsumable())
            return QFont("Arial", 14);
        else return QFont("San Serif", 14);
    }
    return QVariant();
}

bool QTableModelAdapter::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() && role != Qt::EditRole)
        return false;
    switch(index.column())
    {
    case 1:
        model->getBeautyItem(static_cast<unsigned int>(index.row()))->setMarca(value.toString().toStdString()); break;
    case 2:
        model->getBeautyItem(static_cast<unsigned int>(index.row()))->setNome(value.toString().toStdString()); break;
    }
    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags QTableModelAdapter::flags(const QModelIndex& index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    if(index.column()==0 || index.column()==3)
        return QAbstractTableModel::flags(index);
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

/*
 * Inserisce 'count' nuove righe nel modello a partire dall'elemento di indice 'begin'
 */

bool QTableModelAdapter::insertRows(int begin, int count, const QModelIndex& parent) {
    beginInsertRows(parent, begin, begin + count - 1);
    std::string s = insert->getTipo();
    if(s=="MakeUp"){
        model->add(new MakeUp(insert->getMarca(), insert->getNome(), insert->getColore(), insert->getCapacita(), insert->getConsumo()));
    } else if (s=="Pulizia"){
        model->add(new Pulizia(insert->getMarca(), insert->getNome(), insert->getParteDelCorpo(), insert->getCapacita(), insert->getConsumo()));
    } else if (s=="Profumo"){
        model->add(new Profumo(insert->getMarca(), insert->getNome(), insert->getOdore(), insert->getCapacita(), insert->getConsumo()));
    } else if (s=="Strumento"){
        model->add(new Strumento(insert->getMarca(), insert->getNome(), insert->getParteDelCorpo(), insert->getMateriale(), insert->getContatore()));
    }
    endInsertRows();
    return true;
}
bool QTableModelAdapter::removeRows(int begin, int count, const QModelIndex& parent) {
    beginRemoveRows(parent, begin, begin + count - 1);
    model->remove(begin);
    endRemoveRows();
    return true;
}
void QTableModelAdapter::showMore(const QModelIndex & index) {
    if (index.isValid() && static_cast<unsigned int>(index.row()) < rowCount() && index.column()<columnCount()){
        itemview* item = new itemview(model->getBeautyItem(static_cast<unsigned int>(index.row())), QAbstractTableModel::createIndex(index.row(), 0), QAbstractTableModel::createIndex(index.row(), columnCount()-1));
        connect(item, SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)));
        item->setAttribute(Qt::WA_DeleteOnClose); //item viene distrutto alla sua chiusura
        item->show();
    }
}
bool QTableModelAdapter::use(const QModelIndex & index) const {
    if (!index.isValid() || index.row() >= rowCount() || index.column()>=columnCount())
        return false;
    return model->use(index.row());
}
void QTableModelAdapter::saveToFile(const std::string& filename) const {
    model->saveToFile(filename);
}
void QTableModelAdapter::loadFromFile(const std::string& filename) const {
    model->loadFromFile(filename);
}
const insertWidget* QTableModelAdapter::getInsertWidget() const{
    return insert;
}
bool QTableModelAdapter::matchRegExp(unsigned int r, const QRegExp& s, const QString& a) const{
    if(a=="Nome")
        return QString::fromStdString(model->getBeautyItem(r)->getNome()).contains(s);
    else if(a=="Marca")
        return QString::fromStdString(model->getBeautyItem(r)->getMarca()).contains(s);
    else if(a=="Tipo")
        return QString::fromStdString(model->getBeautyItem(r)->tipo()).contains(s);
    else if(a=="Materiale")
        return !model->getBeautyItem(r)->isConsumable() && QString::fromStdString(static_cast<NonConsumableItem*>(model->getBeautyItem(r))->getMateriale()).contains(s);
    else if(a=="Colore")
        return QString::fromStdString(model->getBeautyItem(r)->tipo())=="MakeUp" && QString::fromStdString(static_cast<MakeUp*>(model->getBeautyItem(r))->getColore()).contains(s);
    else if(a=="Odore")
        return QString::fromStdString(model->getBeautyItem(r)->tipo())=="Profumo" && QString::fromStdString(static_cast<Profumo*>(model->getBeautyItem(r))->getOdore()).contains(s);
    else if(a=="Parte del corpo")
        return (QString::fromStdString(model->getBeautyItem(r)->tipo())=="Pulizia" && QString::fromStdString(static_cast<Pulizia*>(model->getBeautyItem(r))->getParteDelCorpo()).contains(s)) || (QString::fromStdString(model->getBeautyItem(r)->tipo())=="Strumento" && QString::fromStdString(static_cast<Strumento*>(model->getBeautyItem(r))->getParteDelCorpo()).contains(s));
    else
        return false;
}
void QTableModelAdapter::useResults(const std::vector<unsigned int>& v) const{
    model->useIndexes(v);
}
