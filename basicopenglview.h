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
    void clearStack();
    QStack<QMatrix3x3> stack;

signals:

public slots:

    /* void newPoly();
     *
     * Creates a new polygon by closing the last one
     */
    void newPoly();

    /* void clearPolys();
     *
     * Clears all of the polygons on the screen
     */
    void clearPolys();

    /* void toggleMatrices(bool toggle);
     *
     * sets the global transform to true of false
     */
    void toggleMatrices(bool toggle);

    /* void toggleViewportScaling(bool scale);
     *
     * sets the global viewportScaling to true or false
     */
    void toggleViewportScaling(bool scale);

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

    void movePoint(int invX, int invY);
    void addPoint(int invX,  int invY);
    void select(int invX, int invY);
    void drawFigure();
    void drawCircle(double radius, double xcen, double ycen, bool line);
    void drawLine(double x0, double y0, double x1, double y1 );

    /* Additional Variables */
    QVector< QVector<QVector3D> > polygons; // All the polygons (sets of points) are stored here
    QVector< QVector<double> > polyColors;  // All the polgons have separate colours, stored here
    QVector3D * csv;                        // The current selected vertex.  Set to null if none selected
    QMatrix3x3 viewportScale;               // The matrix that gets all polygons back onto the screen
    bool viewportScaling;                   // True if user wants to scale down/up to viewport
    bool transform;                         // True if user wants to apply transformation matrix

    /* Additional Functions */

    /* QVector3D vectorTransform(QVector3D v, QMatrix3x3 m);
     *
     * Given a vector v and a 3x3 matrix m, computes m*v
     */
    QVector3D vectorTransform(QVector3D v, QMatrix3x3 m);

    /* QMatrix3x3 invertMatrix(QMatrix3x3 orig);
     *
     * given a 3x3 matrix orig, inverts the matrix
     */
    QMatrix3x3 invertMatrix(QMatrix3x3 orig);

    /* void scaleViewport();
     *
     * Scales all of the points on the screen so that they fit within the current viewport
     */
    void scaleViewport();

    /* QVector3D visualVertex(QVector3D result);
     *
     * Given a QVector3D that is a polygon point in memory, visualVertex will return
     * a QVector3D that is the visual location of that vertex.  This is needed because
     * I am storing the vertices in their absolute locations, regardless of transforms,
     * and displaying them with the transforms applied.
     */
    QVector3D visualVertex(QVector3D result);

    /* QVector3D inverseClick(QVector3D result);
     *
     * Given a QVector3D that represents where the user clicked, visualVertex will
     * return a QVector3D that has the inverted coordinates of the system.  Which means,
     * I apply the inverse marix of the matrix stack, as well as the inverse of the viewport
     * matrix, and then return that point.  This is needed because when you click to add
     * a new point, it needs to be added at the inverse of where it will be drawn, so it ends
     * up back underneath the mouse cursor.
     *
     */
    QVector3D inverseClick(QVector3D result);

};

#endif // BASICOPENGLVIEW_H
