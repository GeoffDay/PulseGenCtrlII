#include <QApplication>
#include "PulseGenCtrl2.h"

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    PulseGenCtrl2 w;
    w.show();
    
    return a.exec();
}
