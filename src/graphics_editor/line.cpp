#include "line.h"
#include <QStyleOptionGraphicsItem>
#include <QPen>

Line::Line(const QPointF &start, const QPointF &end, LineType type, const QPen &pen)
    : Shape(), start(start), end(end), type(type), pen(pen) {}

QRectF Line::boundingRect() const {
    // Возвращаем прямоугольник, который охватывает линию
    return QRectF(start, end).normalized();
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    applyLineStyle(painter);

    // Рисуем линию
    painter->drawLine(start, end);

    if (option->state & QStyle::State_Selected) {
        // Если объект выбран, рисуем его с толстой черной линией
        QPen selectedPen(Qt::black);
        selectedPen.setWidth(6);
        painter->setPen(selectedPen);
        painter->drawLine(start, end);
    }
}


void Line::applyLineStyle(QPainter *painter) const {
    // Создаем копию QPen, чтобы не изменять оригинальный pen
    QPen tempPen = pen;

    // Применяем стиль линии в зависимости от типа
    switch (type) {
        case Solid:
            painter->setPen(tempPen);  // Сплошная линия
            break;
        case Dashed:
            tempPen.setStyle(Qt::DashLine);  // Пунктирная линия
            painter->setPen(tempPen);
            break;
        case Dotted:
            tempPen.setStyle(Qt::DotLine);  // Точечная линия
            painter->setPen(tempPen);
            break;
    }
}

