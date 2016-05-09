#include "mupromain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    muproMain w;
    w.show();

    return a.exec();
}
