#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class Shape : public QGraphicsItem {
public:
    Shape();
    virtual ~Shape() = default;

    // Переопределяем виртуальные функции для рисования
    virtual QRectF boundingRect() const override = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

protected:
    // Общие события для перемещения
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool isMoving;  // Флаг для отслеживания состояния перемещения
    QPointF lastMousePosition;  // Последняя позиция мыши
};

#endif // SHAPE_H
