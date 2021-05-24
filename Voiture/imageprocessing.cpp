#include "imageprocessing.h"

ImageProcessing::ImageProcessing(int framedata[2]) // framedata : [width,Height]
{
    // size of image
     frameWidth_=framedata[0];
     frameHeight_=framedata[1];

     // queue
     //q_=q;

     // tcheck if camera ok
     cap_=cv::VideoCapture(0);
     cap_.set(cv::CAP_PROP_FRAME_WIDTH,frameWidth_);
     cap_.set(cv::CAP_PROP_FRAME_HEIGHT,frameHeight_);
     if(!cap_.isOpened()){  // check if we succeeded
      std::cerr<<"Error openning the default camera"<<std::endl;
    }

     // tcheck if cascade classifier ok
     if( !hand_cascade_.load( "../Voiture/res/fist3.xml" ) )
     {
         std::cerr<<"Error loading haarcascade"<<std::endl;

     }
     if( !palm_cascade_.load( "../Voiture/res/palm_v4.xml" ) )
     {
         std::cerr<<"Error loading haarcascade"<<std::endl;

     }
}
ImageProcessing::~ImageProcessing(){
    cap_.release();
}
int ImageProcessing::Process(){


       // Init output window
       cv::namedWindow("WebCam",1);
           cv::Mat frame,frame_gray;
           std::vector<cv::Rect> fist;
           std::vector<cv::Rect> palms;
           // Get frame
           cap_ >> frame;
           // Mirror effect
           cv::flip(frame,frame,1);
           // Convert to gray
           cv::cvtColor(frame,frame_gray,cv::COLOR_BGR2GRAY);
           // Equalize graylevels
   //        equalizeHist( frame_gray, frame_gray );
           //-- Detect palm
           hand_cascade_.detectMultiScale( frame_gray, fist, 1.1, 4, 0, cv::Size(60, 60) );
           palm_cascade_.detectMultiScale( frame_gray, palms, 1.1, 4, 0, cv::Size(60, 60) );
           if (fist.size()>0)
           {
               // Draw green rectangle
               for (int i=0;i<(int)fist.size();i++)
                   rectangle(frame,fist[i],cv::Scalar(0,255,0),2);
                    ImageProcessing::AnalyseRectangle(fist,false);
                    if(direction_!=25){
                   // qDebug()<<" Direction : "<< direction_;
                    }
           }
           if(palms.size()>1){
               qDebug()<<"NB PALM : "<<palms.size();
               for (int i=0;i<(int)palms.size();i++){
                       rectangle(frame,palms[i],cv::Scalar(0,0,255),2);
               }
                ImageProcessing::AnalyseRectangle(palms,true);
           }

           // Display frame
           imshow("WebCam", frame);
           return direction_;
}

void ImageProcessing::AnalyseRectangle(std::vector<cv::Rect> listRect,bool choix){
    direction_=25;
    ImageProcessing::findLeftRight(listRect);
    if(choix ==false){
    if(listRect.size()>1){ // deux mains ou plus

         /* --- Tcheck si jamais le rectangle est au dessus ou en dessous --- */

         if(listRect[index_rect_gauche_].y>listRect[index_rect_droit_].y && abs(listRect[index_rect_gauche_].y-listRect[index_rect_droit_].y)>20){
             direction_ =1; // on tourne à gauche
            // qDebug()<< " tourner à gauche";

         }
         else if (listRect[index_rect_gauche_].y<listRect[index_rect_droit_].y && abs(listRect[index_rect_gauche_].y-listRect[index_rect_droit_].y)>20) {
             direction_=2; // on tourne à droite
             //qDebug()<< " tourner à droite";

         }
         else if (abs(listRect[index_rect_gauche_].x+listRect[index_rect_gauche_].height-listRect[index_rect_droit_].x)<10) {
             direction_=0;
             qDebug()<<"STOP";
         }
         else{
             ; // si une de ces condutions n'est pas satisfaite, fait rien du tout.
         }

        }
    }
    else{
        if(listRect.size()==2){
        direction_=0;
        }
    }
}

void ImageProcessing::run(){

    while(true)
        ImageProcessing::Process();

}
void ImageProcessing::findLeftRight(std::vector<cv::Rect> listRect){
    if(listRect.size()>1){ // deux mains ou plus

    int tab_tri[listRect.size()] ;

    for(int i=0;i<listRect.size();i++){
        tab_tri[i]=listRect[i].width*listRect[i].height;
    }
  //  int *index_max =std::find(tab_tri,tab_tri+listRect.size(),max_element(tab_tri,tab_tri+listRect.size()));
     int largest = -1;
     int second_largest = -1;

     int index_of_largest = -1;
     int index_of_second_largest = -1;

     for (int j = 0; j <listRect.size(); j++)  // find the largest
         {
             if (tab_tri[j] >= largest)
             {
                 largest = tab_tri[j];
                 index_of_largest = j;
             }
         }
     for (int k = 0; k < listRect.size(); k++)  // find the second largest
         {
             if (k != index_of_largest) // skip over the largest one
             {
                 if (tab_tri[k] >= second_largest)
                 {
                     second_largest = tab_tri[k];
                     index_of_second_largest = k;
                 }
             }
         }
    // Rectangle gauche & droit
     if(listRect[index_of_largest].x>0&&listRect[index_of_second_largest].x>0){

     if(listRect[index_of_largest].x<listRect[index_of_second_largest].x){
         // donc le plus gros rectangle est à gauche
         index_rect_gauche_=index_of_largest;
         index_rect_droit_=index_of_second_largest;


     }
     else{
         index_rect_droit_=index_of_largest;
         index_rect_gauche_=index_of_second_largest;

     }
     }
    }
}
