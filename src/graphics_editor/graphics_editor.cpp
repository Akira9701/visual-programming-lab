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


GraphicsEditorWindow::GraphicsEditorWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)),
      currentBrushSize(10), isEraserMode(false), currentBrushStyle(Qt::SolidPattern) {

    // Создаем вид и добавляем сцену
    DrawingView *view = new DrawingView(scene, this);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("QGraphicsView { border: 3px solid black; background-color: white; }");

    setCentralWidget(view);
    setWindowTitle("Graphics Editor");

    // Устанавливаем минимальный и максимальный размер окна
    setMinimumSize(900, 900);  // Минимальный размер окна
    setMaximumSize(1600, 1600); // Максимальный размер окна
    setAcceptDrops(true);     // Разрешаем перетаскивание

    // Создаем панель инструментов
    QToolBar *toolbar = addToolBar("Shapes");

    QAction *addTextAction = new QAction(QIcon(":/res/res/AddText.png"),"Add Text", this);
    toolbar->addAction(addTextAction);
    connect(addTextAction, &QAction::triggered, this, &GraphicsEditorWindow::addText);

    // Добавляем кнопку для круга
    QAction *addCircleAction = new QAction(QIcon(":/res/res/Circle.png"),"Add Circle", this);
    toolbar->addAction(addCircleAction);
    connect(addCircleAction, &QAction::triggered, this, &GraphicsEditorWindow::addCircle);

    // Кнопка для удаления выбранного элемента
    QAction *deleteAction = new QAction(QIcon(":/res/res/Delete.png"),"Delete", this);
    toolbar->addAction(deleteAction);
    connect(deleteAction, &QAction::triggered, this, &GraphicsEditorWindow::deleteSelectedItem);


    // Добавляем кнопку для импорта изображения
    QAction *importAction = new QAction(QIcon(":/res/res/AddImage.png"),"Import Image", this);
    toolbar->addAction(importAction);
    connect(importAction, &QAction::triggered, this, &GraphicsEditorWindow::importImage);

    // Добавляем кнопку для сохранения изображения
    QAction *saveAction = new QAction(QIcon(":/res/res/Save.png"),"Save", this);
    toolbar->addAction(saveAction);
    connect(saveAction, &QAction::triggered, this, &GraphicsEditorWindow::saveImage);

    // Кнопка для изменения фона
    QAction *backgroundAction = new QAction(QIcon(":/res/res/BackgroundColor.png"),"Background Color", this);
    toolbar->addAction(backgroundAction);
    connect(backgroundAction, &QAction::triggered, this, &GraphicsEditorWindow::changeBackgroundColor);

    // Кнопка для изменения размера кисти
    QAction *brushSizeAction = new QAction(QIcon(":/res/res/BrushSize.png"),"Brush Size", this);
    toolbar->addAction(brushSizeAction);
    connect(brushSizeAction, &QAction::triggered, this, &GraphicsEditorWindow::setBrushSize);

    // Кнопка для изменения цвета кисти
    QAction *brushColorAction = new QAction(QIcon(":/res/res/BrushColor.png"),"Brush Color", this);
    toolbar->addAction(brushColorAction);
    connect(brushColorAction, &QAction::triggered, this, &GraphicsEditorWindow::setBrushColor);

    // Добавляем кнопку для линии
    QAction *addLineAction = new QAction(QIcon(":/res/res/Line.png"),"Add Line", this);
    toolbar->addAction(addLineAction);
    connect(addLineAction, &QAction::triggered, this, &GraphicsEditorWindow::addLine);

    // Добавляем кнопку для прямоугольника
    QAction *addRectangleAction = new QAction(QIcon(":/res/res/Rectangle.png"),"Add Rectangle", this);
    toolbar->addAction(addRectangleAction);
    connect(addRectangleAction, &QAction::triggered, this, &GraphicsEditorWindow::addRectangle);

    // Добавляем кнопку для треугольника
    QAction *addTriangleAction = new QAction(QIcon(":/res/res/Triangle.png"),"Add Triangle", this);
    toolbar->addAction(addTriangleAction);
    connect(addTriangleAction, &QAction::triggered, this, &GraphicsEditorWindow::addTriangle);

    // Добавляем кнопку для треугольника
    QAction *addPolygonAction = new QAction(QIcon(":/res/res/Polygon.png"),"Add Polygon", this);
    toolbar->addAction(addPolygonAction);
    connect(addPolygonAction, &QAction::triggered, this, &GraphicsEditorWindow::addPolygon);

     QComboBox *brushStyleComboBox = new QComboBox(this);
     brushStyleComboBox->addItem("Solid", QVariant::fromValue(Qt::SolidPattern));
     brushStyleComboBox->addItem("Dense 1", QVariant::fromValue(Qt::Dense1Pattern));
     brushStyleComboBox->addItem("Dense 2", QVariant::fromValue(Qt::Dense2Pattern));
     brushStyleComboBox->addItem("Dense 3", QVariant::fromValue(Qt::Dense3Pattern));
     brushStyleComboBox->addItem("Dense 4", QVariant::fromValue(Qt::Dense4Pattern));
     brushStyleComboBox->addItem("Dense 5", QVariant::fromValue(Qt::Dense5Pattern));
     brushStyleComboBox->addItem("Dense 6", QVariant::fromValue(Qt::Dense6Pattern));
     brushStyleComboBox->addItem("Dense 7", QVariant::fromValue(Qt::Dense7Pattern));
     brushStyleComboBox->addItem("Cross", QVariant::fromValue(Qt::CrossPattern));
     brushStyleComboBox->addItem("Horizontal", QVariant::fromValue(Qt::HorPattern));
     brushStyleComboBox->addItem("Vertical", QVariant::fromValue(Qt::VerPattern));
     toolbar->addWidget(brushStyleComboBox);
     connect(brushStyleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &GraphicsEditorWindow::setBrushStyle);

     // Кнопка для ластика
     QAction *eraserAction = new QAction(QIcon(":/toolbar/eraser.png"),"Eraser", this);
     toolbar->addAction(eraserAction);
     connect(eraserAction, &QAction::triggered, this, &GraphicsEditorWindow::setEraser);

     QTimer *timer = new QTimer(this);
     timer->start(16); // Set the timer interval (e.g., 16 ms for ~60 FPS)

     /*Dog *dog = new Dog();
     dog->setPos(200, 400);
     connect(timer, &QTimer::timeout, [dog, view]() { dog->move(view); }); // Передаем представление в функцию перемещения
     scene->addItem(dog);

     Bird *bird = new Bird();
     bird->setPos(300, 700);
     connect(timer, &QTimer::timeout, [bird, view]() { bird->move(view); }); // Передаем представление в функцию перемещения
     scene->addItem(bird);


     Flower *flower = new Flower();
     flower->setPos(100, 200);
     connect(timer, &QTimer::timeout, [flower, view]() { flower->move(view); }); // Передаем представление в функцию перемещения
     scene->addItem(flower);

     ParkWord* parkWord = new ParkWord();
     scene->addItem(parkWord);
     connect(timer, &QTimer::timeout, [parkWord, view]() { parkWord->move(view); });
     parkWord->setPos(50, 50);

     /*VarWord* varWord = new VarWord();
     scene->addItem(varWord);
     connect(timer, &QTimer::timeout, [varWord, view]() { varWord->move(view); });
     varWord->setPos(50, 50);*/

     /*MartWord* martWord = new MartWord();
     scene->addItem(martWord);
     connect(timer, &QTimer::timeout, [martWord, view]() { martWord->move(view); });
     martWord->setPos(50, 50);*/
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


// Слот для сохранения изображения
void GraphicsEditorWindow::saveImage() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG Files (*.png)");

    if (!filePath.isEmpty()) {
        // Устанавливаем размер изображения под размер сцены
        QPixmap pixmap(scene->sceneRect().size().toSize());

        // Создаём QPainter для рисования на QPixmap
        QPainter painter(&pixmap);

        // Отрисовываем сцену на QPixmap
        scene->render(&painter);

        // Сохраняем изображение в фа��л
        pixmap.save(filePath, "PNG");
    }
}

// Слот для импорта изображения

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

void GraphicsEditorWindow::setEraser() {
    isEraserMode = true;
    static_cast<DrawingView*>(centralWidget())->setBrushColor(scene->backgroundBrush().color());
}

void GraphicsEditorWindow::changeBackgroundColor() {
    QColor color = QColorDialog::getColor(scene->backgroundBrush().color(), this, "Select Background Color");
    if (color.isValid()) {
        scene->setBackgroundBrush(color);
        if (isEraserMode) {
            static_cast<DrawingView*>(centralWidget())->setBrushColor(color);
        }
    }
}

// Слот для добавлеия текста
void GraphicsEditorWindow::addText() {
    // Запрашиваем текст
    bool ok;
    QString text = QInputDialog::getText(this, "Add Text", "Enter your text:", QLineEdit::Normal, "", &ok);
    if (!ok || text.isEmpty()) return;

    // Запрашиваем шрифт
    bool fontOk;
    QFont font = QFontDialog::getFont(&fontOk, QFont("Arial", 12), this, "Select Font");
    if (!fontOk) return;

    // Создаем элемент текста с поведением перемещения правой кнопкой мыши
    MovableTextItem *textItem = new MovableTextItem(text);
    textItem->setFont(font);

    // Добавляем текст на сцену
    scene->addItem(textItem);
    textItem->setPos(100, 200);
}


void GraphicsEditorWindow::deleteSelectedItem() {
    // Получаем выбранные элементы
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    if (selectedItems.isEmpty()) {
        qDebug() << "No items selected for deletion."; // Отладочное сообщение
        return;
    }

    // Удаляем все выбранные элементы
    for (QGraphicsItem *item : selectedItems) {
        scene->removeItem(item); // Удаляем элемент из сцены
        delete item; // Удаляем объект из памяти
        qDebug() << "Item deleted."; // Подтверждение удаления
    }
}


// Обработка события входа перетаскивания
void GraphicsEditorWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    }
}

// Обработка события завершения перетаскивания
void GraphicsEditorWindow::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasImage()) {
        QPixmap pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
        item->setPos(event->pos()); // Устанавливаем позицию на сцене
        scene->addItem(item);        // Добавляем изображение на сцену
        event->acceptProposedAction();
    }
}







