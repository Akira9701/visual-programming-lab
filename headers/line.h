#ifndef LINE_H
#define LINE_H

#include "movableshape.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QLineF>

class Line : public Shape {
public:
    enum LineType {
        Solid,   // Сплошная линия
        Dashed,  // Пунктирная линия
        Dotted   // Точечная линия
    };

    Line(const QPointF &start, const QPointF &end, LineType type, const QPen &pen);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;

private:
    QPointF start;     // Начальная точка
    QPointF end;       // Конечная точка
    LineType type;     // Тип линии
    QPen pen;          // Карандаш для рисования

    void applyLineStyle(QPainter *painter) const;  // Метод для применения стиля линии
};

#endif // LINE_H
