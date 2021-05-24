#include <QApplication>
#include "myglwidget.h"
#include "appmanager.h"
#include "imageprocessing.h"

int main(int argc, char *argv[])
{
    // Creation de l'application QT
    QApplication app(argc, argv);

    // Creation du widget opengl
    MyGLWidget* glWidget= new MyGLWidget;
    int frame[]={640,480};
    ImageProcessing* imgProc=new ImageProcessing(frame);
    //glWidget.show();
    appManager appM=appManager(glWidget,imgProc);
    appM.run();
    // Execution de l'application QT
    return app.exec();
}
