#include "Ground.h"

Ground::Ground(float* speed)
{
    vitessep_=speed;

    glEnable(GL_TEXTURE_2D);

    QImage Grass = QGLWidget::convertToGLFormat(QImage(":/grass.jpg"));
    QImage Road = QGLWidget::convertToGLFormat(QImage(":/road.jpg"));
    QImage Sky = QGLWidget::convertToGLFormat(QImage(":/stars.jpg"));

    texture = new GLuint[3];
    glGenTextures(3, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D,0,4,Grass.width(),Grass.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,Grass.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D,0,4,Road.width(),Road.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,Road.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexImage2D(GL_TEXTURE_2D,0,4,Sky.width(),Sky.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,Sky.bits());

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

    //sky
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glBegin(GL_QUADS);

    GLfloat ciel[]={1,1,1,1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, ciel);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ciel);

    glNormal3f(0,0,1);
    glTexCoord2f(0,1);
    glVertex3f(-700,687,-1000.f);

    glTexCoord2f(0,0);
    glVertex3f(-700,-100,-1000.f);

    glTexCoord2f(1,0);
    glVertex3f(700,-100,-1000.f);

    glTexCoord2f(1,1);
    glVertex3f(700,687,-1000.f);
    glEnd();

    // Grass
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glBegin(GL_QUADS);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    GLfloat herbe[]={0.3,0.5,0.3,1.0};
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
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glBegin(GL_QUADS);
    GLfloat route[]={0.3,0.3,0.3,1.0};
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

