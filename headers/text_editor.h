#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <QMainWindow>
#include <QFileDialog>
#include <QInputDialog>
#include <QColorDialog>
#include <QTextDocumentFragment>
#include <QTextTable>
#include <QTextBlock>
#include <QCloseEvent>

namespace Ui {
class text_editor;
}

class text_editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit text_editor(QWidget *parent = nullptr);
    ~text_editor();

public:
    void fileOpen(const QString &filePath);

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void firstWindow();

private slots:
    void on_FileExitMW_triggered();
    void on_FileExitDesktop_triggered();

    void on_FileOpen_triggered();

    void on_FileSaveAs_triggered();
    void on_FileSave_triggered();

    void on_BoldButton_clicked(bool checked);

    void on_ItalicButton_clicked(bool checked);

    void on_UnderlinedButton_clicked(bool checked);

    void on_StrikethroughButton_clicked(bool checked);

    void on_spinBox_valueChanged(int arg1);

    void on_ClearButton_triggered();

    void on_UndoButton_triggered();

    void on_AlignLeftButton_clicked();

    void on_AlignCenterButton_clicked();

    void on_AlignRightButton_clicked();

    void on_AlignJustifyButton_clicked();

    void on_actionOpen_in_NewWindow_triggered();

    void on_AddTable_triggered();

    void on_LoadTable_triggered();

    void on_RemoveSelectedTable_triggered();


    void on_AddRow_triggered();

    void on_AddColumn_triggered();

    void on_RemoveRow_triggered();

    void on_RemoveColumn_triggered();

    void on_paintButton_clicked();

    void onTextChanged();

    void on_actionNew_triggered();

private:
    Ui::text_editor *ui;
    QString tempPath;
//    bool isTableMode;
    bool isModified;
};

#endif // TEXT_EDITOR_H
