#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QSettings>
#include <QMainWindow>
#include <QDebug>
#include <QFile>

#include <iostream>
#include <QtWidgets>


const uint MAINWINDOW_WIDTH = 950;
const uint MAINWINDOW_HEIGHT = 350;
const uint TEXTEDIT_HEIGHT = 23;
const uint TEXTEDIT_WIDTH = 50;
const uint TEXTEDITC = 16;
const char INI_PARAM_DELIMITER = '=';



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    //-[BasicData]
    QTextEdit*  teRDCN;
    QTextEdit*  teRDCNRec;
    QTextEdit*  teEngineType;
    QTextEdit*  teEngineN;
    QTextEdit*  teUser;
    QTextEdit*  teLogged;
    QTextEdit*  teComment;
    QTextEdit*  teND450N;

    //-[FlyData]
    QTextEdit*  teFlightN;
    QTextEdit*  teAPTakeOf;
    QTextEdit*  teAPArrive;
    QTextEdit*  teFlightDate;
    QTextEdit*  teFlightStartTime;
    QTextEdit*  teBoardN;
    QTextEdit*  teType;

    //-[Config]
    QTextEdit*  teShowFlightWin;

    //-arr of TEs
    QTextEdit*  TEArr[TEXTEDITC] = {
                            teRDCN,
                            teRDCNRec,
                            teEngineType,
                            teEngineN,
                            teUser,
                            teLogged,
                            teComment,
                            teND450N,
                            teFlightN,
                            teAPTakeOf,
                            teAPArrive,
                            teFlightDate,
                            teFlightStartTime,
                            teBoardN,
                            teType,
                            teShowFlightWin,
                            };

    //-[BasicData]
    QLabel*  labelRDCN;
    QLabel*  labelRDCNRec;
    QLabel*  labelEngineType;
    QLabel*  labelEngineN;
    QLabel*  labelUser;
    QLabel*  labelLogged;
    QLabel*  labelComment;
    QLabel*  labelND450N;

    //-[FlyData]
    QLabel*  labelFlightN;
    QLabel*  labelAPTakeOf;
    QLabel*  labelAPArrive;
    QLabel*  labelFlightDate;
    QLabel*  labelFlightStartTime;
    QLabel*  labelBoardN;
    QLabel*  labelType;

    //-[Config]
    QLabel*  labelShowFlightWin;

    //-arr of TEs
    QLabel*  labelArr[TEXTEDITC] = {
                            labelRDCN,
                            labelRDCNRec,
                            labelEngineType,
                            labelEngineN,
                            labelUser,
                            labelLogged,
                            labelComment,
                            labelND450N,
                            labelFlightN,
                            labelAPTakeOf,
                            labelAPArrive,
                            labelFlightDate,
                            labelFlightStartTime,
                            labelBoardN,
                            labelType,
                            labelShowFlightWin,
                            };

    QString labelNameArray[TEXTEDITC] = {
                            "&RDCN",
                            "RDCNRec",
                            "EngineType",
                            "EngineN",
                            "User",
                            "Logged",
                            "Comment",
                            "ND450N",
                            "&FlightN",
                            "APTakeOf",
                            "APArrive",
                            "FlightDate",
                            "FlightStartTime",
                            "BoardN",
                            "Type",
                            "S&howFlightWin",
                            };

    QString configKeyArray[TEXTEDITC] = {
                            "RDCN",
                            "RDCNRec",
                            "EngineType",
                            "EngineN",
                            "User",
                            "Logged",
                            "Comment",
                            "ND450N",
                            "FlightN",
                            "APTakeOf",
                            "APArrive",
                            "FlightDate",
                            "FlightStartTime",
                            "BoardN",
                            "Type",
                            "ShowFlightWin",
                        };

    QPushButton*        btnSave;
    QPushButton*        btnQuit;

//    std::unordered_map<std::string, std::string> pt;
//    std::unordered_map<QString, QString> fv;



    //-methods ----------------------------------------------------------------
    Ui::MainWindow *ui;
    void do_stuff(void);
    void load_from_file(void);
    void save_to_file(void);

    void btnSaveReleased(void);
    void btnQuitReleased(void);






}; //-class MainWindow
#endif // MAINWINDOW_H
