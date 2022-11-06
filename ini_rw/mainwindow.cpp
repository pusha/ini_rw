#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);  //-создаёт кнопки-лейбы из ui-файла

    do_stuff();
}

//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//-----------------------------------------------------------------------------
void MainWindow::do_stuff(void)
{

    //-создадим поля и лейбы к ним
    for (uint i = 0; i < TEXTEDITC; i++)
    {
        TEArr[i] = new QTextEdit(this);
        TEArr[i]->setPlaceholderText("-=пусто=-");
        TEArr[i]->resize(TEXTEDIT_WIDTH, TEXTEDIT_HEIGHT);
        TEArr[i]->setLineWrapMode(QTextEdit::NoWrap);
        TEArr[i]->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TEArr[i]->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TEArr[i]->setFixedHeight(TEXTEDIT_HEIGHT);


        labelArr[i] = new QLabel(labelNameArray[i], this);
        labelArr[i]->setBuddy(TEArr[i]);        //-let's make some friends
        labelArr[i]->setAlignment(Qt::AlignLeft);
    }


    //-выведем секцию [BasicData]
    QGroupBox *gboxBasicData = new QGroupBox("BasicData", this);
    QGridLayout *glayBasicData = new QGridLayout;
    for (uint i = 0; i < 8; i++)
    {
        TEArr[i]->move(150, 10 + i * (TEXTEDIT_HEIGHT+5));
        labelArr[i]->move(50, 10 + i * (TEXTEDIT_HEIGHT+5));
        glayBasicData->addWidget(labelArr[i], i, 0);
        glayBasicData->addWidget(TEArr[i], i, 1);
    }
    gboxBasicData->setLayout(glayBasicData);
    gboxBasicData->resize(300, MAINWINDOW_HEIGHT);
    gboxBasicData->show();


    //-[FlyData]
    QGroupBox *gboxFlyData = new QGroupBox("FlyData", this);
    QGridLayout *glayFlyData = new QGridLayout;
    for (uint i = 0; i < 7; i++)
    {
        TEArr[i+8]->move(450, 10 + i * (TEXTEDIT_HEIGHT+5));
        labelArr[i+8]->move(350, 10 + i * (TEXTEDIT_HEIGHT+5));
        glayFlyData->addWidget(labelArr[i+8], i, 0);
        glayFlyData->addWidget(TEArr[i+8], i, 1);
    }
    gboxFlyData->setLayout(glayFlyData);
    gboxFlyData->resize(300, MAINWINDOW_HEIGHT);
    gboxFlyData->move(300, 0);
    gboxFlyData->show();


    //-[Config]
    QGroupBox *gboxConfig = new QGroupBox("Config", this);
    QGridLayout *glayConfig = new QGridLayout;
    TEArr[TEXTEDITC-1]->move(700, 10);
    labelArr[TEXTEDITC-1]->move(600, 10);
    glayConfig->addWidget(labelArr[TEXTEDITC-1], 0, 0);
    glayConfig->addWidget(TEArr[TEXTEDITC-1], 0, 1);
    gboxConfig->setLayout(glayConfig);
    gboxConfig->resize(300, 80);
    gboxConfig->move(600, 0);
    gboxConfig->show();

    TEArr[0]->setFocus();   //-курсор на старт


    //-кнопка -=сохраниться=-
    this->btnSave = new QPushButton("&Save", this);
    this->btnSave->move(630, MAINWINDOW_HEIGHT - 50);
    connect(this->btnSave, &QPushButton::released, this, &MainWindow::btnSaveReleased);

    //-кнопка -=выйти=-
    this->btnQuit = new QPushButton("&Quit", this);
    this->btnQuit->move(MAINWINDOW_WIDTH - 150, MAINWINDOW_HEIGHT - 50);
    connect(this->btnQuit, &QPushButton::released, this, &MainWindow::btnQuitReleased);


    //-загрузим данные из .ini ------------------------------------------------
    load_from_file();


} //MainWindow::do_stuff()

//-----------------------------------------------------------------------------
void MainWindow::load_from_file()
/**
 * в цикле читаем строки из файла
 * сравниваем строки на наличие начального "[" и конечного "]"
 * в таком случае получаем строку в скобочках, по ней
 * пустые строки пропускаем
 *
 */
{
    //-получим имя файла
    QString fileNameFull = QCoreApplication::applicationDirPath() + "/ini/rdc450.ini";
    std::cout << "INI FILE TO READ:\n" << fileNameFull.toStdString() << std::endl;


    //-читаем из файла
    QFile inputFile(fileNameFull);

    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        in.setCodec("UTF-8");      //-спасибо qt за наше счастливое детство
        uint no = 0;    //-counter

        while (!in.atEnd()) //-читаем файл
        {
            QString line = in.readLine();

            if (!line.isEmpty())
            {
                //-проверка на [категорию]
                if (line[0] == '[' && line[line.length()-1] == ']')
                {
                    //it's a category, do nothing
                }
                else    //-основное здесь
                    //-оставляем только value без key
                    TEArr[no++]->setText(line.mid(line.lastIndexOf(INI_PARAM_DELIMITER)+1));

            }
        }
        inputFile.close();
    }
    else
    {
        std::cout << "Unable to open file " << fileNameFull.toStdString() << std::endl;
        std::exit(1);
    }


} //MainWindow::load_from_file


//-----------------------------------------------------------------------------
void MainWindow::save_to_file()
{
    //-получим имя файла с полным путём к нему
    QString fileNameFull = QCoreApplication::applicationDirPath() + "/ini/rdc450.ini";
    std::cout << "INI FILE TO WRITE:\n" << fileNameFull.toStdString() << std::endl;

    QFile file_out(fileNameFull);
    if (!file_out.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        std::cout << "error opening file for writing!\n";
        return;
    }

    QTextStream out(&file_out);
    out.setCodec("UTF-8");      //-спасибо qt за наше счастливое детство

    for (uint i = 0; i < TEXTEDITC; i++)
    {
        switch (i)
        {
            case (0):
                out << "[BasicData]\n"; //0x0D0A;
            break;
            case (8):
                out << "\n[FlyData]\n"; //0x0D0A;
            break;
            case (TEXTEDITC-1):
                out << "\n[Config]\n"; //0x0D0A;
            break;

        }

        //-выводим параметры и значения через '='
        out << configKeyArray[i] << INI_PARAM_DELIMITER << TEArr[i]->toPlainText() << "\n"; //0x0D0A;
        std::cout << "to file [" << i << "] => " << TEArr[i]->toPlainText().toStdString() << std::endl;
    }
} //MainWindow::save_to_file()

//-----------------------------------------------------------------------------
void MainWindow::btnSaveReleased()
{
    this->save_to_file();
} //MainWindow::btnSaveReleased()

//-----------------------------------------------------------------------------
void MainWindow::btnQuitReleased()
{
    this->save_to_file();

    exit(0);
} //MainWindow::btnQuitReleased()

