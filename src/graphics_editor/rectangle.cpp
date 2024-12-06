#include "rectangle.h"
#include <QStyleOptionGraphicsItem>

Rectangle::Rectangle(qreal width, qreal height, const QBrush &fillColor, const QPen &borderColor, qreal radius)
    : Shape(), width(width), height(height), fillColor(fillColor), borderColor(borderColor), cornerRadius(radius) {}

QRectF Rectangle::boundingRect() const {
    return QRectF(0, 0, width, height);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setBrush(fillColor);
    painter->setPen(borderColor);

    // Если радиус округления углов больше 0, рисуем прямоугольник с округленными углами
    if (cornerRadius > 0) {
        drawRectangleWithRoundedCorners(painter);
    } else {
        painter->drawRect(boundingRect());  // Рисуем обычный прямоугольник
    }

    if (option->state & QStyle::State_Selected) {
        QPen selectedPen(Qt::black);
        selectedPen.setWidth(6);
        painter->setPen(selectedPen);

        if (cornerRadius > 0) {
            drawRectangleWithRoundedCorners(painter);
        } else {
            painter->drawRect(boundingRect());
        }
    }
}

void Rectangle::drawRectangleWithRoundedCorners(QPainter *painter) const {
    // Используем QPainterPath для рисования прямоугольника с округленными углами
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(boundingRect(), cornerRadius, cornerRadius);  // Добавляем прямоугольник с округленными углами
    painter->drawPath(path);
}
