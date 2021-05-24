#ifndef BIDON_H
#define BIDON_H
#include <qopengl.h>
#include <QImage>
#include <GL/glu.h>
#include<QGLWidget>
#include<QDebug>

class Bidon
{
public:
    Bidon(float *f);
    ~Bidon();
    void drawBidon();
    void displayBidon();
    float getposz(){return posz_;};

    void setstatus(bool b){picked_=b;};
    float getstatus(){return picked_;};

private:
    GLuint* texture;
    bool picked_=false;
    float *speed_=nullptr;
    float posz_;
    float posx_;
    GLUquadric* quadrique_ = gluNewQuadric();

    float x_Border_Right_ = 4;
    float x_Border_Left_ = -4;


};

#endif // BIDON_H
