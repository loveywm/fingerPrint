#include <QtGui/QApplication>
#include "widget.h"
#include "widget1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Widget w;
    widget1 w;
    w.show();

    return a.exec();
}
