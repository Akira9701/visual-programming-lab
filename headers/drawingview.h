#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QColor>

class DrawingView: public QGraphicsView {
    Q_OBJECT

public:
    explicit DrawingView(QGraphicsScene *scene, QWidget *parent = nullptr);
    void setBrushSize(qreal size);
    void setBrushColor(const QColor &color);
    void setBrushStyle(Qt::BrushStyle style);
    void setDrawingEnabled(bool enabled);  // Новая возможность для включения/выключения рисования

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override; // Обработчик колесика мыши для изменения размера кисти

private:
    bool isDrawing;
    bool drawingEnabled;  // Новый флаг для управления рисованием
    qreal brushSize;
    QColor brushColor;
    Qt::BrushStyle brushStyle;
    void drawAt(const QPoint &position);
    void updateBrushSize(qreal delta);  // Обновление размера кисти при прокрутке
};

#endif
