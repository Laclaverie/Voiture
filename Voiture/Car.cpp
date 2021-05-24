#include "Car.h"

Car::Car()
{
    quad_=gluNewQuadric();
}

Car::~Car()
{
    gluDeleteQuadric(quad_);
}

void Car::Display()
{


        glBegin(GL_QUADS);


        // Front face
        glNormal3f(0,0,-1);
        glVertex3f(-0.5f,0.1f,-1);
        glVertex3f(-0.5f,1.1f,-1);
        glVertex3f(0.5f,1.1f,-1);
        glVertex3f(0.5f,0.1f,-1);

        // Back face
        glNormal3f(0,0,1);
        glVertex3f(-0.5f,0.1f,1);
        glVertex3f(0.5f,0.1f,1);
        glVertex3f(0.5f,1.1f,1);
        glVertex3f(-0.5f,1.1f,1);

        // Top face
        glNormal3f(0,1,0);
        glVertex3f(-0.5f,1.1f,1);
        glVertex3f(0.5f,1.1f,1);
        glVertex3f(0.5f,1.1f,-1);
        glVertex3f(-0.5f,1.1f,-1);

        // Bottom face
        glNormal3f(0,-1,0);
        glVertex3f(-0.5f,0.1f,1);
        glVertex3f(-0.5f,0.1f,-1);
        glVertex3f(0.5f,0.1f,-1);
        glVertex3f(0.5f,0.1f,1);

        // Right face
        glNormal3f(1,0,0);
        glVertex3f(0.5f,1.1f,1);
        glVertex3f(0.5f,0.1f,1);
        glVertex3f(0.5f,0.1f,-1);
        glVertex3f(0.5f,1.1f,-1);

        // Left face
        glNormal3f(-1,0,0);
        glVertex3f(-0.5f,0.1f,1);
        glVertex3f(-0.5f,1.1f,1);
        glVertex3f(-0.5f,1.1f,-1);
        glVertex3f(-0.5f,0.1f,-1);

        glEnd();


        // Wheels
        GLfloat roue[]={0.1,0.1,0.1,1.0};
        glMaterialfv(GL_FRONT, GL_AMBIENT, roue);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, roue);

        //Front right wheel
        glPushMatrix();
        glTranslatef(.5f,.25f,-0.75);
        drawWheel();
        glPopMatrix();

        //Back right wheel
        glPushMatrix();
        glTranslatef(.5f,.25f,0.5);
        drawWheel();
        glPopMatrix();

        //Front left wheel
        glPushMatrix();
        glTranslatef(-0.75f,.25f,-0.75);
        drawWheel();
        glPopMatrix();

        //Back left wheel
        glPushMatrix();
        glTranslatef(-0.75f,.25f,0.5);
        drawWheel();
        glPopMatrix();


}

void Car::drawWheel(){

    glPushMatrix();
    glRotatef(90,0,1,0);

    glColor3f(.25f,.25f,.25f);
    gluCylinder(quad_,.25,.25,.25,12,1);

    glColor3f(.25f,.25f,.25f);
    gluDisk(quad_,0.,.25,12,1);

    glColor3f(.25f,.25f,.25f);
    glTranslatef(0.f,0.f,0.25f);
    gluDisk(quad_,0.,.25,12,1);

    glPopMatrix();
}






PlayerCar::PlayerCar() : Car()
{
    transx_=0;
    gyro_=true;
    oil_=150;
}
PlayerCar::~PlayerCar(){}
void PlayerCar::disp()
{

    glPushMatrix();

        GLfloat light_voiture[]={0,0.5,1,1};
        glMaterialfv(GL_FRONT, GL_AMBIENT, light_voiture);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, light_voiture);
        glMaterialf(GL_FRONT,GL_SHININESS,90);
        glTranslatef(transx_,0,0);
        //qDebug()<< "xcar= "<<transx_;
        Display();
        DrawOil();
        DrawGyro();


    glPopMatrix();
}
void PlayerCar::DrawGyro()
{
    glPushMatrix();

        GLfloat gyrocolo1[]={1,0,0,1};
        GLfloat gyrocolo2[]={0,0,1,1};
        GLfloat pos[]={0,2,0,1};

        if (gyro_)
        {
            glMaterialfv(GL_FRONT, GL_AMBIENT, gyrocolo1);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, gyrocolo1);
            glLightfv(GL_LIGHT1,GL_DIFFUSE, gyrocolo1);
        }
        else
        {
            glMaterialfv(GL_FRONT, GL_AMBIENT, gyrocolo2);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, gyrocolo2);
            glLightfv(GL_LIGHT1,GL_DIFFUSE, gyrocolo2);
        }

        glLightfv(GL_LIGHT1,GL_POSITION, pos);

        glTranslatef(0.f,1.1f,-0.2f);
        GLUquadric* giro = gluNewQuadric();
        gluQuadricDrawStyle(giro, GLU_FILL);
        gluSphere(giro,0.1,20,20);
        gluDeleteQuadric(giro);

    glPopMatrix();
}
void PlayerCar::DrawOil()
{
    glBegin(GL_QUADS);
    glPushMatrix();
    if(oil_>=(2*150/3))
    {
        GLfloat oil_color[]={0,1,0,1};
        glMaterialfv(GL_FRONT, GL_AMBIENT, oil_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, oil_color);
    }
    else if (oil_>=150/3)
    {
        GLfloat oil_color[]={1,0.5f,0,1};
        glMaterialfv(GL_FRONT, GL_AMBIENT, oil_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, oil_color);
    }
    else
    {
        GLfloat oil_color[]={1,0,0,1};
        glMaterialfv(GL_FRONT, GL_AMBIENT, oil_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, oil_color);
    }


    glVertex3f(-0.2f,0.3f,1.1f); //bas gauche

    glVertex3f(0.2f,0.3f,1.1f); //bas droite

    glVertex3f(0.2f,(0.3f+(oil_*0.8f/150.0)),1.1f); //haut droite

    glVertex3f(-0.2f,(0.3f+(oil_*0.8f/150.0)),1.1f); //haut gauche


    glPopMatrix();
     glEnd();
}





EnemyCar::EnemyCar(float* f) : Car()
{
    srand(static_cast<unsigned int>(clock()));
    float HI = 3.1f;
    float LO=-3.1f;

    float x = LO + (rand())/float((RAND_MAX))*(HI-LO);

    posx_=x;
    speed_ =f;
    posz_=-200;
}
EnemyCar::~EnemyCar(){ }
void EnemyCar::disp()
{
    glPushMatrix();

        GLfloat light_voiture[]={1,0,0,1};
        glMaterialfv(GL_FRONT, GL_AMBIENT, light_voiture);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, light_voiture);
        glMaterialf(GL_FRONT,GL_SHININESS,90);
        if(*speed_==0)
            posz_=posz_+2;
        else
            posz_=posz_+(*speed_*4);
        glTranslatef(posx_,0,posz_);
        Display();

    glPopMatrix();
}
