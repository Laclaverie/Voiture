#include <qopengl.h>
#include <GL/glu.h>
#include <math.h>
#include<QDebug>
#include<iomanip>
#include<random>
#include<iostream>

// Classe dediee pour la gestion de la voiture
class Car
{
public:
    // Constructeur avec parametres
    Car();

    // Destructeur
    ~Car();

    // Methode d'affichage
    void Display();
    void drawWheel();

private:
    GLUquadric* quad_ = nullptr;



};

class PlayerCar : public Car
{
public:
    PlayerCar();
    ~PlayerCar();

    void moveleft(){transx_-=0.1f;};
    void moveright(){transx_+=0.1f;};
    void disp();
    void DrawGyro();
    void DrawOil();

    bool getgyro(){return gyro_;};
    void setgyro(bool b){gyro_=b;};

    float gettransx(){return transx_;};
    void settransx(float f){transx_=f;};

    int getoil(){return oil_;}
    void setoil(int o){oil_=o;}

private:
    bool gyro_;
    float transx_;
    int oil_;
};

class EnemyCar : public Car
{
public:
    EnemyCar(float* f);
    ~EnemyCar();

    void disp();

    float getspeed(){return *speed_;};
    void setspeed(float f){*speed_=f;};

    float getposx(){return posx_;};
    void setposx(float b){posx_=b;};

    float getposz(){return posz_;};
    void setposz(float b){posz_=b;};


private:
    float *speed_=nullptr;
    float posz_;
    float posx_;

};
