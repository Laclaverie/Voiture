#include "ui.h"

UI::UI(QWidget *parent) : QGraphicsView(parent)
{
    Scene_ = new QGraphicsScene(this);
    oillvl_=new QGraphicsTextItem("150");
    oillvl_->setPos(oillvl_->mapFromScene(50,50));
    oillvl_->setPos(100,200);
    Scene_->addItem(oillvl_);

    setScene(Scene_);
}

UI::~UI(){
    delete Scene_;
    delete oillvl_;
}
