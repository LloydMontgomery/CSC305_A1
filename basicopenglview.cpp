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
    viewportScale.setToIdentity();
    viewportScaling = true;
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
    drawFigure();
}

void BasicOpenGLView::mousePressEvent(QMouseEvent *e)
{

    if (mousedown) return;
    mousedown = true;
    csv = NULL;

    QVector3D invClick = inverseClick(QVector3D(e->x(), height()-e->y(), 1));
    if (e->button() == Qt::RightButton)
        addPoint( invClick.x(), invClick.y() );
    if (e->button() == Qt::LeftButton)
        movePoint( invClick.x(), invClick.y() );
    update();
}

void BasicOpenGLView::mouseMoveEvent(QMouseEvent *e)
{
    QVector3D invClick = inverseClick(QVector3D(e->x(), height()-e->y(), 1));
    if (mousedown)
        movePoint( invClick.x(), invClick.y() );
    update();
}

void BasicOpenGLView::mouseReleaseEvent(QMouseEvent *e)
{
    // finished move point
    QVector3D invClick = inverseClick(QVector3D(e->x(), height()-e->y(), 1));
    movePoint( invClick.x(), invClick.y() );
    mousedown = false;
    if (viewportScaling)
        scaleViewport();
    update();
}

void BasicOpenGLView::movePoint(int invX, int invY)
{
    if (mousedown) {
        if (csv == NULL)    // If no vertex selected
            select(invX, invY);  // Look for vertex selected
        if (csv != NULL) {  // If vertex selected
            csv->setX(invX);
            csv->setY(invY);
        }
    }
}

void BasicOpenGLView::addPoint(int invX, int invY)
{
    for (int i = 0; i < polygons.size(); i++) {
        if ( polygons.at(i).size() > 0 \
             && ( (polygons.at(i).at(0).x()-RADIUS) < invX && (polygons.at(i).at(0).x()+RADIUS) > invX )
             && ( (polygons.at(i).at(0).y()-RADIUS) < invY && (polygons.at(i).at(0).y()+RADIUS) > invY ) ) {
            newPoly();
            return;
        }
    }
    polygons.last().append(QVector3D(invX, invY, 1));
}

void BasicOpenGLView::select(int invX, int invY)
{
    for (int i = 0; i < polygons.size(); i++) {
        for (int j = 0; j < polygons.at(i).size(); j++) {
            if (   ( (polygons.at(i).at(j).x()-RADIUS) < invX && (polygons.at(i).at(j).x()+RADIUS) > invX )
                && ( (polygons.at(i).at(j).y()-RADIUS) < invY && (polygons.at(i).at(j).y()+RADIUS) > invY ) ) {
                csv = &(polygons[i][j]);
            }
        }
    }
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

void BasicOpenGLView::drawFigure()
{
    // draw a line between each pair of points
    int x0,x1,y0,y1,i,j, firstX, firstY;
    int numPolys = polygons.size();
    QVector3D visVert;

    for (i = 0; i < numPolys; i++)
    {
        glColor3f(polyColors[i][0], polyColors[i][1], polyColors[i][2]);
        if (polygons.at(i).size() <= 1)
            ;
        else
        {
            visVert = visualVertex(polygons.at(i).at(0));

            firstX = visVert.x();
            firstY = visVert.y();
            x0 = firstX;
            y0 = firstY;

            for (j = 1; j < polygons.at(i).size(); j++) {
                visVert = visualVertex(polygons.at(i).at(j));
                x1 = visVert.x();
                y1 = visVert.y();
                drawLine(x0, y0, x1, y1);
                x0 = x1;  y0 = y1;

            }

            // If this is a closed polygon, draw the last line
            if (i != (numPolys - 1))
                drawLine(x1, y1, firstX, firstY);
        }

        for (j = 0; j < polygons.at(i).size(); j++){
            visVert = visualVertex(polygons.at(i).at(j));
            drawCircle( (double)RADIUS, visVert.x(), visVert.y(), false);
        }
    }
}

/* ********************** PUBLIC SLOTS ********************** */

void BasicOpenGLView::newPoly() {
    polygons.append(QVector<QVector3D>());
    polyColors.append(QVector<double>(3));
    polyColors.last()[0] = ((double) rand() / (RAND_MAX));
    polyColors.last()[1] = ((double) rand() / (RAND_MAX));
    polyColors.last()[2] = ((double) rand() / (RAND_MAX));
    update();
}

void BasicOpenGLView::clearPolys()
{
    polygons.clear();
    polyColors.clear();
    viewportScale.setToIdentity();
    newPoly();
    update();
}

void BasicOpenGLView::toggleMatrices(bool toggle)
{
    transform = toggle;
    if (viewportScaling)
        scaleViewport();
    update();
}

void BasicOpenGLView::toggleViewportScaling(bool scale)
{
    viewportScaling = scale;
    if (viewportScaling)
        scaleViewport();
    update();
}

/* ******************** PUBLIC FUNCTIONS ******************** */

void BasicOpenGLView::pushMatrix(QMatrix3x3 newMatrix) {
    stack.push(newMatrix*stack.top());
    if (viewportScaling)
        scaleViewport();
    update();
}

void BasicOpenGLView::popMatrix() {
    stack.pop();
    if (viewportScaling)
        scaleViewport();
    update();
}

void BasicOpenGLView::newStack() {
    QMatrix3x3 ident = QMatrix3x3();
    ident.setToIdentity();
    stack.push(ident);
}

void BasicOpenGLView::clearStack()
{
    stack.clear();
    newStack();
    if (viewportScaling)
        scaleViewport();
    update();
}

/* ******************** PRIVATE FUNCTIONS ******************** */

QVector3D BasicOpenGLView::visualVertex(QVector3D result) {
    if (transform && viewportScaling)
        result = vectorTransform(result, (viewportScale * stack.top()));
    else if (transform)
        result = vectorTransform(result, stack.top());
    else if (viewportScaling)
        result = vectorTransform(result, viewportScale);
    return result;
}

QVector3D BasicOpenGLView::inverseClick(QVector3D result) {
    if (transform && viewportScaling)
        result = vectorTransform(result, invertMatrix((viewportScale * stack.top())));
    else if (transform)
        result = vectorTransform(result, invertMatrix(stack.top()));
    else if (viewportScaling)
        result = vectorTransform(result, invertMatrix(viewportScale));
    return result;
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
        (orig.operator()(0,0) * ((orig.operator()(1,1) * orig.operator()(2,2)) - (orig.operator()(1,2) * orig.operator()(2,1)))) - \
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

void BasicOpenGLView::scaleViewport() {
    if (polygons.at(0).size() == 0)  // nothing on the screen
        return;

    int i, j;
    double minX, maxX, minY, maxY;
    QVector3D visVert;

    for (int itter = 0; itter < 2; itter++) {
        // set mins and maxs to a point on the screen
        minX = visualVertex(polygons.at(0).at(0)).x();
        maxX = minX;
        minY = visualVertex(polygons.at(0).at(0)).y();
        maxY = minY;

        if ( itter == 1 )
            viewportScaling = false;
        // Set mins and maxes
        for (i = 0; i < polygons.size(); i++) {
            for (j = 0; j < polygons.at(i).size(); j++) {
               visVert = visualVertex(polygons.at(i).at(j));
               if (visVert.x() < minX) minX = visVert.x();
               else if (visVert.x() > maxX) maxX = visVert.x();
               if (visVert.y() < minY) minY = visVert.y();
               else if (visVert.y() > maxY) maxY = visVert.y();
            }
        }
        if ( itter == 1 )
            viewportScaling = true;

        // If all points are within the viewport, then exit
        if ( itter == 0 )
            if (minX >= 0 &&  minY >= 0 && maxX <= width() && maxY <= height())
                return;
    }


    double scale;
    if (((maxX-minX) - width()) > ((maxY-minY) - height()))
        scale = (width() / (maxX-minX));
    else
        scale = (height() / (maxY-minY));

    double elems1[] = {1, 0, -(minX - 5), 0, 1, -(minY - 5), 0, 0, 1};
    double elems2[] = {scale*.9, 0, 0, 0, scale*.9, 0, 0, 0, 1};  // scale to bring all elements into the viewport

    qDebug() << QMatrix3x3(elems1);
    qDebug() << QMatrix3x3(elems2);
    viewportScale.setToIdentity();
    viewportScale = viewportScale * (QMatrix3x3(elems2) * QMatrix3x3(elems1));
}
