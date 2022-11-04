#include "MySnipaste.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MySnipaste w;
    w.show();
    return a.exec();
}
