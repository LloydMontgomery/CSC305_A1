#ifndef POLYGON_H
#define POLYGON_H

#include <QVector3D>
#include <QVector>

class Polygon
{
public:
    Polygon(QVector3D vertex);
    ~Polygon();

private:
    QVector<QVector3D> vertices;
};

#endif // POLYGON_H
