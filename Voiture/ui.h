#ifndef UI_H
#define UI_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>


class UI : public QGraphicsView
{
public:
    UI(QWidget *parent = 0);
    ~UI();

    void setoil(int l){oillvl_->setPlainText(QString::number(l));}

private:
    QGraphicsScene* Scene_;
    QGraphicsTextItem* oillvl_;
};

#endif // UI_H
