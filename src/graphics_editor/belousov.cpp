#include "belousov.h"
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

Belousov::Belousov() : CompositeObject() {
    qreal x = 0;
    qreal y = 0;
    qreal spacing = 70;

    QBrush brush(Qt::black);
    QPen pen(Qt::black);
    pen.setWidth(2);

    // Буква "Б"
    {
        QGraphicsRectItem* topBar = new QGraphicsRectItem(x + 10, y, 40, 10);
        topBar->setBrush(brush);
        topBar->setPen(pen);
        addItem(topBar);


        QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x, y, 10, 60);
        verticalStem->setBrush(brush);
        verticalStem->setPen(pen);
        addItem(verticalStem);

        QGraphicsEllipseItem* bottomLoop = new QGraphicsEllipseItem(x + 10, y + 30, 40, 30);
        bottomLoop->setBrush(brush);
        bottomLoop->setPen(pen);
        addItem(bottomLoop);
    }

    x += spacing;

    // Буква "Е"
    {
        QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x, y, 10, 60);
        verticalStem->setBrush(brush);
        verticalStem->setPen(pen);
        addItem(verticalStem);

        QGraphicsRectItem* topBar = new QGraphicsRectItem(x + 10, y, 40, 10);
        topBar->setBrush(brush);
        topBar->setPen(pen);
        addItem(topBar);

        QGraphicsRectItem* middleBar = new QGraphicsRectItem(x + 10, y + 25, 30, 10);
        middleBar->setBrush(brush);
        middleBar->setPen(pen);
        addItem(middleBar);

        QGraphicsRectItem* bottomBar = new QGraphicsRectItem(x + 10, y + 50, 40, 10);
        bottomBar->setBrush(brush);
        bottomBar->setPen(pen);
        addItem(bottomBar);
    }

    x += spacing;

    // Буква "Л"
    {
        QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x, y, 10, 60);
        verticalStem->setBrush(brush);
        verticalStem->setPen(pen);
        addItem(verticalStem);

        QGraphicsRectItem* base = new QGraphicsRectItem(x + 10, y + 50, 40, 10);
        base->setBrush(brush);
        base->setPen(pen);
        addItem(base);
    }

    x += spacing;

    // Буква "О"
    {
        QGraphicsEllipseItem* oval = new QGraphicsEllipseItem(x, y, 50, 60);
        oval->setPen(pen);
        addItem(oval);
    }

    x += spacing;

    // Буква "У"
    {
        QGraphicsLineItem* leftDiagonal = new QGraphicsLineItem(x, y, x + 25, y + 40);
        leftDiagonal->setPen(pen);
        addItem(leftDiagonal);

        QGraphicsLineItem* rightStem = new QGraphicsLineItem(x + 25, y + 40, x + 25, y + 60);
        rightStem->setPen(pen);
        addItem(rightStem);

        QGraphicsLineItem* rightDiagonal = new QGraphicsLineItem(x + 25, y + 40, x + 50, y);
        rightDiagonal->setPen(pen);
        addItem(rightDiagonal);
    }

    x += spacing;

    // Буква "С"
    {
        QGraphicsEllipseItem* semicircle = new QGraphicsEllipseItem(x, y, 50, 60);
        semicircle->setPen(pen);
        semicircle->setStartAngle(30 * 16); // Начало дуги
        semicircle->setSpanAngle(300 * 16); // Длина дуги
        addItem(semicircle);
    }

    x += spacing;

    // Буква "О"
    {
        QGraphicsEllipseItem* oval = new QGraphicsEllipseItem(x, y, 50, 60);
        oval->setPen(pen);
        addItem(oval);
    }

    x += spacing;

    // Буква "В"
    {
        QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x, y, 10, 60);
        verticalStem->setBrush(brush);
        verticalStem->setPen(pen);
        addItem(verticalStem);

        QGraphicsEllipseItem* topLoop = new QGraphicsEllipseItem(x + 10, y, 30, 30);
        topLoop->setPen(pen);
        addItem(topLoop);

        QGraphicsEllipseItem* bottomLoop = new QGraphicsEllipseItem(x + 10, y + 30, 30, 30);
        bottomLoop->setPen(pen);
        addItem(bottomLoop);
    }
}
