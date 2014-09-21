#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

class Vertex
{
public:
    Vertex(qreal x, qreal y);
    ~Vertex();
    void setX(qreal x);
    void setY(qreal y);
    qreal getX();
    qreal getY();

private:
    QVector3D position;
};

#endif // VERTEX_H
