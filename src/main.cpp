#include <QApplication>
#include "../includes/authorization.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Authorization au;
    au.show();

    return a.exec();
}