#include "flower.h"
#include <QBrush>
#include <QPen>
#include <QColor>
#include <cmath>

Flower::Flower() : CompositeObject() {
    QColor yellow(255, 223, 0);
    QColor red(255, 0, 0);
    // Центр цветка
    QGraphicsEllipseItem* center = new QGraphicsEllipseItem(-20, 20, 40, 40);
    center->setBrush(QBrush(yellow));
    center->setPen(QPen(Qt::black));
    addItem(center);

    const int petalWidth = 30;
    const int petalHeight = 60;
    const int radius = 10;
    const int petalCount = 7;

    for (int i = 0; i < petalCount; ++i) {
        double angle = (360.0 / petalCount) * i;
        QGraphicsEllipseItem* petal = new QGraphicsEllipseItem(-petalWidth / 2, -radius - petalHeight / 2, petalWidth, petalHeight);
        petal->setBrush(QBrush(red));
        petal->setPen(QPen(Qt::black));
        petal->setTransformOriginPoint(0, radius + petalHeight / 2);
        petal->setRotation(angle);

        addItem(petal);
    }
}
