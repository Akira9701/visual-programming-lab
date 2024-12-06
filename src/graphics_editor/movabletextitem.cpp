#include "movabletextitem.h"

// Конструктор
MovableTextItem::MovableTextItem(const QString &text, QGraphicsItem *parent)
    : QGraphicsTextItem(text, parent), isMoving(false) {
    setFlag(QGraphicsItem::ItemIsSelectable); // Позволяет выделять текст
}

// Обработка нажатия мыши
void MovableTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        isMoving = true;
        lastMousePosition = event->scenePos();  // Запоминаем позицию при нажатии
        event->accept();  // Принимаем событие
    } else {
        QGraphicsTextItem::mousePressEvent(event); // Для других кнопок — стандартная обработка
    }
}

// Обработка перемещения мыши
void MovableTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (isMoving) {
        QPointF offset = event->scenePos() - lastMousePosition;  // Рассчитываем смещение
        setPos(pos() + offset);  // Перемещаем текст
        lastMousePosition = event->scenePos();  // Обновляем позицию
    } else {
        QGraphicsTextItem::mouseMoveEvent(event); // Стандартная обработка
    }
}

// Обработка отпускания кнопки мыши
void MovableTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        isMoving = false;  // Завершаем перемещение
        event->accept();
    } else {
        QGraphicsTextItem::mouseReleaseEvent(event); // Стандартная обработка
    }
}

// Обработка двойного нажатия левой кнопкой мыши
void MovableTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setTextInteractionFlags(Qt::TextEditorInteraction); // Активируем редактирование текста
        setFlag(QGraphicsItem::ItemIsMovable, false);        // Отключаем перемещение при редактировании
    }
    QGraphicsTextItem::mouseDoubleClickEvent(event); // Стандартная обработка
}
