#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>
#include "QMessageBox"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    text = new text_editor();
    connect(text,&text_editor::firstWindow,this,&MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ButtonOpen_clicked()
{

    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString openFilePath = QFileDialog::getOpenFileName(this, "Выбрать файл", desktopPath,
                                                        "All Files (*.*);; TXT Files (*.txt);; XLS Files (*.csv);");

    if (openFilePath.endsWith(".txt", Qt::CaseInsensitive)) {
        text->fileOpen(openFilePath);
        this->close();
    }
}

void MainWindow::on_ButtonCreate_clicked()
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString savePath = QFileDialog::getSaveFileName(this, "Сохранить файл", desktopPath,
                                                    "All Files (*.*);; TXT Files (*.txt);; XLS Files (*.csv);");
    // Пользователь отменил сохранение
    if (savePath.isEmpty()) {
        return;
    }

    QFile file(savePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать файл.");
        return;
    }

    // Открываем соответствующее окно в зависимости от расширения файла
    if (savePath.endsWith(".txt", Qt::CaseInsensitive)) {
        text->show();
        text->fileOpen(savePath);
        this->close();
    }
}
