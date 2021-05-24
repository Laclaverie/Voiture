#include "myglwidget.h"
#include <QApplication>
#include <QDesktopWidget>

// Declarations des constantes
const unsigned int WIN = 800;

// Constructeur
MyGLWidget::MyGLWidget(QWidget * parent) : QOpenGLWidget(parent)
{
    // Reglage de la taille/position
    setFixedSize(WIN, WIN);
    move(QApplication::desktop()->screen()->rect().center() - rect().center());

    // Connexion du timer
    connect(&m_AnimationTimer_,  &QTimer::timeout, [&] {
        m_TimeElapsed_ += 1.0f;
        pcar_->setgyro(!pcar_->getgyro());


        if(vitesse_!=0 && pcar_->getoil()>0)
        {
            pcar_->setoil(pcar_->getoil()-1);
            //qDebug()<<"oil: "<<pcar_->getoil();
        }
        gui_->setoil(pcar_->getoil());

        update();
    });

    m_AnimationTimer_.setInterval(100);
    m_AnimationTimer_.start();

}
MyGLWidget::~MyGLWidget(){
    delete pcar_;
    delete ecar_;
    delete bid_;
    delete ground_;
    delete imgProc_;

}


// Fonction d'initialisation
void MyGLWidget::initializeGL()
{

    vitesse_= 1;
    pcar_ = new PlayerCar();
    ecar_ = new EnemyCar(&vitesse_);
    ground_ = new Ground(&vitesse_);
    bid_ = new Bidon(&vitesse_);
    gui_=new UI(this);
    int withd[2]={680,640};
   // imgProc_=new ImageProcessing(withd);


    glClearColor(.3f,.7f,.9f,1.f);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    //ca clignotre jsp pk
    GLfloat soleil[]={0.9,0.9,0.9,1};
    GLfloat test[]={10,10,6,1};
    glLightfv(GL_LIGHT0,GL_AMBIENT, soleil);
    glLightfv(GL_LIGHT0,GL_DIFFUSE, soleil);
    glLightfv(GL_LIGHT0,GL_POSITION, test);


    //rajouter diffuse pour faire des ombres
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}


// Fonction de redimensionnement
void MyGLWidget::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);
}

// Fonction d'affichage
void MyGLWidget::paintGL()
{

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.,1.,2,2000.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,4,5,
              0,1.,0,
              0,1,0);

    ground_->Display();
    pcar_->disp();
    ecar_->disp();
    detectcollision();
    bid_->displayBidon();
    //imgProc_->Process();
    if (ecar_->getposz()>10)
    {
        //delete ecar_;
        ecar_ = new EnemyCar(&vitesse_);

    }
    if (bid_->getposz()>3)
    {

        //delete bid_;
        bid_= new Bidon(&vitesse_);

    }

}


// Fonction de gestion d'interactions clavier
void MyGLWidget::keyPressEvent(QKeyEvent * event)
{
    qDebug("touche");
    switch(event->key())
    {
        //case Qt::Key_Left:
        case Qt::Key_A:
            if(vitesse_!=0)
            {
                qDebug("fleche");
                pcar_->moveleft();
            }
            break;
        //case Qt::Key_Right:
        case Qt::Key_D:
            if(vitesse_!=0)
            {
                qDebug("fleche");
                pcar_->moveright();
            }
            break;
        case Qt::Key_Space:
            vitesse_=0;
            break;
        case Qt::Key_Enter:
            vitesse_=1;
            break;
        default:
        {
            // Ignorer l'evenement
            event->ignore();
            return;
        }
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    //update();
}
void MyGLWidget::mousePressEvent(QMouseEvent *event){

    if (event-> button()==Qt::LeftButton)
    {
    /* ------------ hits ---------*/

        GLint hits;
        GLuint selectBuff[512];
        glSelectBuffer(512,selectBuff);

        glRenderMode(GL_SELECT);
        glInitNames();
        glPushName(0);

        glPushMatrix();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT,viewport);
        gluPickMatrix(event->x(),(viewport[3]-event->y()),4.0,4.0,viewport);// x,y,largeur,longueur,viewport

        gluPerspective(70.,1.,2,2000.);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(0,4,5,
                  0,1.,0,
                  0,1,0);


        glLoadName(1);
        bid_->drawBidon();
        glPopMatrix();
        glFlush();
        hits = glRenderMode(GL_RENDER);
        MyGLWidget::processHits(hits,selectBuff);
    }
}
void MyGLWidget::processHits(GLint hits, GLuint *buffer){


    if (hits>0){
        qDebug()<<"Bidon picked ";
        pcar_->setoil((pcar_->getoil()+70));
        if(pcar_->getoil()>150)
            pcar_->setoil(150);

    }
    else{
        qDebug()<< "Bidon pas picked ";
    }
}


void MyGLWidget::detectcollision()
{
    float xcar,xene,zene;

    xcar=pcar_->gettransx();

    xene=ecar_->getposx();
    zene=ecar_->getposz();

    if (zene+1>=-1) //si l'enemi est au niveau du joueur
    {
        if ((xcar<=xene && xcar+0.6f>=xene-0.6f) || (xcar>=xene && xcar-0.6f<=xene+0.6f))
        {
            qDebug("Boom!!");
        }
    }

}
void MyGLWidget::updateDrawing(int direction){
    if(direction==1){
        pcar_->moveleft();

    }
    if(direction==2){
        pcar_->moveright();
    }

    update();
}
