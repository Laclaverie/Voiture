#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>

#include<QtConcurrent/QtConcurrent>

#include <queue>
#include <thread>
#include <cstdio>
#include <iostream>
#include<QDebug>
#include<QMutex>
#include<QObject>



class ImageProcessing :public QThread//https://github.com/OAID/CVGesture/blob/master/fist_v3.xml
{


public:
    ImageProcessing(int framedata[2]);
    ~ImageProcessing();
    int Process();
    void AnalyseRectangle(std::vector<cv::Rect> listRect,bool choix);
    void findLeftRight(std::vector<cv::Rect> listRect);

private:
    int frameWidth_=640;
    int frameHeight_=480;
    int direction_=0 ; // 0 : arrêt, 1: gauche, 2: droite
    cv::VideoCapture cap_; // open the default camera
    cv::CascadeClassifier hand_cascade_;
    cv::CascadeClassifier palm_cascade_;
    std::queue<int> q_;
    std::vector<std::vector<cv::Rect>> slidingWindows; // tableau des rectangles des images.
    /*  Chaque vector<Rect> contient n rectangles (0,1,2 en théorie, mais des fois il y a des artéfacts) pour une frame
     *  Chaque rectangle représentant bien évidement le poing de l'utilisateur
     *  on stoke m images pour pouvoir tcheck si il n'y a pas trop de sauts, dans ce cas là, ne pas prendre la mesure mais une autre
     *  */
    QMutex mutex_;
    int index_rect_gauche_,index_rect_droit_;

protected:
       void run();
};

#endif // IMAGEPROCESSING_H
