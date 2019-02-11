#ifndef INSERTWIDGET_H
#define INSERTWIDGET_H

#include <QWidget>
class QVBoxLayout;
class QLineEdit;
class QString;
class QComboBox;
class QLabel;
class insertWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel* tipoLabel;
    QComboBox* tipo;
    QLabel* marcaLabel;
    QLabel* nomeLabel;
    QLabel* coloreLabel;
    QLabel* odoreLabel;
    QLabel* parteDelCorpoLabel;
    QLabel* capacitaLabel;
    QLabel* consumoLabel;
    QLabel* materialeLabel;
    QLabel* contatoreLabel;
    QLineEdit* marca;
    QLineEdit* nome;
    QLineEdit* colore;
    QLineEdit* odore;
    QLineEdit* parteDelCorpo;
    QLineEdit* capacita;
    QLineEdit* consumo;
    QLineEdit* materiale;
    QLineEdit* contatore;

public:
    explicit insertWidget(QWidget *parent = nullptr);
    std::string getTipo() const;
    std::string getMarca() const;
    std::string getNome() const;
    float getCapacita() const;
    float getConsumo() const;
    std::string getMateriale() const;
    unsigned int getContatore() const;
    std::string getColore() const;
    std::string getParteDelCorpo() const;
    std::string getOdore() const;

signals:
    void insertClicked();
private slots:
    void setRightFields(const QString &);
};

#endif // INSERTWIDGET_H
