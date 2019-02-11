#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QTableView>

/*
 * Classe utile per dimensionare correttamente la view con sizeHint()
 */
class TableView : public QTableView {
public:
    TableView(QWidget* = nullptr);
    QSize sizeHint() const override;
    void mousePressEvent(QMouseEvent*) override;
    //void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // TABLEVIEW_H
