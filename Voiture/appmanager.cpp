#include "appmanager.h"

appManager::appManager(MyGLWidget* mw,ImageProcessing *imProc)
{
    mw_=mw;
    imProc_=imProc;
}
appManager::~appManager(){

}
void appManager::run(){

   // QFuture<void> future= QtConcurrent::run(this->imProc_,&ImageProcessing::Process);

    //QFuture<void> future2=QtConcurrent::run(this->mw_);
    //imProc_->start();
    mw_->show();
    while(cv::waitKey(5) < 0)
    {
        int d=imProc_->Process();
        mw_->updateDrawing(d);
    }
   // future.waitForFinished();
}
