// ### Created by Vecnik88

/*
        Создано 25.04.2017, исполнитель Vecnik88
        Реализовано приложение текстового редактора с возможностью шифрование исходного текста
        и сохранения его в последствии в новый текстовый документ.
        Реализована возможность вырезания текста, его вставка и копирование,
        также сделаны две клавиши - возврат на шаг назад и на шаг вперед.

        Created 25.04.2017, Vecnik88 artist
        Implemented a text editor application with the ability to encrypt the source code
        and save it later in a new text document.
        The possibility of cutting the text, copying and pasting it,
        also made two keys - return one step back and one step forward.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <string>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionInfo_triggered();

    void on_actionNew_triggered();

    void on_actionCopy_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCiphier_triggered();

    void on_pushButton_clicked();

    void on_actionSave_as_cipher_text_triggered();

private:
    Ui::MainWindow *ui;
    QString mFilename;                              // <---. имя файла основного, с которым будем работать
    QString cipher(QString& str);                   // <---. метод шифрования текста из исходной строки
};

#endif // MAINWINDOW_H
