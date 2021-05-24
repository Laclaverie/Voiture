#include "bidon.h"

Bidon::Bidon(float *f)
{

    QImage bid = QGLWidget::convertToGLFormat(QImage(":/fuel.jpg"));
    QImage arret = QGLWidget::convertToGLFormat(QImage(":/arret.png"));

    texture = new GLuint[2];
    glGenTextures(2, texture);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexImage2D(GL_TEXTURE_2D,0,4,bid.width(),bid.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,bid.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexImage2D(GL_TEXTURE_2D,0,4,arret.width(),arret.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,arret.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    speed_= f;
    posz_=-200;

    srand(static_cast<unsigned int>(clock()));

    if(rand()/float(RAND_MAX)<0.5){
        posx_=x_Border_Right_;
    }
    else{
        posx_= x_Border_Left_;
    }


}
Bidon::~Bidon(){
gluDeleteQuadric(quadrique_);
}
void Bidon::drawBidon(){
    posz_=posz_+(*speed_*4);

    glEnable(GL_TEXTURE_2D);
    glTranslatef(posx_,2,posz_);
    /*glPushMatrix();
    glBegin(GL_QUADS);
    glBindTexture(GL_TEXTURE_2D, texture[1]); //ca prrnd la texture de la route ???

    GLfloat arret[]={1,1,1,1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, arret);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, arret);

    glNormal3f(0,0,1);
    glNormal3f(0,1,0);
    glTexCoord2f(0,1);
    glVertex3f(-3,-1.99f,-3);

    glTexCoord2f(0,0);
    glVertex3f(-3,-1.99f,3);

    glTexCoord2f(1,0);
    glVertex3f(0,-1.99f,3);

    glTexCoord2f(1,1);
    glVertex3f(0,-1.99f,-3);
    glEnd();*/

    glPushMatrix();

        glBindTexture(GL_TEXTURE_2D, texture[0]);

        glRotatef(90,1.,0.,0.);

        gluQuadricDrawStyle(quadrique_,GLU_FILL);
        gluQuadricTexture(quadrique_,GL_TRUE);
        gluCylinder(quadrique_,.5,.5,1.,50,50);

    glPopMatrix();
    //glPopMatrix();

}
void Bidon::displayBidon(){

    glPushMatrix();


    if(picked_)
    {
        GLfloat bidon []= {0.5f,0,0.1f,1.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, bidon);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, bidon);
    }
    else
    {
        GLfloat bidon []= {0.5f,0.5f,0.5f,1.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, bidon);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, bidon);
    }

    glMaterialf(GL_FRONT,GL_SHININESS,90);

    Bidon::drawBidon();

    glPopMatrix();


}
