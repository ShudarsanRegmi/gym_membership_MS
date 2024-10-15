#include "mainwindow.h"

#include <QApplication>
#include "databaseapi.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseAPI *dbApi = new DatabaseAPI();
    MainWindow w(dbApi);
    w.show();
    return a.exec();
}
