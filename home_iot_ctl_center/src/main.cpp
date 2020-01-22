// main.cpp

#include "main.hpp"

#include <QApplication>
#include <QTableView>

#include <iot/home.hpp>
#include "mymodel.hpp"




/////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTableView tableView;
    MyModel myModel;
    tableView.setModel(&myModel);
    tableView.show();

    auto home = new Home();

    delete home;

    return QApplication::exec();
}