#include "ui.h"
#include<QDebug>

UI::UI(QWidget *parent) : QGraphicsView(parent)
{
    Scene_ = new QGraphicsScene(this);
    time_=new QGraphicsSimpleTextItem();
    time_->setPos(time_->mapFromScene(50,50));
    time_->setPos(500,500);
    f = new QFont;
    f->setPointSize(18);
    time_->setFont(*f);
    Scene_->addItem(time_);
    time_->setText("00:00");

    setScene(Scene_);
}

UI::~UI(){
    delete Scene_;
    delete time_;
    delete f;
}

void UI::increasetime()
{
    QString time= time_->text();
    int minutes = time.split(":")[0].toInt();
    float seconds = time.split(":")[1].toFloat();

    seconds+=0.1f;
    if(seconds>=60)
    {
        minutes++;
        seconds-=60;
    }
    if (seconds ==10)
    {
        f->setPointSize(14);
        time_->setFont(*f);
    }
    QString str = QString("%1%2%3").arg(QString::number(minutes),tr(":"),QString::number(seconds));
    time_->setText(str);

}
