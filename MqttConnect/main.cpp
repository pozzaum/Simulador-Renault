#include "mymqtt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myMqtt w;
    w.show();
    return a.exec();
}
