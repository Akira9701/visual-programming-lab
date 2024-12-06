#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "movableshape.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QPainterPath>

class Rectangle : public Shape {
public:
    Rectangle(qreal width, qreal height, const QBrush &fillColor, const QPen &borderColor, qreal radius = 0);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;

    qreal getCornerRadius() const { return cornerRadius; }

private:
    qreal width;
    qreal height;
    QBrush fillColor;
    QPen borderColor;
    qreal cornerRadius;    // Радиус округления углов

    // Метод для рисования прямоугольника с округленными углами
    void drawRectangleWithRoundedCorners(QPainter *painter) const;
};

#endif // RECTANGLE_H
