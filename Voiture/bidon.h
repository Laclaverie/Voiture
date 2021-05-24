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

private:

    float *speed_=nullptr;
    float posz_;
    float posx_;
    QImage fuel_;
    GLUquadric* quadrique_ = gluNewQuadric();
    GLuint* texture_;

    float x_Border_Right_ = 4;
    float x_Border_Left_ = -4;


};

#endif // BIDON_H
