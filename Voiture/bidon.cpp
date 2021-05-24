#include "bidon.h"

Bidon::Bidon(float *f)
{

    fuel_ = QGLWidget::convertToGLFormat(QImage(":/fuel.jpg"));
    speed_= f;
    posz_=-200;

    srand(static_cast<unsigned int>(clock()));

    if(rand()/float(RAND_MAX)<0.5){
        posx_=x_Border_Right_;
    }
    else{
        posx_= x_Border_Left_;
    }
    texture_= new GLuint[1];
    glGenTextures(1, texture_);

    glBindTexture(GL_TEXTURE_2D, texture_[0]);
    glTexImage2D(GL_TEXTURE_2D,0,4,fuel_.width(),fuel_.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,fuel_.bits());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


}
Bidon::~Bidon(){

delete speed_;
   qDebug()<< " j'ai bien supprimé speed";
}
void Bidon::drawBidon(){
    posz_=posz_+(*speed_*4);

    glTranslatef(posx_,2,posz_);

    glPushMatrix();
        glEnable(GL_TEXTURE_2D);

glBindTexture(GL_TEXTURE_2D, texture_[0]);


        glRotatef(90,1.,0.,0.);

        gluQuadricDrawStyle(quadrique_,GLU_FILL);
        gluCylinder(quadrique_,.5,.5,1.,50,50);

        glPopMatrix();

}
void Bidon::displayBidon(){

    glPushMatrix();

    GLfloat bidon []= {0,1,0.2,1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, bidon);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bidon);
    glMaterialf(GL_FRONT,GL_SHININESS,90);

    Bidon::drawBidon();

    glPopMatrix();


}
