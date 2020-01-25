#ifndef HOMEIOTCTLCENTER_H
#define HOMEIOTCTLCENTER_H

#include <QMainWindow>

namespace Ui {
class HomeIotCtlCenter;
}

class HomeIotCtlCenter : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomeIotCtlCenter(QWidget *parent = nullptr);
    ~HomeIotCtlCenter();

private:
    Ui::HomeIotCtlCenter *ui;
};

#endif // HOMEIOTCTLCENTER_H
