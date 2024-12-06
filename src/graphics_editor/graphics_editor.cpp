#include "graphics_editor.h"
#include "circle.h"
#include "line.h"
#include "triangle.h"
#include "rectangle.h"
#include <QGraphicsView>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QInputDialog>
#include <QColorDialog>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QFontDialog>
#include <QGraphicsPixmapItem>
#include <QComboBox>
#include <drawingview.h>
#include "movabletextitem.h"
#include "QtMath"
#include "compositeobject.h"
#include <polygon.h>
#include <QMessageBox>
#include <QMenu>
#include <flower.h>
#include <mouse.h>
#include <antonov.h>
#include <belousov.h>

GraphicsEditorWindow::GraphicsEditorWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)),
      currentBrushSize(10), isEraserMode(false), currentBrushStyle(Qt::SolidPattern) {

    DrawingView *view = new DrawingView(scene, this);
    setStyleSheet("QGraphicsView { border: 3px solid black; background-color: white; }");
    scene->setBackgroundBrush(Qt::white);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setCentralWidget(view);

    setWindowTitle("Graphics Window");
    setFixedSize(900, 900);
    setAcceptDrops(true);

    QToolBar *toolbar = new QToolBar("Toolbar", this);
    addToolBar(Qt::LeftToolBarArea, toolbar);
    toolbar->setOrientation(Qt::Vertical);
    toolbar->setStyleSheet("QToolBar { background-color: #333; }"
                           "QToolButton { color: white; font-size: 14px; }");

    QAction *addTextAction = new QAction(QIcon(":/res/res/AddText.png"),"Add Text", this);
    toolbar->addAction(addTextAction);
    connect(addTextAction, &QAction::triggered, this, &GraphicsEditorWindow::addText);

    QAction *addLineAction = new QAction(QIcon(":/res/res/Line.png"),"Add Line", this);
    toolbar->addAction(addLineAction);
    connect(addLineAction, &QAction::triggered, this, &GraphicsEditorWindow::addLine);

    QAction *addCircleAction = new QAction(QIcon(":/res/res/Circle.png"),"Add Circle", this);
    toolbar->addAction(addCircleAction);
    connect(addCircleAction, &QAction::triggered, this, &GraphicsEditorWindow::addCircle);

    QAction *addRectangleAction = new QAction(QIcon(":/res/res/Rectangle.png"),"Add Rectangle", this);
    toolbar->addAction(addRectangleAction);
    connect(addRectangleAction, &QAction::triggered, this, &GraphicsEditorWindow::addRectangle);

    QAction *addTriangleAction = new QAction(QIcon(":/res/res/Triangle.png"),"Add Triangle", this);
    toolbar->addAction(addTriangleAction);
    connect(addTriangleAction, &QAction::triggered, this, &GraphicsEditorWindow::addTriangle);

    QAction *addPolygonAction = new QAction(QIcon(":/res/res/Polygon.png"),"Add Polygon", this);
    toolbar->addAction(addPolygonAction);
    connect(addPolygonAction, &QAction::triggered, this, &GraphicsEditorWindow::addPolygon);

    QAction *deleteAction = new QAction(QIcon(":/res/res/Delete.png"),"Delete", this);
    toolbar->addAction(deleteAction);
    connect(deleteAction, &QAction::triggered, this, &GraphicsEditorWindow::deleteSelectedItem);

    QAction *backgroundAction = new QAction(QIcon(":/res/res/BackgroundColor.png"),"Background Color", this);
    toolbar->addAction(backgroundAction);
    connect(backgroundAction, &QAction::triggered, this, &GraphicsEditorWindow::changeBackgroundColor);

    QAction *eraserAction = new QAction(QIcon(":/res/res/Eraser.png"),"Eraser", this);
    toolbar->addAction(eraserAction);
    connect(eraserAction, &QAction::triggered, this, &GraphicsEditorWindow::setEraser);

    QAction *importAction = new QAction(QIcon(":/res/res/AddImage.png"),"Import Image", this);
    toolbar->addAction(importAction);
    connect(importAction, &QAction::triggered, this, &GraphicsEditorWindow::importImage);

    QAction *saveAction = new QAction(QIcon(":/res/res/Save.png"),"Save", this);
    toolbar->addAction(saveAction);
    connect(saveAction, &QAction::triggered, this, &GraphicsEditorWindow::saveImage);

    QAction *brushSizeAction = new QAction(QIcon(":/res/res/BrushSize.png"),"Brush Size", this);
    toolbar->addAction(brushSizeAction);
    connect(brushSizeAction, &QAction::triggered, this, &GraphicsEditorWindow::setBrushSize);

    QComboBox *brushStyleComboBox = new QComboBox(this);
    brushStyleComboBox->addItem("Solid", QVariant::fromValue(Qt::SolidPattern));
    brushStyleComboBox->addItem("Dense 1", QVariant::fromValue(Qt::Dense1Pattern));
    brushStyleComboBox->addItem("Dense 2", QVariant::fromValue(Qt::Dense2Pattern));
    brushStyleComboBox->addItem("Dense 3", QVariant::fromValue(Qt::Dense3Pattern));
    brushStyleComboBox->addItem("Cross", QVariant::fromValue(Qt::CrossPattern));
    brushStyleComboBox->addItem("Horizontal", QVariant::fromValue(Qt::HorPattern));
    brushStyleComboBox->addItem("Vertical", QVariant::fromValue(Qt::VerPattern));

    QAction *brushColorAction = new QAction(QIcon(":/res/res/BrushColor.png"),"Brush Color", this);
    toolbar->addAction(brushColorAction);
    connect(brushColorAction, &QAction::triggered, this, &GraphicsEditorWindow::setBrushColor);

    toolbar->addWidget(brushStyleComboBox);

    connect(brushStyleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &GraphicsEditorWindow::setBrushStyle);

    QTimer *timer = new QTimer(this);
    timer->start(16);

}

GraphicsEditorWindow::~GraphicsEditorWindow() {
    delete scene;
}

// Слот для добавления круга
void GraphicsEditorWindow::addCircle() {
    qreal radius = QInputDialog::getDouble(this, "Добавить круг", "Введите радиус круга:",
                                           50, 1, 200, 1, nullptr);
    if (radius <= 0) return;

    QColor fillColor = QColorDialog::getColor(Qt::blue, this, "Выберите цвет заливки");
    if (!fillColor.isValid()) return;

    QColor borderColor = QColorDialog::getColor(Qt::black, this, "Выберите цвет обводки");
    if (!borderColor.isValid()) return;

    auto circle = new Circle(radius, QPointF(0, 0), QBrush(fillColor), QPen(borderColor, 2));

    circle->setPos(scene->width() / 2, scene->height() / 2);

    scene->addItem(circle);
}

// Линия
void GraphicsEditorWindow::addLine() {
    bool ok;

    qreal startX = QInputDialog::getDouble(this, "Начальная точка", "Введите X начальной точки:", 0, 0, 500, 1, &ok);
    if (!ok) return;
    qreal startY = QInputDialog::getDouble(this, "Начальная точка", "Введите Y начальной точки:", 0, 0, 500, 1, &ok);
    if (!ok) return;

    qreal endX = QInputDialog::getDouble(this, "Конечная точка", "Введите X конечной точки:", 0, 0, 500, 1, &ok);
    if (!ok) return;
    qreal endY = QInputDialog::getDouble(this, "Конечная точка", "Введите Y конечной точки:", 0, 0, 500, 1, &ok);
    if (!ok) return;

    QColor lineColor = QColorDialog::getColor(Qt::black, this, "Выберите цвет линии");
    if (!lineColor.isValid()) return;

    QPen pen(lineColor);
    pen.setWidth(2);

    QStringList lineTypes;
    lineTypes << "Сплошная" << "Пунктирная" << "Точечная";
    bool typeOk;
    QString selectedType = QInputDialog::getItem(this, "Тип линии", "Выберите тип линии:", lineTypes, 0, false, &typeOk);
    if (!typeOk) return;

    Line::LineType lineType;
    if (selectedType == "Сплошная") {
        lineType = Line::Solid;
    } else if (selectedType == "Пунктирная") {
        lineType = Line::Dashed;
    } else {
        lineType = Line::Dotted;
    }

    Line *line = new Line(QPointF(startX, startY), QPointF(endX, endY), lineType, pen);
    scene->addItem(line);
}

//Круг
void GraphicsEditorWindow::addPolygon() {
    bool ok;

    int sides = QInputDialog::getInt(this, "Количество сторон", "Введите количество сторон многоугольника:", 5, 3, 20, 1, &ok);
    if (!ok) return;

    qreal radius = QInputDialog::getDouble(this, "Радиус", "Введите радиус описанной окружности:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    QColor fillColor = QColorDialog::getColor(Qt::blue, this, "Выберите цвет заливки");
    if (!fillColor.isValid()) return;

    QColor borderColor = QColorDialog::getColor(Qt::black, this, "Выберите цвет обводки");
    if (!borderColor.isValid()) return;

    QBrush brush(fillColor);
    QPen pen(borderColor);
    pen.setWidth(2);

    Polygon *polygon = new Polygon(sides, radius, brush, pen);
    scene->addItem(polygon);
    polygon->setPos(100, 200);  // Устанавливаем позицию на сцене
}

//Прямоугольник
void GraphicsEditorWindow::addRectangle() {
    bool ok;
    qreal width = QInputDialog::getDouble(this, "Ширина прямоугольника", "Введите ширину прямоугольника:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    qreal height = QInputDialog::getDouble(this, "Высота прямоугольника", "Введите высоту прямоугольника:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    qreal cornerRadius = QInputDialog::getDouble(this, "Радиус углов", "Введите радиус округления углов:", 0, 0, qMin(width, height) / 2, 1, &ok);
    if (!ok) return;

    QColor fillColor = QColorDialog::getColor(Qt::blue, this, "Выберите цвет заливки");
    if (!fillColor.isValid()) return;

    QColor borderColor = QColorDialog::getColor(Qt::black, this, "Выберите цвет обводки");
    if (!borderColor.isValid()) return;

    QBrush brush(fillColor);
    QPen pen(borderColor);
    pen.setWidth(2);

    Rectangle *rect = new Rectangle(width, height, brush, pen, cornerRadius);
    scene->addItem(rect);
    rect->setPos(100, 200);
}

//Треугольник
void GraphicsEditorWindow::addTriangle() {
    bool ok;

    qreal base = QInputDialog::getDouble(this, "Основание треугольника", "Введите основание треугольника:", 100, 1, 500, 1, &ok);
    if (!ok || base <= 0) {
        QMessageBox::warning(this, "Неверный ввод", "Основание должно быть положительным числом.");
        return;
    }

    qreal height = QInputDialog::getDouble(this, "Высота треугольника", "Введите высоту треугольника:", 100, 1, 500, 1, &ok);
    if (!ok || height <= 0) {
        QMessageBox::warning(this, "Неверный ввод", "Высота должна быть положительным числом.");
        return;
    }

    bool okType;
    QStringList types = { "Равнобедренный", "Разносторонний" };
    QString selectedType = QInputDialog::getItem(this, "Тип треугольника", "Выберите тип треугольника:", types, 0, false, &okType);

    if (!okType) return;

    Triangle::TriangleType type;
    if (selectedType == "Равнобедренный") {
        type = Triangle::Isosceles;
    } else {
        type = Triangle::Scalene;
    }

    QColor fillColor = QColorDialog::getColor(Qt::blue, this, "Выберите цвет заливки");
    if (!fillColor.isValid()) {
        QMessageBox::warning(this, "Неверный цвет", "Вы должны выбрать корректный цвет заливки.");
        return;
    }

    QColor borderColor = QColorDialog::getColor(Qt::black, this, "Выберите цвет обводки");
    if (!borderColor.isValid()) {
        QMessageBox::warning(this, "Неверный цвет", "Вы должны выбрать корректный цвет обводки.");
        return;
    }

    QBrush brush(fillColor);
    QPen pen(borderColor);
    pen.setWidth(2);

    Triangle *triangle = new Triangle(base, height, type, brush, pen);

    scene->addItem(triangle);

    triangle->setPos(100, 200);
}

void GraphicsEditorWindow::setBrushStyle() {
    QComboBox *brushStyleComboBox = qobject_cast<QComboBox*>(sender());
    if (brushStyleComboBox) {
        Qt::BrushStyle style = static_cast<Qt::BrushStyle>(brushStyleComboBox->currentData().toInt());
        currentBrushStyle = style;
        static_cast<DrawingView*>(centralWidget())->setBrushStyle(currentBrushStyle);
    }
}

void GraphicsEditorWindow::setBrushSize() {
    bool ok;
    qreal size = QInputDialog::getDouble(this, "Brush Size", "Enter brush size:", currentBrushSize, 1, 50, 1, &ok);
    if (ok) {
        currentBrushSize = size;
        static_cast<DrawingView*>(centralWidget())->setBrushSize(currentBrushSize);
    }
}

void GraphicsEditorWindow::setBrushColor() {
    QColor color = QColorDialog::getColor(currentBrushColor, this, "Select Brush Color");
    if (color.isValid()) {
        currentBrushColor = color;
        isEraserMode = false;
        static_cast<DrawingView*>(centralWidget())->setBrushColor(currentBrushColor);
    }
}

// Ластик
void GraphicsEditorWindow::setEraser() {
    isEraserMode = true;
    DrawingView *drawingView = qobject_cast<DrawingView*>(centralWidget());
    if (drawingView) {
        QColor backgroundColor = scene->backgroundBrush().color();
        if (backgroundColor.isValid()) {
            drawingView->setBrushColor(backgroundColor);
        } else {
            drawingView->setBrushColor(Qt::white);
        }
    }
}

// Изменение заднего фона
void GraphicsEditorWindow::changeBackgroundColor() {
    QColor color = QColorDialog::getColor(scene->backgroundBrush().color(), this, "Выберите цвет заднего фона");

    if (!color.isValid()) {
        return;
    }

    if (scene->backgroundBrush().color() != color) {
        scene->setBackgroundBrush(color);
        setEraser();
    }

    if (isEraserMode) {
        static_cast<DrawingView*>(centralWidget())->setBrushColor(color);
    }
}

// Добавление текста
void GraphicsEditorWindow::addText() {
    bool ok;
    QString text = QInputDialog::getText(this, "Add Text", "Enter your text:", QLineEdit::Normal, "", &ok);
    if (!ok || text.isEmpty()) return;

    bool fontOk;
    QFont font = QFontDialog::getFont(&fontOk, QFont("Arial", 12), this, "Select Font");
    if (!fontOk) return;

    MovableTextItem *textItem = new MovableTextItem(text);
    textItem->setFont(font);

    scene->addItem(textItem);
    textItem->setPos(100, 200);
}

//Удаление выбранного объекта
void GraphicsEditorWindow::deleteSelectedItem() {
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    if (selectedItems.isEmpty()) {
        return;
    }

    for (QGraphicsItem *item : selectedItems) {
        scene->removeItem(item);
        delete item;
    }
}

// Перетаскивание изображения
// Слот для сохранения изображения
void GraphicsEditorWindow::saveImage() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG Files (*.png)");

    if (!filePath.isEmpty()) {
        QPixmap pixmap(scene->sceneRect().size().toSize());
        QPainter painter(&pixmap);
        scene->render(&painter);
        pixmap.save(filePath, "PNG");
    }
}

void GraphicsEditorWindow::importImage() {
    QString filePath = QFileDialog::getOpenFileName(this, "Import Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");

    if (!filePath.isEmpty()) {
        QPixmap pixmap(filePath);

        if (!pixmap.isNull()) {
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
            item->setPos(0, 0);
            item->setFlag(QGraphicsItem::ItemIsMovable);
            item->setFlag(QGraphicsItem::ItemIsSelectable);
            scene->addItem(item);
        }
    }
}

void GraphicsEditorWindow::mousePressEvent(QMouseEvent *event) {
    if (scene->itemAt(event->pos(), QTransform()) != nullptr) {
        event->accept();
    } else {
        event->ignore();
    }
}

void GraphicsEditorWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    }
}

void GraphicsEditorWindow::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasImage()) {
        QPixmap pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
        item->setPos(event->pos());
        scene->addItem(item);
        event->acceptProposedAction();
    }
}
