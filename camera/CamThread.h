#ifndef CAMTHREAD_H

#define CAMTHREAD_H

#include <QThread>
#include <QDebug>
class CamThread : public QThread
{
    Q_OBJECT
public:
    CamThread(QObject *parent);
    ~CamThread()
    {
        CamStop();
        CamExit();
        qDebug() << "~CamThread";
    }
    void DestroyThread();
    void StopThread();
    void ResumeThread();
    int CamInit();
    int CamStart();
    int CamStop();
    int CamExit();
    int SetExposureTime(float ExposureTime);
    bool m_bRun;
    bool m_bStop;
    float m_ExposureTime;
    virtual void run();//任务处理线程
signals:
    void showimage(int index);
public slots:
 

};

#endif // CAMTHREAD_H
