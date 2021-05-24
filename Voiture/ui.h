#ifndef UI_H
#define UI_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSimpleTextItem>
#include  <tgmath.h>


class UI : public QGraphicsView
{
public:
    UI(QWidget *parent = 0);
    ~UI();

    void resettime(){time_->setText("00:00");}
    void increasetime();

private:
    QFont * f;
    QGraphicsScene* Scene_;
    QGraphicsSimpleTextItem* time_;
};

#endif // UI_H
