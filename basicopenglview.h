#ifndef BASICOPENGLVIEW_H
#define BASICOPENGLVIEW_H

#include <QGLWidget>
#include <math.h>
#include <QtDebug>
#include "foundation.h"
#include <QVector>
#include <QVector3D>
#include <stdlib.h>
#include <time.h>
#include <QGenericMatrix>
#include <QStack>

#define MAXPTS 300
#define RADIUS 8  // circle around a point for selection

typedef    QVector<QVector3D>  vecs;

/**
  * @class  BasicOpenGLView
  * @brief  our OpenGL view derived from QGLWidget.
  * We have to override several functions for our
  * application-specific OpenGL drawing functionality
  */
class BasicOpenGLView : public QGLWidget
{
    /**
      * macro needed to be inserted in every QT derived class.
      */
    Q_OBJECT
public:

    /**
      * our constructor
      * @param  parent the parent object of the widget.
                pass this one on to the superclass constructor
      */
    explicit BasicOpenGLView(QWidget *parent = 0);
    void pushMatrix(QMatrix3x3);
    void popMatrix();
    void newStack();
    QStack<QMatrix3x3> stack;
    bool transform;

signals:

public slots:
    void newPoly();
    void clearPolys();
    void clearStack();
    void scaleViewport();

protected:

    /**
      * function called automatically by QT after the OpenGL context is created
      * in here, do all OpenGL setup stuff, that you can before the actual program
      * execution starts
      */
    void initializeGL();

    /**
      * the function called whenever our Widget is being redrawn.
      * assume that the BasicOpenGLView's OpenGL context has already
      * been made the current one, so no need to call
      * this->makeCurrent(); anymore
      * Do all your rendering loop related code in there
      */
    void paintGL();

    /**
      * method called when the widget is resized.
      * we need code in there, to react to the changed window size
      * otherwise the rendering will look skewed and ugly
      */
    void resizeGL(int width, int height);

    /**
      * function called when a mouse button is pressed and the cursor is hovering
      * over our widget
      * use the QMouseEvent classmembers to access the mouse information
      */
    void mousePressEvent(QMouseEvent *event);

    /**
      * function called when mouse cursor is moved inside our widgets region
      * use the QMouseEvent classmembers to access the mouse information
      */
    void mouseMoveEvent(QMouseEvent *event);

    /**
      * function called when a mouse button is released and the cursor is hovering
      * over our widget
      * use the QMouseEvent classmembers to access the mouse information
      */
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool mousedown;

    void movePoint(int x, int y);
    void addPoint(int x,  int y);
    void select(int x, int y);

    bool  drawon, permittransform;
    void drawFigure();
    void drawCircle(double radius, double xcen, double ycen, bool line);
    void drawLine(double x0, double y0, double x1, double y1 );

    /* Additional Variables */
    QVector< QVector<QVector3D> > polygons;
    QVector< QVector<double> > polyColors;
    QVector3D * csv;  // The current selected vertex.  Set to null if none selected
    QMatrix3x3 viewportScale;

    /* Additional Functions */
    QVector3D vectorTransform(QVector3D v, QMatrix3x3 m);
    QMatrix3x3 invertMatrix(QMatrix3x3 orig);

};

#endif // BASICOPENGLVIEW_H
