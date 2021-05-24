#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include"imageprocessing.h"
#include "myglwidget.h"
#include<QFuture>
#include<QtConcurrent/QtConcurrent>


class appManager:public QObject
{
    Q_OBJECT
public:
    appManager(MyGLWidget* mw,ImageProcessing* imProc);
    ~appManager();
    void run();
private:
    MyGLWidget* mw_;
    ImageProcessing *imProc_;
    QFuture<void> myFuture;
};

#endif // APPMANAGER_H
