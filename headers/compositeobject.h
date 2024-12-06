#ifndef COMPLEXOBJECT_H
#define COMPLEXOBJECT_H
#include "movableshape.h"
#include <QGraphicsItem>
#include <QList>
#include <QTimer>
#include <QGraphicsView>
#include <QSoundEffect>
#include <QMediaPlayer>

class CompositeObject : public Shape
{
public:
    CompositeObject();
    ~CompositeObject();

    void addItem(QGraphicsItem* item);
    void removeItem(QGraphicsItem* item);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void move(QGraphicsView *view);

private:
    QList<QGraphicsItem*> items;
    qreal dx;
    qreal dy;
    QSoundEffect collisionSound;

    void handleBoundaryCollision(const QRectF &viewRect, const QRectF &objectRect);
    void handleItemCollision(QGraphicsItem *item);
    void playCollisionSound();
};

#endif // COMPLEXOBJECT_H
