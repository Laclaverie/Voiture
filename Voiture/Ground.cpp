#include "Ground.h"

Ground::Ground(float* speed)
{
    vitessep_=speed;
    Grass_ = QGLWidget::convertToGLFormat(QImage(":/grass.jpg"));
    Road_ = QGLWidget::convertToGLFormat(QImage(":/road.jpg"));

    texture_ = new GLuint[2];
    glGenTextures(2, texture_);

    glBindTexture(GL_TEXTURE_2D, texture_[0]);
    glTexImage2D(GL_TEXTURE_2D,0,4,Grass_.width(),Grass_.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,Grass_.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glBindTexture(GL_TEXTURE_2D, texture_[1]);
    glTexImage2D(GL_TEXTURE_2D,0,4,Road_.width(),Road_.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,Road_.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Ground::~Ground()
{
    delete vitessep_;
}


void Ground::Display()
{
    shift_=shift_+*vitessep_;
    shift_=shift_-100.f*floor(shift_/100.f);

    glEnable(GL_TEXTURE_2D);

    // Grass
    glBindTexture(GL_TEXTURE_2D, texture_[0]);
    glBegin(GL_QUADS);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    GLfloat herbe[]={0,1,0.2,1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, herbe);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, herbe);

    glNormal3f(0,1,0);

    glTexCoord2f(0,100+shift_/2);
    glVertex3f(-1000.f,-0.01f,-2000.f);

    glTexCoord2f(0,0+shift_/2);
    glVertex3f(-1000.f,-0.01f,10.f);

    glTexCoord2f(100,0+shift_/2);
    glVertex3f(1000.f,-0.01f,10.f);

    glTexCoord2f(100,100+shift_/2);
    glVertex3f(1000.f,-0.01f,-2000.f);
    glEnd();


    // road
    glBindTexture(GL_TEXTURE_2D, texture_[1]);
    glBegin(GL_QUADS);
    GLfloat route[]={0.2,0.2,0.2,1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, route);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, route);



    glNormal3f(0,1,0);

    glTexCoord2f(0,500+shift_/2);
    glVertex3f(-5.f,0.f,-2000.f);

    glTexCoord2f(0,0+shift_/2);
    glVertex3f(-5.f,0.f,10.f);

    glTexCoord2f(1,0+shift_/2);
    glVertex3f(5.f,0.f,10.f);

    glTexCoord2f(1,500+shift_/2);
    glVertex3f(5.f,0.f,-2000.f);

    glEnd();
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

