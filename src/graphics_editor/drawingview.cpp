#include "drawingview.h"
#include <QGraphicsScene>
#include <QPen>
#include <QGraphicsEllipseItem>
#include <QMimeData>
#include <QResizeEvent>

DrawingView::DrawingView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent), isDrawing(false), drawingEnabled(true), brushSize(5), brushStyle(Qt::SolidPattern), brushColor(Qt::black) {}

void DrawingView::setBrushSize(qreal size) {
    brushSize = size;
}

void DrawingView::setBrushColor(const QColor &color) {
    brushColor = color;
}

void DrawingView::setBrushStyle(Qt::BrushStyle style) {
    brushStyle = style;
}

void DrawingView::setDrawingEnabled(bool enabled) {
    drawingEnabled = enabled;
}

void DrawingView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawingEnabled) {
        isDrawing = true;
        drawAt(event->pos());
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void DrawingView::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    } else {
        QGraphicsView::dragEnterEvent(event);
    }
}

void DrawingView::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasImage()) {
        QPixmap pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
        item->setPos(mapToScene(event->pos()));
        scene()->addItem(item);
        event->acceptProposedAction();
    } else {
        QGraphicsView::dropEvent(event);
    }
}

void DrawingView::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawing && drawingEnabled) {
        drawAt(event->pos());
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void DrawingView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDrawing = false;
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void DrawingView::drawAt(const QPoint &position) {
    QPointF scenePos = mapToScene(position);
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(
        scenePos.x() - brushSize / 2,
        scenePos.y() - brushSize / 2,
        brushSize,
        brushSize
    );

    QBrush brush(brushColor, brushStyle);
    ellipse->setBrush(brush);
    ellipse->setPen(Qt::NoPen);
    scene()->addItem(ellipse);
}

void DrawingView::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    if (scene()) {
        scene()->setSceneRect(rect());
    }
}

void DrawingView::wheelEvent(QWheelEvent *event) {
    if (event->angleDelta().y() > 0) {
        updateBrushSize(1);  // Увеличиваем размер кисти при прокрутке вверх
    } else {
        updateBrushSize(-1); // Уменьшаем размер кисти при прокрутке вниз
    }
}

void DrawingView::updateBrushSize(qreal delta) {
    brushSize = qMax(1.0, brushSize + delta);
}
