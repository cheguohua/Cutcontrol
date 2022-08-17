#ifndef GTSTHREAD_H

#define GTSTHREAD_H

#include <QThread>
#include <QDebug>
#include <QObject>
#include <QTimer>
#define GTSINIT             1
#define GTSCLEAR            2
#define GTSGOHOME           3
#define GTSSETZERO          4
#define GTSSETUP            5
#define GTSSETDOWN          6
#define GTSGOZERO           7
#define GTSGOUP             8
#define GTSGODOWN           9

#define GTSJOGAX1EABLE      10
#define GTSJOGAX2EABLE      11
#define GTSJOGAX3EABLE      12

#define GTSJOGAX1CONF       13
#define GTSJOGAX2CONF       14
#define GTSJOGAX3CONF       15

#define GTSCRDPRM           16

#define GTSCRDSTOP          17


typedef struct actionparam_{
    bool    active;
    double  spc;
    double  nextspc;
    double  positon;
    double  adc;
}actionparam;

typedef struct crdparam_{
    int     typid;
    long    x;
    long    y;
    long    centerx;
    long    centery;
    long    direct;
    long    radius;
    double     spc;
    double     acc;
    double     endspc;
}crdparam;

typedef struct crdactive_{
    bool        active;
    int         number;
    crdparam    param[512];
}crdactive;

class GtsThread : public QObject
{
    Q_OBJECT
public:
    GtsThread(QObject *parent);
    ~GtsThread()
    {
        mytimer->stop();
        GtsExit();
        qDebug() << "~GtsThread";
    }
    int GtsClearStatus();
    int GtsGoHome(int index);
    int GtsInit();
    int GtsExit();
    int GtsGoPosition(short index,long position);
    bool m_gtsstatus;
    QTimer* mytimer;
    bool m_Terminate;//终止当前动作
    actionparam axiparam1;
    actionparam axiparam2;
    actionparam axiparam3;
    crdactive   crdactive1;
    void TermAction();
    int CrdPrmSet(int dimension,double synVelMax,double synAccMax,int evenTime,int profile0,int profile1,int setOriginFlag,long originPos0,long originPos1);
    int AddCrdPrmLine(long x,long y,double spc,double acc,double endspc);
    int AddCrdPrmC(long x,long y,long centerx,long centery,long direct,double spc,double acc,double endspc);
    int AddCrdPrmR(long x,long y,long radius,long direct, double spc,double acc,double endspc);
//    virtual void run();//任务处理线程
signals:
    void SendStatus(int index,int code,double value0 = 0,double value1 = 0.0);
public slots:
    void GTSDoProc(int index,int value0, double value1 = 0.0, double value2 = 0.0);
    void onTimerOut();
};

#endif // GTSTHREAD_H
