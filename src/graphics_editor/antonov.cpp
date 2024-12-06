#include "antonov.h"
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

Antonov::Antonov() : CompositeObject() {
    qreal x = 0;
    qreal y = 0;
    qreal spacing = 70;

    QBrush brush(Qt::black);
    QPen pen(Qt::black);
    pen.setWidth(2);

    // Буква "А"
    {
        QGraphicsLineItem* leftDiagonal = new QGraphicsLineItem(x + 25, y, x + 5, y + 60);
        leftDiagonal->setPen(pen);
        addItem(leftDiagonal);

        QGraphicsLineItem* rightDiagonal = new QGraphicsLineItem(x + 25, y, x + 45, y + 60);
        rightDiagonal->setPen(pen);
        addItem(rightDiagonal);

        QGraphicsRectItem* horizontalBar = new QGraphicsRectItem(x + 10, y + 30, 30, 5);
        horizontalBar->setBrush(brush);
        horizontalBar->setPen(pen);
        addItem(horizontalBar);
    }

    x += spacing;

    // Буква "Н"
    {
        QGraphicsRectItem* leftStem = new QGraphicsRectItem(x, y, 10, 60);
        leftStem->setBrush(brush);
        leftStem->setPen(pen);
        addItem(leftStem);

        QGraphicsRectItem* horizontalBar = new QGraphicsRectItem(x, y + 25, 50, 10);
        horizontalBar->setBrush(brush);
        horizontalBar->setPen(pen);
        addItem(horizontalBar);

        QGraphicsRectItem* rightStem = new QGraphicsRectItem(x + 40, y, 10, 60);
        rightStem->setBrush(brush);
        rightStem->setPen(pen);
        addItem(rightStem);
    }

    x += spacing;

    // Буква "Т"
    {
        QGraphicsLineItem* topBar = new QGraphicsLineItem(x, y, x + 50, y);
        topBar->setPen(pen);
        addItem(topBar);

        QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x + 20, y, 10, 60);
        verticalStem->setBrush(brush);
        verticalStem->setPen(pen);
        addItem(verticalStem);
    }

    x += spacing;

    // Буква "О"
    {
        QGraphicsEllipseItem* oval = new QGraphicsEllipseItem(x, y, 50, 60);
        oval->setPen(pen);
        addItem(oval);
    }

    x += spacing;

    // Буква "Н"
    {
        QGraphicsRectItem* leftStem = new QGraphicsRectItem(x, y, 10, 60);
        leftStem->setBrush(brush);
        leftStem->setPen(pen);
        addItem(leftStem);

        QGraphicsRectItem* horizontalBar = new QGraphicsRectItem(x, y + 25, 50, 10);
        horizontalBar->setBrush(brush);
        horizontalBar->setPen(pen);
        addItem(horizontalBar);

        QGraphicsRectItem* rightStem = new QGraphicsRectItem(x + 40, y, 10, 60);
        rightStem->setBrush(brush);
        rightStem->setPen(pen);
        addItem(rightStem);
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
        topLoop->setBrush(brush);
        topLoop->setPen(pen);
        addItem(topLoop);

        QGraphicsEllipseItem* bottomLoop = new QGraphicsEllipseItem(x + 10, y + 30, 30, 30);
        bottomLoop->setBrush(brush);
        bottomLoop->setPen(pen);
        addItem(bottomLoop);
    }
}
