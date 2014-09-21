#include "vertex.h"

Vertex::Vertex(qreal x, qreal y) : position(QVector3D(x, y, 1)) {}

Vertex::~Vertex() {}

void Vertex::setX(qreal x) {
    position.setX(x);
}

void Vertex::setY(qreal y) {
    position.setY(y);
}

qreal Vertex::getX() {
    return position.x();
}

qreal Vertex::getY() {
    return position.y();
}
