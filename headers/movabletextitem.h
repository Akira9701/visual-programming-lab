#ifndef MOVABLETEXTITEM_H
#define MOVABLETEXTITEM_H

#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>

class MovableTextItem : public QGraphicsTextItem {
public:
    // Конструктор
    MovableTextItem(const QString &text, QGraphicsItem *parent = nullptr);

protected:
    // Переопределение событий мыши
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    bool isMoving;              // Флаг, указывающий, перемещается ли элемент
    QPointF lastMousePosition;  // Последняя позиция мыши для расчета смещения
};

#endif // MOVABLETEXTITEM_H
