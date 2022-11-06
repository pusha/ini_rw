#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
/**
 * Keys (properties)
 * Sections
 * Case sensitivity. Section and property names are case insensitive.
 * Comments - linestart semicolons
 * delimiter - equals sign
 * hierarchy - abscent
 *
 *
 * Technically, there is a standard string class to store any type of character: std::basic_string. std::string and std::wstring are nothing but specializations of std::basic_string for char and wchar. There are also the specializations std::u16string and std::u32string that are meant for UTF-16 and UTF-32 storage.
 *
 * app icon
 *
 *
 * compiled-in dll's
 */
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("RDC450");
    w.resize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);
    w.setMaximumSize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);
    w.setMinimumSize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);
    w.show();

    return a.exec();
}


