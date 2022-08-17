#include "testcontrol.h"
#include "ui_testcontrol.h"
#include "maincontrol.h"
#include <QInputDialog>

#include <QTextCodec>
#include <QSettings>
#define CONGIG_DEV  "CutControlConf.ini"


void TestControl::WriteConfig(QString key,QString value)
{
    QSettings *configIniWrite = new QSettings(CONGIG_DEV, QSettings::IniFormat);
    configIniWrite->setValue(key, value.toStdString().c_str());
    delete configIniWrite;
}

QString TestControl::ReadConfig(QString key,QString defaultvalue)
{
    QSettings *configIniRead = new QSettings(CONGIG_DEV, QSettings::IniFormat);
    QString value = configIniRead->value(key,"").toString();
    if(value == "")
    {
        value = defaultvalue;
    }
    delete configIniRead;
    return value;
}


TestControl::TestControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestControl)
{
    ui->setupUi(this);
    AXIS1STATUS = false;
    AXIS2STATUS = false;
    AXIS3STATUS = false;

    AXIS1Conf = false;
    AXIS2Conf = false;
    AXIS3Conf = false;

    gtsthread = new GtsThread(this);
    mythread = new QThread();
    gtsthread->moveToThread(mythread);

    connect(this,SIGNAL(GTSDoEmit(int,int,double,double)),gtsthread,SLOT(GTSDoProc(int,int,double,double)),Qt::QueuedConnection);
    connect(gtsthread,SIGNAL(SendStatus(int,int,double,double)),this,SLOT(ShowStatus(int,int,double,double)),Qt::QueuedConnection);
    mythread->start();

}

TestControl::~TestControl()
{
    qDebug()<<"~TestControl";
    delete ui;
}

void TestControl::ShowStatus(int index,int code,double value0,double value1)
{
    switch (index)
    {
        case GTSINIT:
            if( code >= 0)
            {
                ui->BtInit->setText(QString::fromLocal8Bit("初始化完成"));
            }
            else
            {
                ui->BtInit->setText(QString::fromLocal8Bit("初始化失败"));
            }
            break;
         case GTSCLEAR:
            if( code >= 0)
            {
                ui->BtClear->setText(QString::fromLocal8Bit("清除故障完成"));
            }
            else
            {
                ui->BtClear->setText(QString::fromLocal8Bit("清除故障失败"));
            }
            break;
         case GTSGOHOME:
            if( code >= 0)
            {
                ui->BtHome->setText(QString::fromLocal8Bit("回HOME完成"));
            }
            else if(code == -1)
            {
                ui->BtHome->setText(QString::fromLocal8Bit("回HOME失败"));
            }
            else
            {
                ui->BtHome->setText(QString::fromLocal8Bit("回HOME超时"));
            }
            break;
         case GTSGOZERO:
            if( code >= 0)
            {
                ui->BtToZero->setText(QString::fromLocal8Bit("到0点"));
            }
            else
            {
                ui->BtToZero->setText(QString::fromLocal8Bit("到0失败"));
            }
            break;
         case GTSGOUP:
            if( code >= 0)
            {
                ui->BtToUp->setText(QString::fromLocal8Bit("到上料位"));
            }
            else
            {
                ui->BtToUp->setText(QString::fromLocal8Bit("到上料位失败"));
            }
            break;
        case GTSGODOWN:
           if( code >= 0)
           {
               ui->BtToDown->setText(QString::fromLocal8Bit("到下料位"));
           }
           else
           {
               ui->BtToDown->setText(QString::fromLocal8Bit("到下料位失败"));
           }
           break;
         case GTSJOGAX1EABLE:
            if( code >= 0)
            {
                if(value0 > 0 )
                {
                    ui->STATUS1->setStyleSheet("background-color:rgb(0,255,0)");
                    ui->AXIS1->setText(QString::fromLocal8Bit("AXIS1 OFF"));
                    ui->STATUS1->setText(QString::fromLocal8Bit("enable"));
                }
                else
                {
                    ui->STATUS1->setStyleSheet("");
                    ui->AXIS1->setText(QString::fromLocal8Bit("AXIS1 ON"));
                    ui->STATUS1->setText(QString::fromLocal8Bit("disable"));

                }
            }
            break;
            case GTSJOGAX2EABLE:
        if( code >= 0)
        {
            if(value0 > 0 )
            {
                ui->STATUS2->setStyleSheet("background-color:rgb(0,255,0)");
                ui->AXIS2->setText(QString::fromLocal8Bit("AXIS2 OFF"));
                ui->STATUS2->setText(QString::fromLocal8Bit("enable"));
            }
            else
            {
                ui->STATUS2->setStyleSheet("");
                ui->AXIS2->setText(QString::fromLocal8Bit("AXIS2 ON"));
                ui->STATUS2->setText(QString::fromLocal8Bit("disable"));

            }
        }
               break;
            case GTSJOGAX3EABLE:
                if( code >= 0)
                {
                    if(value0 > 0 )
                    {
                        ui->STATUS3->setStyleSheet("background-color:rgb(0,255,0)");
                        ui->AXIS3->setText(QString::fromLocal8Bit("AXIS3 OFF"));
                        ui->STATUS3->setText(QString::fromLocal8Bit("enable"));
                    }
                    else
                    {
                        ui->STATUS3->setStyleSheet("");
                        ui->AXIS3->setText(QString::fromLocal8Bit("AXIS3 ON"));
                        ui->STATUS3->setText(QString::fromLocal8Bit("disable"));

                    }
                }
//               if( code >= 0)
//               {
//                   ui->AXIS3->setStyleSheet("background-color:rgb(0,255,0)");
//                   ui->AXIS3->setText(QString::fromLocal8Bit("AXIS3 OFF"));
//               }
//               else
//               {
//                   ui->AXIS3->setStyleSheet("background-color:rgb(255,0,0)");
//                   ui->AXIS3->setText(QString::fromLocal8Bit("AXIS3 ON"));
//               }
               break;
            case GTSJOGAX1CONF:
                ui->LeSpc1->setText(QString::number(value0, 'f', 3));
                ui->LePos1->setText(QString::number(value1, 'f', 3));
                break;
            case GTSJOGAX2CONF:
                ui->LeSpc2->setText(QString::number(value0, 'f', 3));
                ui->LePos2->setText(QString::number(value1, 'f', 3));
                break;
            case GTSJOGAX3CONF:
                ui->LeSpc3->setText(QString::number(value0, 'f', 3));
                ui->LePos3->setText(QString::number(value1, 'f', 3));
                break;
            case GTSCRDPRM:
                if(code > 0)
                {
                    ui->BtTestLine->setText(QString::fromLocal8Bit("测试"));
                    ui->BtTestRound->setText(QString::fromLocal8Bit("测试"));
                }
                break;
        default:
            break;
    }
    return;
}

//测试页面返回
void TestControl::on_BtBack_clicked()
{
    mythread->quit();
    mythread->wait();
    delete gtsthread;
    emit showMainUi();
    this->close();
}

//测试页面初始化
void TestControl::on_BtInit_clicked()
{
    ui->BtInit->setText(QString::fromLocal8Bit("初始化中"));
    emit GTSDoEmit(GTSINIT);
}

//测试页面清除警报
void TestControl::on_BtClear_clicked()
{
    emit GTSDoEmit(GTSCLEAR);
}


//测试页面回HOME
void TestControl::on_BtHome_clicked()
{
    ui->BtHome->setText(QString::fromLocal8Bit("回HOME中"));
    emit GTSDoEmit(GTSGOHOME,ui->CbAXISSelect->currentIndex()+1);
}

//测试页面设置0点
void TestControl::on_BtZero_clicked()
{
    bool ok;
    QString axis = ui->CbAXISSelect->currentText();

    QString zero = ReadConfig("/"+axis+"/motocontrol/zero","0.0");
    double zerovalue = QInputDialog::getDouble(this,QString::fromLocal8Bit("设置0点 "),QString::fromLocal8Bit("请输入0点数值"),zero.toDouble(),-65535,65535,3,&ok);
    if(ok)
    {
        qDebug()<<"zerovalue"<<zerovalue;
        WriteConfig("/"+axis+"/motocontrol/zero",QString::number(zerovalue, 'f', 3));
    }
}

//测试页面设置上料位
void TestControl::on_BtUp_clicked()
{
    bool ok;
    QString axis = ui->CbAXISSelect->currentText();
    QString up = ReadConfig("/"+axis+"/motocontrol/up","0.0");
    double upvalue = QInputDialog::getDouble(this,QString::fromLocal8Bit("设置上料位 "),QString::fromLocal8Bit("请输入上料位数值"),up.toDouble(),-65535,65535,3,&ok);
    if(ok)
    {
        qDebug()<<"zerovalue"<<upvalue;
        WriteConfig("/"+axis+"/motocontrol/up",QString::number(upvalue, 'f', 3));
    }

}

//测试页面设置下料位
void TestControl::on_BtDown_clicked()
{
    bool ok;
    QString axis = ui->CbAXISSelect->currentText();
    QString down = ReadConfig("/"+axis+"/motocontrol/down","0.0");
    double downvalue = QInputDialog::getDouble(this,QString::fromLocal8Bit("设置下料位 "),QString::fromLocal8Bit("请输入下料位数值"),down.toDouble(),-65535,65535,3,&ok);
    if(ok)
    {
        qDebug()<<"zerovalue"<<downvalue;
        WriteConfig("/"+axis+"/motocontrol/down",QString::number(downvalue, 'f', 3));
    }

}

//测试页面到0点
void TestControl::on_BtToZero_clicked()
{
    double zerovalue = 0.0;
    QString axis = ui->CbAXISSelect->currentText();
    QString zero = ReadConfig("/"+axis+"/motocontrol/zero","");
    if(zero != "")
    {
        ui->BtToZero->setText(QString::fromLocal8Bit("到0位中"));
        zerovalue = zero.toDouble();
        emit GTSDoEmit(GTSGOZERO,ui->CbAXISSelect->currentIndex()+1,zerovalue);
    }

}


//测试页面到上料位
void TestControl::on_BtToUp_clicked()
{
    double upvalue = 0.0;
    QString axis = ui->CbAXISSelect->currentText();
    QString up = ReadConfig("/"+axis+"/motocontrol/up","");
    if(up != "")
    {
        ui->BtToUp->setText(QString::fromLocal8Bit("到上料位中"));
        upvalue = up.toDouble();
        emit GTSDoEmit(GTSGOUP,ui->CbAXISSelect->currentIndex()+1,upvalue);
    }
}

//测试页面到下料位
void TestControl::on_BtToDown_clicked()
{
    double downvalue = 0.0;
    QString axis = ui->CbAXISSelect->currentText();
    QString down = ReadConfig("/"+axis+"/motocontrol/down","");
    if(down != "")
    {
        ui->BtToDown->setText(QString::fromLocal8Bit("到下料位中"));
        downvalue = down.toDouble();
        emit GTSDoEmit(GTSGODOWN,ui->CbAXISSelect->currentIndex()+1,downvalue);
    }
}

//设置JOG模式X轴状态
void TestControl::on_AXIS1_clicked()
{
    if(AXIS1STATUS)
    {

        emit GTSDoEmit(GTSJOGAX1EABLE,0);
        AXIS1STATUS = false;
    }
    else
    {
        emit GTSDoEmit(GTSJOGAX1EABLE,1);
        AXIS1STATUS = true;
    }
    qDebug()<<"on_AXIS1_clicked "<<AXIS1STATUS;
}

//设置JOG模式Y轴状态
void TestControl::on_AXIS2_clicked()
{
    if(AXIS2STATUS)
    {
        emit GTSDoEmit(GTSJOGAX2EABLE,0);
        AXIS2STATUS = false;
    }
    else
    {
        emit GTSDoEmit(GTSJOGAX2EABLE,1);
        AXIS2STATUS = true;
    }
}

//设置JOG模式Z轴状态
void TestControl::on_AXIS3_clicked()
{
    if(AXIS3STATUS)
    {
        emit GTSDoEmit(GTSJOGAX3EABLE,0);
        AXIS3STATUS = false;
    }
    else
    {
        emit GTSDoEmit(GTSJOGAX3EABLE,1);
        AXIS3STATUS = true;
    }
}

//设置JOG模式X轴配置生效
void TestControl::on_BtAX1Conf_clicked()
{
    if(!AXIS1STATUS)
    {
        return;
    }
    if(AXIS1Conf)
    {
        emit GTSDoEmit(GTSJOGAX1CONF,0,ui->Sudo1->text().toDouble(),ui->LeDis1->text().toDouble());
        AXIS1Conf = false;
        ui->BtAX1Conf->setText(QString::fromLocal8Bit("启动"));
    }
    else
    {
        emit GTSDoEmit(GTSJOGAX1CONF,1,ui->Sudo1->text().toDouble(),ui->LeDis1->text().toDouble());
        AXIS1Conf = true;
        ui->BtAX1Conf->setText(QString::fromLocal8Bit("停止"));
    }
}

//设置JOG模式Y轴配置生效
void TestControl::on_BtAX2Conf_clicked()
{
    if(!AXIS2STATUS)
    {
        return;
    }
    if(AXIS2Conf)
    {
        emit GTSDoEmit(GTSJOGAX2CONF,0,ui->Sudo2->text().toDouble(),ui->LeDis2->text().toDouble());
        AXIS2Conf = false;
        ui->BtAX2Conf->setText(QString::fromLocal8Bit("启动"));
    }
    else
    {
        emit GTSDoEmit(GTSJOGAX2CONF,1,ui->Sudo2->text().toDouble(),ui->LeDis2->text().toDouble());
        AXIS2Conf = true;
        ui->BtAX2Conf->setText(QString::fromLocal8Bit("停止"));
    }

}

//设置JOG模式Z轴配置生效
void TestControl::on_BtAX3Conf_clicked()
{
    if(!AXIS3STATUS)
    {
        return;
    }
    if(AXIS3Conf)
    {
        emit GTSDoEmit(GTSJOGAX3CONF,0,ui->Sudo3->text().toDouble(),ui->LeDis3->text().toDouble());
        AXIS3Conf = false;
        ui->BtAX3Conf->setText(QString::fromLocal8Bit("启动"));
    }
    else
    {
        emit GTSDoEmit(GTSJOGAX3CONF,1,ui->Sudo3->text().toDouble(),ui->LeDis3->text().toDouble());
        AXIS3Conf = true;
        ui->BtAX3Conf->setText(QString::fromLocal8Bit("停止"));
    }
}

//设置JOG模式L轴配置生效
void TestControl::on_BtAX4Conf_clicked()
{

}

void TestControl::on_BtStop_clicked()
{
    gtsthread->TermAction();
}

void TestControl::on_BtTestLine_clicked()
{
    int nRet = -1;
    int dimension       =   2;//为二维坐标系
    double synVelMax    =   500;
    double synAccMax    =   1;
    int evenTime        =   50;
    int profile0        =   1;
    int profile1        =   2;
    int setOriginFlag   =   1;
    long originPos0      =   ui->LETestLineStX->text().toLong();
    long originPos1      =   ui->LETestLineStY->text().toLong();

    nRet = gtsthread->CrdPrmSet(dimension,synVelMax, synAccMax, evenTime, profile0, profile1, setOriginFlag, originPos0, originPos1);
    qDebug()<<"CrdPrmSet"<<nRet;
    if(nRet == 0)
    {
        nRet = gtsthread->AddCrdPrmLine(ui->LETestLineEnX->text().toLong(),ui->LETestLineEnY->text().toLong(),ui->LETestLineSpd->text().toDouble(),0.1,0);
        qDebug()<<"AddCrdPrm"<<nRet;
        emit GTSDoEmit(GTSCRDPRM,1);
        ui->BtTestLine->setText(QString::fromLocal8Bit("测试中"));
    }

}

void TestControl::on_BtTestRound_clicked()
{
    int nRet = -1;
    int dimension       =   2;//为二维坐标系
    double synVelMax    =   500;
    double synAccMax    =   1;
    int evenTime        =   50;
    int profile0        =   1;
    int profile1        =   2;
    int setOriginFlag   =   1;
    long originPos0      =   ui->LETestLineStX->text().toLong();
    long originPos1      =   ui->LETestLineStY->text().toLong();

    nRet = gtsthread->CrdPrmSet(dimension,synVelMax, synAccMax, evenTime, profile0, profile1, setOriginFlag, originPos0, originPos1);
    qDebug()<<"CrdPrmSet"<<nRet;
    if(nRet == 0)
    {
        nRet = gtsthread->AddCrdPrmR(ui->LETestLineEnX->text().toLong(),ui->LETestLineEnY->text().toLong(),
               ui->LETestRoundD->text().toLong(),0, ui->LETestRoundSpd->text().toDouble(),0.1,0);
        qDebug()<<"AddCrdPrm"<<nRet;
        emit GTSDoEmit(GTSCRDPRM,1);
        ui->BtTestRound->setText(QString::fromLocal8Bit("测试中"));
    }
}

void TestControl::on_BtTestStop_clicked()
{
    emit GTSDoEmit(GTSCRDSTOP,1);
    ui->BtTestLine->setText(QString::fromLocal8Bit("测试"));
    ui->BtTestRound->setText(QString::fromLocal8Bit("测试"));
}
