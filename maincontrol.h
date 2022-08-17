#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include <QMainWindow>
#include <QDir>
#include <QListWidgetItem>
#include <QFileInfoList>
#include <QListWidget>
#include "camera/CamThread.h"
#include "testcontrol.h"
#include "dxf/include/dl_dxf.h"
#include "dxf/include/dl_creationclass.h"

namespace Ui {
class MainControl;
}

class MainControl : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainControl(QWidget *parent = 0);
    ~MainControl();
    CamThread* Camtask;
    bool preview;
    QList<Vertexdxf>dxfworklist;
    GtsThread* gtsthread;
    QThread* mythread;
    bool DxfWorking;
    long dxfindex;
    void showFileInfoList(QFileInfoList list);
private slots:
    void on_BtMianExit_clicked();
    void display(int index);
    void on_Bttestcontrol_clicked();
    void DisplayMainUi();
    void on_BtMainSet_clicked();

    void on_BtPreviewMain_clicked();

    void on_BtMainStar_clicked();

    void on_BtMainStop_clicked();
    void ShowStatus(int index,int code = 0,double value0 = 0,double value1 = 0.0);
    void on_BtPrjBrowe_clicked();
    //--显示当前目录下的所有文件
    void slotShow(QDir dir);
    //----根据选择显示下一级目录下的文件，
    void slotDirShow(QListWidgetItem *Item);
signals:
    void GTSDoEmit(int index,int value0=0 ,double value1=0.0,double value2=0.0);
private:
    Ui::MainControl *ui;
    QListWidget *fileListWidget;
    QFileInfoList list;
};

#endif // MAINCONTROL_H
