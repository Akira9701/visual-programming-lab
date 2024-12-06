#include "compositeobject.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QSoundEffect>
#include <QDebug>

CompositeObject::CompositeObject() : dx(1), dy(1) {
    collisionSound.setSource(QUrl::fromLocalFile(":/music/Sound.wav"));
    collisionSound.setVolume(0.5);
}

CompositeObject::~CompositeObject() {
    qDeleteAll(items);
}

void CompositeObject::addItem(QGraphicsItem* item) {
    if (item) {
        items.append(item);
        item->setParentItem(this);
    }
}

void CompositeObject::removeItem(QGraphicsItem* item) {
    if (item && items.removeOne(item)) {
        delete item;
    }
}

QRectF CompositeObject::boundingRect() const {
    QRectF rect;
    for (const QGraphicsItem* item : items) {
        QRectF itemRect = item->mapToParent(item->boundingRect()).boundingRect();
        rect = rect.united(itemRect);
    }
    return rect;
}


void CompositeObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    for (QGraphicsItem* item : items) {
        if (item) {
            item->paint(painter, option, widget);
        }
    }
}


void CompositeObject::move(QGraphicsView *view) {
    if (!view) return;
    QGraphicsScene *scene = view->scene();
    if (!scene) return;
    setPos(x() + dx, y() + dy);

    QRectF viewRect = view->mapToScene(view->viewport()->rect()).boundingRect();
    QRectF objectRect = boundingRect().translated(pos());

    // Проверяем столкновения с границами сцены
    if (!viewRect.contains(objectRect)) {
        handleBoundaryCollision(viewRect, objectRect);
    }

    // Проверяем столкновения с другими объектами
    for (QGraphicsItem *item : scene->collidingItems(this)) {
        handleItemCollision(item);
    }
}


void CompositeObject::handleBoundaryCollision(const QRectF &viewRect, const QRectF &objectRect) {
    if (objectRect.left() < viewRect.left() || objectRect.right() > viewRect.right()) {
        dx = -dx;
    }
    if (objectRect.top() < viewRect.top() || objectRect.bottom() > viewRect.bottom()) {
        dy = -dy;
    }
    playCollisionSound();
}

void CompositeObject::handleItemCollision(QGraphicsItem *item) {
    if ((dynamic_cast<CompositeObject*>(item) || dynamic_cast<Shape*>(item)) && !items.contains(item)) {
        dx = -dx;
        dy = -dy;
        playCollisionSound();
    }
}

// Воспроизведение звука столкновения
void CompositeObject::playCollisionSound() {
    if (collisionSound.isLoaded()) {
        collisionSound.play();
    } else {
        qDebug() << "Ошибка: звук столкновения не загружен!";
    }
}
