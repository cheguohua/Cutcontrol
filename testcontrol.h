 #ifndef TESTCONTROL_H
#define TESTCONTROL_H

#include <QWidget>
#include "gts/Gtsthread.h"

namespace Ui {
class TestControl;
}

class TestControl : public QWidget
{
    Q_OBJECT

public:
    explicit TestControl(QWidget *parent = 0);
    ~TestControl();
    GtsThread* gtsthread;
    QThread* mythread;
    void WriteConfig(QString key,QString value);
    QString TestControl::ReadConfig(QString key,QString defaultvalue);
    bool AXIS1STATUS;
    bool AXIS2STATUS;
    bool AXIS3STATUS;

    bool AXIS1Conf;
    bool AXIS2Conf;
    bool AXIS3Conf;
private slots:
    void on_BtBack_clicked();
    void on_BtInit_clicked();
    void ShowStatus(int index,int code = 0,double value0 = 0,double value1 = 0.0);
    void on_BtClear_clicked();

    void on_BtHome_clicked();

    void on_BtZero_clicked();

    void on_BtUp_clicked();

    void on_BtDown_clicked();

    void on_BtToZero_clicked();

    void on_BtToUp_clicked();

    void on_BtToDown_clicked();

    void on_AXIS1_clicked();

    void on_AXIS2_clicked();

    void on_AXIS3_clicked();

    void on_BtAX1Conf_clicked();

    void on_BtAX2Conf_clicked();

    void on_BtAX3Conf_clicked();

    void on_BtAX4Conf_clicked();

    void on_BtStop_clicked();

    void on_BtTestLine_clicked();

    void on_BtTestRound_clicked();

    void on_BtTestStop_clicked();

signals:
    void showMainUi();
    void GTSDoEmit(int index,int value0=0 ,double value1=0.0,double value2=0.0);
private:
    Ui::TestControl *ui;
};

#endif // TESTCONTROL_H
