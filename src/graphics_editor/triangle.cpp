#include "triangle.h"
#include <QStyleOptionGraphicsItem>
#include <cmath>

Triangle::Triangle(qreal base, qreal height, TriangleType type, const QBrush &fillColor, const QPen &borderColor)
    : Shape(), base(base), height(height), type(type), fillColor(fillColor), borderColor(borderColor) {}

QRectF Triangle::boundingRect() const {
    return QRectF(-base / 2, -height, base, height);
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setBrush(fillColor);
    painter->setPen(borderColor);

    // Вычисляем точки для треугольника в зависимости от его типа
    QPolygonF triangle = calculatePoints();

    painter->drawPolygon(triangle);

    if (option->state & QStyle::State_Selected) {
        QPen selectedPen(Qt::black);
        selectedPen.setWidth(6);
        painter->setPen(selectedPen);
        painter->drawPolygon(triangle);
    }
}

// Метод для вычисления точек в зависимости от типа треугольника
QPolygonF Triangle::calculatePoints() const {
    QPolygonF points;

    switch (type) {
        case Isosceles: {
            // Равнобедренный треугольник
            points << QPointF(0, -this->height)  // Верхняя точка
                   << QPointF(-base / 2, 0)  // Левая точка
                   << QPointF(base / 2, 0);  // Правая точка
            break;
        }
        case Scalene: {
            // Разносторонний треугольник
            points << QPointF(0, -height)  // Верхняя точка
                   << QPointF(-base / 2, 0)  // Левая точка
                   << QPointF(base / 2, 0);  // Правая точка
            break;
        }
    }

    return points;
}
