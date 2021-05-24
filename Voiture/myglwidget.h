#ifndef GL_H
#define GL_H
#include "Car.h"
#include "Ground.h"
#include"bidon.h"
#include "ui.h"
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>
#include <QTimer>
#include<QMouseEvent>
#include<QDebug>
#include<imageprocessing.h>


// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QOpenGLWidget
{
public:

    // Constructeur
    MyGLWidget(QWidget * parent = nullptr);
    ~MyGLWidget();
    void mousePressEvent(QMouseEvent *event);
    void processHits(GLint hits,GLuint buffer[]);
    void updateDrawing(int d);

private:
    PlayerCar * pcar_;
    EnemyCar * ecar_; //a enlveer mais for now laisse
    Bidon * bid_;
    float vitesse_;
    UI *gui_;
    Ground * ground_;
    float m_TimeElapsed_ { 0.0f };
    QTimer m_AnimationTimer_;
    ImageProcessing* imgProc_;

protected:

    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    // Fonction de gestion d'interactions clavier
    void keyPressEvent(QKeyEvent* event);

    // fonction picking

    //
    void detectcollision();

};
#endif
