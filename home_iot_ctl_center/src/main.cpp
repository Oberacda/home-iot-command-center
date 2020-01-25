// main.cpp

#include "main.hpp"

#include <QApplication>
#include <QTableView>

#include <iot/home.hpp>

#include "homeiotctlcenter.hpp"




/////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    HomeIotCtlCenter root;
    root.show();

    auto home = new Home();

    delete home;

    return QApplication::exec();
}