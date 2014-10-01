#include "basicopenglview.h"


BasicOpenGLView::BasicOpenGLView(QWidget *parent)
      : QGLWidget(parent), polygons(QVector< QVector<QVector3D> >())
{
    mousedown = false;
    csv = NULL;  // represents an unselected vertex
    stack = QStack<QMatrix3x3>();

    srand (time(NULL));  // Set the random seed
    newPoly();
    newStack();
    transform = true;
}

void BasicOpenGLView::initializeGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // white
    glShadeModel( GL_FLAT );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glPointSize(5);
}

void BasicOpenGLView::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,GLdouble(width),0,GLdouble(height),-10.0,10.0);

    glMatrixMode(GL_MODELVIEW);
}

void BasicOpenGLView::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawFigure(transform);
}


void BasicOpenGLView::mousePressEvent(QMouseEvent *e)
{

    if (mousedown) return;
    mousedown = true;
    csv = NULL;

    if (e->button() == Qt::RightButton)
        addPoint( e->x(), height()-e->y() );
    if (e->button() == Qt::LeftButton)
        movePoint(e->x(), height()-e->y() );
    update();
}

void BasicOpenGLView::mouseMoveEvent(QMouseEvent *e)
{
    if (mousedown) movePoint(e->x(), height()-e->y());
    update();
}

void BasicOpenGLView::mouseReleaseEvent(QMouseEvent *e)
{
    // finished move point
    movePoint(e->x(), height()-e->y());
    mousedown = false;
    update();
}

void BasicOpenGLView::movePoint(int x, int y)
{
    if (transform) {
        QVector3D invPoint = vectorTransform(QVector3D(x, y, 1), invertMatrix(stack.top()));
        if (mousedown) {
            if (csv == NULL)    // If no vertex selected
                select(x, y);  // Look for vertex selected
            if (csv != NULL) {  // If vertex selected
                csv->setX(invPoint.x());
                csv->setY(invPoint.y());
            }
        }
    }
    else {
        if (mousedown) {
            if (csv == NULL)    // If no vertex selected
                select(x, y);  // Look for vertex selected
            if (csv != NULL) {  // If vertex selected
                csv->setX(x);
                csv->setY(y);
            }
        }
    }
}

void BasicOpenGLView::addPoint(int x, int y)
{
    int i;
    if (transform) {
        QVector3D invPoint = vectorTransform(QVector3D(x, y, 1), invertMatrix(stack.top()));
        for (i = 0; i < polygons.size(); i++) {
            if ( polygons.at(i).size() > 0 && ( (polygons.at(i).at(0).x()-RADIUS) < invPoint.x() && (polygons.at(i).at(0).x()+RADIUS) > invPoint.x() )
                                           && ( (polygons.at(i).at(0).y()-RADIUS) < invPoint.y() && (polygons.at(i).at(0).y()+RADIUS) > invPoint.y() ) ) {
                newPoly();
                return;
            }
        }
        polygons.last().append(QVector3D(invPoint.x(), invPoint.y(), 1));
    }
    else {
        for (i = 0; i < polygons.size(); i++) {
            if ( polygons.at(i).size() > 0 && ( (polygons.at(i).at(0).x()-RADIUS) < x && (polygons.at(i).at(0).x()+RADIUS) > x )
                                           && ( (polygons.at(i).at(0).y()-RADIUS) < y && (polygons.at(i).at(0).y()+RADIUS) > y ) ) {
                newPoly();
                return;
            }
        }
        polygons.last().append(QVector3D(x, y, 1));
    }
}

void BasicOpenGLView::select(int x, int y)
{
    int i, j;
    if (transform) {
        QVector3D invPoint = vectorTransform(QVector3D(x, y, 1), invertMatrix(stack.top()));
        for (i = 0; i < polygons.size(); i++) {
            for (j = 0; j < polygons.at(i).size(); j++) {
                if (   ( (polygons.at(i).at(j).x()-RADIUS) < invPoint.x() && (polygons.at(i).at(j).x()+RADIUS) > invPoint.x() )
                    && ( (polygons.at(i).at(j).y()-RADIUS) < invPoint.y() && (polygons.at(i).at(j).y()+RADIUS) > invPoint.y() ) ) {
                    csv = &(polygons[i][j]);
                }
            }
        }
    }
    else {
        for (i = 0; i < polygons.size(); i++) {
            for (j = 0; j < polygons.at(i).size(); j++) {
                if (   ( (polygons.at(i).at(j).x()-RADIUS) < x && (polygons.at(i).at(j).x()+RADIUS) > x )
                    && ( (polygons.at(i).at(j).y()-RADIUS) < y && (polygons.at(i).at(j).y()+RADIUS) > y ) ) {
                    csv = &(polygons[i][j]);
                }
            }
        }
    }
}

void BasicOpenGLView::clearPolys()
{
    //for (int i = 0; i < polygons.size(); i++)
    //    polygons.at(i).clear();
    // THIS IS NOT A DEEP CLEAR, FIX THIS
    polygons.clear();
    polyColors.clear();
    newPoly();
    update();
}

void BasicOpenGLView::clearStack()
{
    stack.clear();
    newStack();

    update();
}

void BasicOpenGLView::drawCircle(double radius, double xcen, double ycen, bool line)
{
   GLint i;
   static GLfloat circcoords[100][2];

   for(i=0;i<100;i++) {
     circcoords[i][0]=radius*cos(i*2*M_PI/100.0)+xcen;
     circcoords[i][1]=radius*sin(i*2*M_PI/100.0)+ycen;
   }
   if (line)   glBegin(GL_LINES); else glBegin(GL_POLYGON);
      for(i=0;i<100;i++)
         glVertex2fv(&circcoords[i][0]);
   glEnd();
}

void BasicOpenGLView::drawLine(double x0, double y0, double x1, double y1 )
{
    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);
    glEnd();
}

void BasicOpenGLView::drawFigure(bool transform)
{
    // draw a line between each pair of points
    int x0,x1,y0,y1,i,j, firstX, firstY;
    int numPolys = polygons.size();
    QVector3D transformed;

    for (i = 0; i < numPolys; i++)
    {
        glColor3f(polyColors[i][0], polyColors[i][1], polyColors[i][2]);
        if (polygons.at(i).size() <= 1)
            ;
        else
        {
            if (transform) {
                transformed = vectorTransform(polygons.at(i).at(0), stack.top());
                firstX = transformed.x();
                firstY = transformed.y();
                x0 = firstX;
                y0 = firstY;

                for (j = 1; j < polygons.at(i).size(); j++) {
                    transformed = vectorTransform(polygons.at(i).at(j), stack.top());
                    x1 = transformed.x();
                    y1 = transformed.y();
                    drawLine(x0, y0, x1, y1);
                    x0 = x1;  y0 = y1;
                }
            }
            else {
                firstX = polygons.at(i).at(0).x();
                firstY = polygons.at(i).at(0).y();
                x0 = firstX;
                y0 = firstY;

                for (j = 1; j < polygons.at(i).size(); j++) {
                    x1 = polygons.at(i).at(j).x();
                    y1 = polygons.at(i).at(j).y();
                    drawLine(x0, y0, x1, y1);
                    x0 = x1;  y0 = y1;
                }
            }

            // If this is a closed polygon, draw the last line
            if (i != (numPolys - 1))
                drawLine(x1, y1, firstX, firstY);
        }

        if (transform) {
            for (j = 0; j < polygons.at(i).size(); j++){
                transformed = vectorTransform(polygons.at(i).at(j), stack.top());
                drawCircle( (double)RADIUS, transformed.x(), transformed.y(), false);
            }
        }
        else {
            for (j = 0; j < polygons.at(i).size(); j++){
                drawCircle( (double)RADIUS, polygons.at(i).at(j).x(), polygons.at(i).at(j).y(), false);
            }
        }
    }
}

QVector3D BasicOpenGLView::vectorTransform(QVector3D v, QMatrix3x3 m)
{
    QVector3D transformed = QVector3D();
    transformed.setX( ((m.operator()(0,0))*v.x()) + ((m.operator()(0,1))*v.y()) + ((m.operator()(0,2))*v.z()) );
    transformed.setY( ((m.operator()(1,0))*v.x()) + ((m.operator()(1,1))*v.y()) + ((m.operator()(1,2))*v.z()) );
    transformed.setZ( ((m.operator()(2,0))*v.x()) + ((m.operator()(2,1))*v.y()) + ((m.operator()(2,2))*v.z()) );
    return transformed;
}

QMatrix3x3 BasicOpenGLView::invertMatrix(QMatrix3x3 orig)
{
    QMatrix3x3 inv = QMatrix3x3();
    double det = (\
        (orig.operator()(0,0) * ((orig.operator()(1,1) * orig.operator()(2,2)) - (orig.operator()(1,2) * orig.operator()(2,1)))) + \
        (orig.operator()(0,1) * ((orig.operator()(1,0) * orig.operator()(2,2)) - (orig.operator()(1,2) * orig.operator()(2,0)))) + \
        (orig.operator()(0,2) * ((orig.operator()(1,0) * orig.operator()(2,1)) - (orig.operator()(1,1) * orig.operator()(2,0)))) );

    inv.operator()(0,0) = (((orig.operator()(1,1) * orig.operator()(2,2)) - (orig.operator()(1,2) * orig.operator()(2,1))) / det);
    inv.operator()(1,0) = -(((orig.operator()(1,0) * orig.operator()(2,2)) - (orig.operator()(1,2) * orig.operator()(2,0))) / det);
    inv.operator()(2,0) = (((orig.operator()(1,0) * orig.operator()(2,1)) - (orig.operator()(1,1) * orig.operator()(2,0))) / det);

    inv.operator()(0,1) = -(((orig.operator()(0,1) * orig.operator()(2,2)) - (orig.operator()(0,2) * orig.operator()(2,1))) / det);
    inv.operator()(1,1) = (((orig.operator()(0,0) * orig.operator()(2,2)) - (orig.operator()(0,2) * orig.operator()(2,0))) / det);
    inv.operator()(2,1) = -(((orig.operator()(0,0) * orig.operator()(2,1)) - (orig.operator()(0,1) * orig.operator()(2,0))) / det);

    inv.operator()(0,2) = (((orig.operator()(0,1) * orig.operator()(1,2)) - (orig.operator()(0,2) * orig.operator()(1,1))) / det);
    inv.operator()(1,2) = -(((orig.operator()(0,0) * orig.operator()(1,2)) - (orig.operator()(0,2) * orig.operator()(1,0))) / det);
    inv.operator()(2,2) = (((orig.operator()(0,0) * orig.operator()(1,1)) - (orig.operator()(0,1) * orig.operator()(1,0))) / det);

    return inv;
}

void BasicOpenGLView::newPoly() {
    polygons.append(QVector<QVector3D>());
    polyColors.append(QVector<double>(3));
    polyColors.last()[0] = ((double) rand() / (RAND_MAX));
    polyColors.last()[1] = ((double) rand() / (RAND_MAX));
    polyColors.last()[2] = ((double) rand() / (RAND_MAX));
    update();
}

void BasicOpenGLView::newStack() {
    QMatrix3x3 ident = QMatrix3x3();
    ident.setToIdentity();
    stack.push(ident);
}

void BasicOpenGLView::pushMatrix(QMatrix3x3 newMatrix) {
    stack.push(newMatrix*stack.top());
    update();
}

void BasicOpenGLView::popMatrix() {
    stack.pop();
    update();
}

