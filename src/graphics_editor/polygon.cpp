#include "polygon.h"
#include <QStyleOptionGraphicsItem>
#include <cmath>

Polygon::Polygon(int sides, qreal radius, const QBrush &fillColor, const QPen &borderColor)
    : Shape(), sides(sides), radius(radius), fillColor(fillColor), borderColor(borderColor) {}

QRectF Polygon::boundingRect() const {
    return QRectF(-radius, -radius, 2 * radius, 2 * radius);  // Ограничивающий прямоугольник
}

void Polygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setBrush(fillColor);
    painter->setPen(borderColor);

    // Вычисляем точки для многоугольника
    QPolygonF polygon = calculatePoints();

    painter->drawPolygon(polygon);

    if (option->state & QStyle::State_Selected) {
        QPen selectedPen(Qt::black);
        selectedPen.setWidth(6);
        painter->setPen(selectedPen);
        painter->drawPolygon(polygon);
    }
}

// Метод для вычисления точек многоугольника
QPolygonF Polygon::calculatePoints() const {
    QPolygonF points;

    // Угловой шаг для многоугольника
    qreal angleStep = 2 * M_PI / sides;

    for (int i = 0; i < sides; ++i) {
        qreal angle = i * angleStep;
        qreal x = radius * cos(angle);
        qreal y = radius * sin(angle);
        points << QPointF(x, y);
    }

    return points;
}
