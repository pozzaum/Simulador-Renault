#include "mainwindow.h"

#include <QApplication>
//#include <QLocale>
//#include <QTranslator>

/**
 * @brief main
 * Program's main function
 *
 * This function calls the translator and Qt MainWindow object which has all the functions respnsible for data gathering and simulation.
 * @param argc
 * @param argv
 * @return
 */

int main(int argc, char *argv[])
{
    qDebug() << "Antes do QApplication";
    QApplication a(argc, argv);
    qDebug() << "QApplication criado";

    MainWindow w;
    w.show();
    return a.exec();
}
