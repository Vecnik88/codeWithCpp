#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // настройки размеров положения окна, текстовых редакторов, надписей, кнопки

    this->setWindowTitle("Text Editor Created by Vecnik88");
    this->setGeometry(100, 30, 1200, 650);
    ui->textEdit->setGeometry(150, 25, 1000, 275);
    ui->textEdit_2->setGeometry(150, 325, 1000, 275);
    ui->label->move(50,25);
    ui->label_2->move(50, 325);
    ui->pushButton->move(32, 350);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()                   // <---. создаем новый файл
{
    mFilename = "";
    ui->textEdit->setPlainText("");
    ui->textEdit_2->setPlainText("");
}

void MainWindow::on_actionOpen_triggered()                  // <---. открываем файл, только в первом текст. редакторе
{
    QString file = QFileDialog::getOpenFileName(this, "Open a file");
    mFilename = file;

    if(!file.isEmpty())
    {
        QFile sFile(file);
        if(sFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&sFile);
            QString text = in.readAll();

            ui->textEdit->setPlainText(text);
            sFile.close();
        }
    }
}

void MainWindow::on_actionSave_triggered()                  // <---. возможность сохранить изменения в открытом файле
{
    QFile sFile(mFilename);
    if(sFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&sFile);

        out << ui->textEdit->toPlainText();

        sFile.flush();
        sFile.close();
    }
}

void MainWindow::on_actionSave_as_triggered()               // <---. сохраняем в новый файл, не кодированный
{
    QString file = QFileDialog::getSaveFileName(this, "Open a file");

    if(!file.isEmpty())
    {
        mFilename = file;
        on_actionSave_triggered();
    }
}
void MainWindow::on_actionSave_as_cipher_text_triggered()   // <---. сохраняем закодированный текст в файл
{
    QString file = QFileDialog::getSaveFileName(this, "Open a file");

    if(!file.isEmpty())
    {
        QFile outFile(file);
        if(outFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&outFile);

            out << ui->textEdit_2->toPlainText();

            outFile.flush();
            outFile.close();
        }
    }
}

void MainWindow::on_actionCopy_triggered()                  // <---. копируем текст из активного окна
{
    if(ui->textEdit->hasFocus())
        ui->textEdit->copy();

    if(ui->textEdit_2->hasFocus())
        ui->textEdit_2->copy();
}

void MainWindow::on_actionCut_triggered()                   // <---. вырезать текст из активного редактора
{
    if(ui->textEdit->hasFocus())
        ui->textEdit->cut();

    if(ui->textEdit_2->hasFocus())
        ui->textEdit_2->cut();
}

void MainWindow::on_actionPaste_triggered()                 // <---. вставить текст в активный редактор
{
    if(ui->textEdit->hasFocus())
        ui->textEdit->paste();

    if(ui->textEdit_2->hasFocus())
        ui->textEdit_2->paste();
}

void MainWindow::on_actionUndo_triggered()                  // <---. вернуться на шаг назад в активном редакторе
{
    if(ui->textEdit->hasFocus())
        ui->textEdit->undo();

    if(ui->textEdit_2->hasFocus())
        ui->textEdit_2->undo();
}

void MainWindow::on_actionRedo_triggered()                  // <---. вернуться на шаг вперед в активном редакторе
{
    if(ui->textEdit->hasFocus())
        ui->textEdit->redo();

    if(ui->textEdit_2->hasFocus())
        ui->textEdit_2->redo();
}

void MainWindow::on_actionCiphier_triggered()               // <---. происходит шифрование текста из 1 редактора
{                                                           //       и вывод его во втором
        QString text = ui->textEdit->toPlainText();
        text = cipher(text);
        ui->textEdit_2->setPlainText(text);
}

QString MainWindow::cipher(QString& str)                    // <---. шифрование
{
    std::string invert = str.toStdString();                 // <---. приводим к string, поскольку switch u QChar несовместимы
    std::string result;

    for(size_t i = 0; i < invert.size(); ++i)
    {
        switch(tolower(invert.at(i)))
        {
        case 'a':
            result += ".- ";
            break;
        case 'b':
            result += "-... ";
            break;
        case 'c':
            result += "-.-. ";
            break;
        case 'd':
            result += "-.. ";
            break;
        case 'e':
            result += ". ";
            break;
        case 'f':
            result += "..-. ";
            break;
        case 'g':
            result += "--. ";
            break;
        case 'h':
            result += ".... ";
            break;
        case 'i':
            result += ".. ";
            break;
        case 'j':
            result += ".--- ";
            break;
        case 'k':
            result += "-.- ";
            break;
        case 'l':
            result += ".-.. ";
            break;
        case 'm':
            result += "-- ";
            break;
        case 'n':
            result += "-. ";
            break;
        case 'o':
            result += "--- ";
            break;
        case 'p':
            result += ".--. ";
            break;
        case 'q':
            result += "--.- ";
            break;
        case 'r':
            result += ".-. ";
            break;
        case 's':
            result += "... ";
            break;
        case 't':
            result += "- ";
            break;
        case 'u':
            result += "..- ";
            break;
        case 'v':
            result += "...- ";
            break;
        case 'w':
            result += ".-- ";
            break;
        case 'x':
            result += "-..- ";
            break;
        case 'y':
            result += "-.-- ";
            break;
        case 'z':
            result += "--.. ";
            break;
        case '1':
            result += ".---- ";
            break;
        case '2':
            result += "..--- ";
            break;
        case '3':
            result += "...-- ";
            break;
        case '4':
            result += "....- ";
            break;
        case '5':
            result += "..... ";
            break;
        case '6':
            result += "-.... ";
            break;
        case '7':
            result += "--... ";
            break;
        case '8':
            result += "---.. ";
            break;
        case '9':
            result += "----. ";
            break;
        case '0':
            result += "----- ";
            break;
        case ' ':
            result += "  ";
            break;
        case '.':
            result += "...... ";
            break;
        case ',':
            result += ".-.-.- ";
            break;
        case ':':
            result += "---... ";
            break;
        case ';':
            result += "-.-.-. ";
            break;
        case ')':
        case '(':
            result += "-.--.- ";
            break;
        case '\'':
            result += ".----. ";
            break;
        case '\"':
            result += ".-..-. ";
            break;
        case '/':
            result += "-..-. ";
            break;
        case '?':
            result += "..--.. ";
            break;
        case '!':
            result += "--..-- ";
            break;
        case '@':
            result += ".--.-. ";
            break;
        default:
            break;
        }
    }
    return QString::fromStdString(result);                  // <---. приводим string k QString
}

void MainWindow::on_pushButton_clicked()                    // <---. шифр через кнопку CHIHER
{
    on_actionCiphier_triggered();
}

void MainWindow::on_actionInfo_triggered()
{
    QMessageBox::information(this, tr("Information"),tr("\t\tСоздано 25.02.2017, исполнитель Vecnik88\n\n"
                "\tРеализовано приложение текстового редактора с возможностью шифрование исходного текста"
                "и сохранения его в последствии в новый текстовый документ.\n"
                "\tРеализована возможность вырезания текста, его вставка и копирование,"
                "также сделаны две клавиши - возврат на шаг назад и на шаг вперед.\n\n"

                "\t\tCreated 25.02.2017 by Vecnik88\n\n"
                "\tImplemented a text editor application with the ability to encrypt the source code"
                "and save it later in a new text document.\n"
                "\tThe possibility of cutting the text, copying and pasting it,"
                "also made two keys - return one step back and one step forward."));
}


