#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include <QWidget>
#include <QModelIndex>
class QLineEdit;
class QLabel;
class BeautyItem;
class itemview : public QWidget
{
    Q_OBJECT
private:
    BeautyItem* p;
    const QModelIndex begin; //riga del view che sta modificando
    const QModelIndex end;
    QLineEdit* marca;
    QLineEdit* nome;
    QLabel* tipo;
    QLineEdit* colore;
    QLineEdit* odore;
    QLineEdit* parteDelCorpo;
    QLineEdit* capacita;
    QLineEdit* consumo;
    QLineEdit* materiale;
    QLineEdit* contatore;
public:
    explicit itemview(BeautyItem*, const QModelIndex&, const QModelIndex&, QWidget *parent = nullptr);
signals:
    void dataChanged(const QModelIndex&, const QModelIndex&);
private slots:
    void saveSettings();
};

#endif // ITEMVIEW_H
