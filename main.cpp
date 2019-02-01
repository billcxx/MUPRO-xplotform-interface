#include "mupromain.h"
#include "patternreco.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    patternReco w;
//    muproMain w;
    w.show();

    return a.exec();
}
