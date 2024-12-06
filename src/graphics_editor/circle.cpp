#include "circle.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

Circle::Circle(qreal radius, const QPointF &center, const QBrush &fillColor, const QPen &borderColor)
    : Shape(), radius(radius), center(center), fillColor(fillColor), borderColor(borderColor) {}

QRectF Circle::boundingRect() const {
    return QRectF(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setBrush(fillColor);
    painter->setPen(borderColor);

    painter->drawEllipse(center, radius, radius);

    // Если элемент выбран, рисуем толстую черную рамку
    if (option->state & QStyle::State_Selected) {
        QPen selectedPen(Qt::black);
        selectedPen.setWidth(6);
        painter->setPen(selectedPen);
        painter->drawEllipse(center, radius, radius);
    }
}
