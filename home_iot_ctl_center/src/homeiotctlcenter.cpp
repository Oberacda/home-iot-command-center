#include "homeiotctlcenter.hpp"
#include "ui_homeiotctlcenter.h"

HomeIotCtlCenter::HomeIotCtlCenter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomeIotCtlCenter)
{
    ui->setupUi(this);
}

HomeIotCtlCenter::~HomeIotCtlCenter()
{
    delete ui;
}
