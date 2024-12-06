#ifndef CIRCLE_H
#define CIRCLE_H

#include "movableshape.h"
#include <QGraphicsItem>

class Circle : public Shape {
public:
    Circle(qreal radius, const QPointF &center, const QBrush &fillColor, const QPen &borderColor);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    qreal radius;
    QPointF center;
    QBrush fillColor;
    QPen borderColor;
};

#endif // CIRCLE_H
