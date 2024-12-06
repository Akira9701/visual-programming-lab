#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "movableshape.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QPolygonF>

class Triangle : public Shape {
public:
    enum TriangleType {
        Isosceles,    // Равнобедренный
        Scalene       // Разносторонний
    };

    Triangle(qreal base, qreal height, TriangleType type, const QBrush &fillColor, const QPen &borderColor);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;

private:
    qreal base;
    qreal height;
    TriangleType type;
    QBrush fillColor;
    QPen borderColor;

    QPolygonF calculatePoints() const;  // Метод для вычисления вершин треугольника
};

#endif // TRIANGLE_H
