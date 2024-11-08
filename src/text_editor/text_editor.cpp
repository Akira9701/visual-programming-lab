#include "text_editor.h"
#include "ui_text_editor.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

text_editor::text_editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::text_editor),
    isModified(false)
{
    ui->setupUi(this);
    QString tempPath = "";
    connect(ui->textEdit, &QTextEdit::textChanged, this, &text_editor::onTextChanged);
}

text_editor::~text_editor()
{
    delete ui;
}

void text_editor::onTextChanged() {
    isModified = true;
}

void text_editor::on_FileExitMW_triggered()
{
    this->close();
    emit firstWindow();
}

void text_editor::on_FileExitDesktop_triggered()
{
    QApplication::quit();
}


void text_editor::on_FileOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", "",
                                                    "All Files (*.*);;TXT Files (*.txt);;HTML Files (*.html)");
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        return;
    }

     QFile file(filePath);
     if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString fileContent = in.readAll();
        file.close();

        ui->textEdit->setHtml(fileContent);
        ui->tabWidget->setTabText(0, QFileInfo(filePath).fileName());
        tempPath = filePath;
        isModified = false;
     }
}

void text_editor::fileOpen(const QString &filePath)
{
    if (filePath.isEmpty()) {
        ui->textEdit->setPlainText("Ошибка загрузки!");
        return;
    }

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        tempPath = filePath;
        QTextStream in(&file);
        QString fileContent = in.readAll();
        file.close();

        ui->textEdit->setHtml(fileContent);
        ui->tabWidget->setTabText(0, QFileInfo(filePath).fileName());
        isModified = false;
        this->show();
    }
}

void text_editor::on_FileSave_triggered()
{
    int currentTabIndex = ui->tabWidget->currentIndex();
    if (currentTabIndex < 0) {
        QMessageBox::warning(this, "Ошибка", "Нет открытых вкладок для сохранения.");
        return;
    }

    QString fileFolder = tempPath;
    if (fileFolder.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
        return;
    }

    QFile file(fileFolder);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        QString textToSave = ui->textEdit->toHtml();
        out << textToSave;
        file.close();
        isModified = false;
        QMessageBox::information(this, "Успех", "Файл успешно сохранён.");
    }
}

void text_editor::on_FileSaveAs_triggered()
{
    QString savePath = QFileDialog::getSaveFileName(this, "Сохранить файл", tempPath,
                                                    "All Files (*.*);; HTML Files (*.html);; TXT Files (*.txt)");
    if (savePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
        return;
    }
    
    QFile file(savePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        QString textToSave = ui->textEdit->toHtml();
        out << textToSave;
        file.close();
        isModified = false;
        QMessageBox::information(this, "Успех", "Файл успешно сохранён.");
    } 
}

void text_editor::on_BoldButton_clicked(bool checked)
{
    QTextCursor cursor = ui->textEdit->textCursor();

    if (!cursor.hasSelection()) {
        return;
    }

    QTextCharFormat format;
    if (checked) {
        format.setFontWeight(QFont::Bold);
    } else {
        format.setFontWeight(QFont::Normal);
    }

    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}


void text_editor::on_ItalicButton_clicked(bool checked)
{
    QTextCursor cursor = ui->textEdit->textCursor();

    if (!cursor.hasSelection()) {
        return;
    }

    QTextCharFormat format;
    format.setFontItalic(checked);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}


void text_editor::on_UnderlinedButton_clicked(bool checked)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    
    if (!cursor.hasSelection()) {
        return;
    }

    QTextCharFormat format;
    format.setFontUnderline(checked);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}


void text_editor::on_StrikethroughButton_clicked(bool checked)
{
    QTextCursor cursor = ui->textEdit->textCursor();
   
    if (!cursor.hasSelection()) {
        return;
    }

    QTextCharFormat format;
    format.setFontStrikeOut(checked);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void text_editor::on_spinBox_valueChanged(int fontSize)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    
    if (!cursor.hasSelection()) {
        return;
    }

    QTextCharFormat format;
    format.setFontPointSize(fontSize);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}


void text_editor::closeEvent(QCloseEvent *event)
{
    if (!isModified) {
        event->accept();
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Сохранить изменения",
                                      "Хотите сохранить изменения в файле перед выходом?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {
        if (tempPath.isEmpty()) {
            on_FileSaveAs_triggered();
        } else {
            on_FileSave_triggered();
        }


        if (!isModified) {
            event->accept();
        } else {
            event->ignore();
        }
    } else if (reply == QMessageBox::No) {
        event->accept();
    } else {
        event->ignore();
    }
}

void text_editor::on_ClearButton_triggered()
{
       QString tempFilePath = QDir::temp().absoluteFilePath("temp_text_file.txt");
       QFile tempFile(tempFilePath);

       if (tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
           QTextStream out(&tempFile);
           out << ui->textEdit->toPlainText();
           tempFile.close();
           ui->textEdit->clear();

           ui->UndoButton->setEnabled(true);
       } else {
           QMessageBox::warning(this, "Ошибка", "Не удалось сохранить во временный файл.");
       }
}

void text_editor::on_UndoButton_triggered()
{
    QString tempFilePath = QDir::temp().absoluteFilePath("temp_text_file.txt");
       QFile tempFile(tempFilePath);

       if (tempFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
           QTextStream in(&tempFile);
           QString restoredText = in.readAll();
           tempFile.close();
           ui->textEdit->setPlainText(restoredText);
           tempFile.remove();
           ui->UndoButton->setEnabled(false);
       } else {
           QMessageBox::warning(this, "Ошибка", "Не удалось восстановить из временного файла.");
       }
}

void text_editor::on_AlignLeftButton_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void text_editor::on_AlignCenterButton_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void text_editor::on_AlignRightButton_clicked()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void text_editor::on_AlignJustifyButton_clicked()
{
   ui->textEdit->setAlignment(Qt::AlignJustify);
}

void text_editor::on_actionOpen_in_NewWindow_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл", "",
                                                    "All Files (*.*);; TXT Files (*.txt);");

    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        return;
    }

    text_editor *newEditor = new text_editor(this);
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString fileContent = in.readAll();
        file.close();

        newEditor->ui->textEdit->setHtml(fileContent);
        newEditor->ui->tabWidget->setTabText(0, QFileInfo(filePath).fileName());
        newEditor->show();
    }
}


void text_editor::on_AddTable_triggered()
{
    bool ok;
    int rows = QInputDialog::getInt(this, tr("Введите количество строк"),
                                     tr("Строки:"), 2, 1, 100, 1, &ok);
    if (!ok) { return; }

    int columns = QInputDialog::getInt(this, tr("Введите количество столбцов"),
                                        tr("Столбцы:"), 2, 1, 100, 1, &ok);
    if (!ok) { return; }



    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setCellPadding(10);
    tableFormat.setCellSpacing(0);
    tableFormat.setAlignment(Qt::AlignCenter);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable *table = cursor.insertTable(rows, columns, tableFormat);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            QTextTableCell cell = table->cellAt(i, j);
            QTextCursor cellCursor = cell.firstCursorPosition();
            cellCursor.insertText(" ");
        }
    }
}

void text_editor::on_LoadTable_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", "",
                                                    "All Files (*.*);;TXT Files (*.txt);;HTML Files (*.html)");
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        return;
    }

     QFile file(filePath);
     if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
         QTextStream in(&file);
         QString fileContent = in.readAll();
         file.close();

         ui->textEdit->insertHtml(fileContent);
     }
}

void text_editor::on_RemoveSelectedTable_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();

    if (!cursor.hasSelection()) {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, выделите таблицу для удаления.");
        return;
    }


    QString selectedText = cursor.selection().toHtml();
    QRegularExpression tablePattern("<table[^>]*>.*?</table>", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch match = tablePattern.match(selectedText);

    if (!match.hasMatch()) {
        QMessageBox::information(this, "Информация", "Выделенный фрагмент не содержит таблицу.");
        return;
    }

    cursor.removeSelectedText();
    cursor.insertText("");
}

void text_editor::on_AddRow_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable *table = cursor.currentTable();

    if (!table) {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, выделите таблицу для добавления строки.");
        return;
    }

    // Add a new row
    table->insertRows(table->rows(), 1);
    for (int j = 0; j < table->columns(); ++j) {
        QTextTableCell cell = table->cellAt(table->rows() - 1, j);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.insertText(" ");
    }
}

void text_editor::on_AddColumn_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable *table = cursor.currentTable();

    if (!table) {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, выделите таблицу для добавления столбца.");
        return;
    }

    table->insertColumns(table->columns(), 1);
    for (int i = 0; i < table->rows(); ++i) {
        QTextTableCell cell = table->cellAt(i, table->columns() - 1);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.insertText(" ");
    }
}

void text_editor::on_RemoveRow_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable *table = cursor.currentTable();

    if (!table) {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, выделите таблицу для удаления строки.");
        return;
    }

    QTextTableCell currentCell = table->cellAt(cursor.position());
    int currentRow = currentCell.row();

    if (currentRow < 0 || currentRow >= table->rows()) {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, установите курсор в строку для удаления.");
        return;
    }

    table->removeRows(currentRow, 1);
}

void text_editor::on_RemoveColumn_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable *table = cursor.currentTable();

    if (!table) {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, выделите таблицу для удаления столбца.");
        return;
    }

    QTextTableCell currentCell = table->cellAt(cursor.position());
    int currentColumn = currentCell.column();

    if (currentColumn < 0 || currentColumn >= table->columns()) {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, установите курсор в столбец для удаления.");
        return;
    }

    table->removeColumns(currentColumn, 1);
}

void text_editor::on_paintButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Выберите цвет текста");
    if (color.isValid()) {
        QTextCharFormat format;
        format.setForeground(color);
        ui->textEdit->textCursor().mergeCharFormat(format);
    }
}
