#ifndef QLISTMODELADAPTER_H
#define QLISTMODELADAPTER_H

#include <QAbstractTableModel>
#include <vector>
class BeautyItem;
class insertWidget;
class QRegExp;
class Model;
class itemview;

class QTableModelAdapter: public QAbstractTableModel {
private:
    Model* model;
    const insertWidget* insert;
public:
    QTableModelAdapter(QObject* = nullptr, const insertWidget* = nullptr);
    ~QTableModelAdapter() override;
    int rowCount(const QModelIndex& = QModelIndex()) const override;
    int columnCount(const QModelIndex& = QModelIndex()) const override;
    QVariant headerData(int, Qt::Orientation, int) const override;
    QVariant data(const QModelIndex&, int = Qt::DisplayRole) const override;
    bool setData(const QModelIndex&, const QVariant&, int) override;
    Qt::ItemFlags flags(const QModelIndex&) const override;
    bool insertRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
    bool removeRows(int, int = 1, const QModelIndex& = QModelIndex()) override;
    void showMore(const QModelIndex&);
    void saveToFile(const std::string&) const;
    void loadFromFile(const std::string &) const;
    const insertWidget* getInsertWidget() const;
    bool matchRegExp(unsigned int, const QRegExp&, const QString&) const;
    bool use(const QModelIndex&) const;
    void useResults(const std::vector<unsigned int>&) const;
    void removeResults(const std::vector<unsigned int> &);
};

#endif // QLISTMODELADAPTER_H
