#ifndef POLYGON_H
#define POLYGON_H

#include "movableshape.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QPolygonF>

class Polygon : public Shape {
public:
    Polygon(int sides, qreal radius, const QBrush &fillColor, const QPen &borderColor);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;

private:
    int sides;         // Количество сторон многоугольника
    qreal radius;
    QBrush fillColor;
    QPen borderColor;

    QPolygonF calculatePoints() const;
};

#endif // POLYGON_H
