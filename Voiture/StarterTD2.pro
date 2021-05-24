# configuration Qt
QT       += core gui opengl widgets
TEMPLATE  = app
CONFIG += c++17

# ajout des libs au linker
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib\

    } else {
        LIBS     += -lopengl32 -lglu32
    }
}
else {
        LIBS     += -lGL -lGLU
}

INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

LIBS += -L$$(OPENCV_DIR)\lib \
    -lopencv_core451 \
    -lopencv_highgui451 \
    -lopencv_imgproc451 \
    -lopencv_imgcodecs451 \
    -lopencv_videoio451 \
    -lopencv_features2d451 \
    -lopencv_calib3d451 \
    -lopencv_objdetect451


# nom de l'exe genere
TARGET 	  = StarterTD2

# fichiers sources/headers/ressources
SOURCES += main.cpp myglwidget.cpp \
    Car.cpp \
    Ground.cpp \
    appmanager.cpp \
    bidon.cpp \
    imageprocessing.cpp \
    ui.cpp
HEADERS += myglwidget.h \
    Car.h \
    Ground.h \
    appmanager.h \
    bidon.h \
    imageprocessing.h \
    ui.h

RESOURCES += \
    res/textures.qrc

DISTFILES +=

