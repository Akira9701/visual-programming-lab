#include "text_editor.h"
#include "ui_text_editor.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

text_editor::text_editor(QWidget *parent) : QMainWindow(parent),
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