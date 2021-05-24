#include <qopengl.h>
#include <math.h>
#include <QImage>
#include <QGLWidget>
#include<GL/glu.h>

// Classe dediee pour la gestion du sol
class Ground
{
public:
    // Constructeur avec parametres
    Ground(float *speed);

    // Destructeur
    ~Ground();

    // Methode d'affichage
    void Display();
    void texture();


private:
    float* vitessep_=nullptr;
    float shift_=0;
     QImage Grass_ ;
     QImage Road_;
     GLuint* texture_;


};
