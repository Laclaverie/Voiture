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


private:
    GLuint* texture;
    float* vitessep_=nullptr;
    float shift_=0;


};
