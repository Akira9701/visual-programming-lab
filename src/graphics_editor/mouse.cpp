#include "mouse.h"
#include <QBrush>
#include <QPen>
#include <QColor>
#include <QPolygonF>
#include <cmath>

Mouse::Mouse() : CompositeObject() {
    QColor gray(169, 169, 169); // Серый цвет для тела
    QColor pink(255, 182, 193); // Розовый цвет для ушей и носа
    QColor black(0, 0, 0);      // Черный цвет для глаз и контура

    // Тело мыши
    QGraphicsEllipseItem* body = new QGraphicsEllipseItem(-50, -30, 100, 60);
    body->setBrush(QBrush(gray));
    body->setPen(QPen(Qt::black));
    addItem(body);

    // Голова мыши
    QGraphicsEllipseItem* head = new QGraphicsEllipseItem(-30, -60, 60, 60);
    head->setBrush(QBrush(gray));
    head->setPen(QPen(Qt::black));
    addItem(head);

    // Левое ухо
    QGraphicsEllipseItem* leftEar = new QGraphicsEllipseItem(-50, -90, 40, 40);
    leftEar->setBrush(QBrush(pink));
    leftEar->setPen(QPen(Qt::black));
    addItem(leftEar);

    // Правое ухо
    QGraphicsEllipseItem* rightEar = new QGraphicsEllipseItem(10, -90, 40, 40);
    rightEar->setBrush(QBrush(pink));
    rightEar->setPen(QPen(Qt::black));
    addItem(rightEar);

    // Левый глаз
    QGraphicsEllipseItem* leftEye = new QGraphicsEllipseItem(-20, -50, 10, 10);
    leftEye->setBrush(QBrush(black));
    addItem(leftEye);

    // Правый глаз
    QGraphicsEllipseItem* rightEye = new QGraphicsEllipseItem(10, -50, 10, 10);
    rightEye->setBrush(QBrush(black));
    addItem(rightEye);

    // Нос
    QGraphicsEllipseItem* nose = new QGraphicsEllipseItem(-5, -35, 10, 10);
    nose->setBrush(QBrush(pink));
    nose->setPen(QPen(Qt::black));
    addItem(nose);

    // Хвост мыши
    QGraphicsPolygonItem* tail = new QGraphicsPolygonItem();
    QPolygonF tailShape;
    tailShape << QPointF(50, 0) << QPointF(80, 10) << QPointF(90, 0) << QPointF(80, -10);
    tail->setPolygon(tailShape);
    tail->setBrush(QBrush(gray));
    tail->setPen(QPen(Qt::black));
    addItem(tail);
}
