#include "Gtsthread.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <QDateTime>
#include "include/gts.h"
#include <QDebug>
#define GTS_OK	0
#define CORE    1   //核心数 (card-1)*2+1 and (card-1)*2+2
#define AXIS1   1   //X轴
#define AXIS2   2   //Y轴
#define AXIS3   3   //Z轴

#define CRDINDEX 1 //规划器索引

#define TYPELINE  1 //直线
#define TYPEROUND 2 //圆
#define TYPECRIL  3 //圆弧

//初始化运动板卡
int GtsThread::GtsInit()
{
    int nRet = CMD_SUCCESS;
    if(m_gtsstatus)
    {
        return 0;
    }
    do
    {
        //打开运动控制器
        nRet = GTN_Open();
        if (CMD_SUCCESS != nRet)
        {
            qDebug()<<"GTN_Open:"<<nRet;
            break;
        }

        //重置运动控制器
        nRet = GTN_Reset(CORE);
        if (CMD_SUCCESS != nRet)
        {
            qDebug()<<"GTN_Reset:"<<nRet;
            break;
        }

        //下载配置文件 主要为了给电机初始位置
        nRet = GTN_LoadConfig(CORE,"gtn_core1.cfg");
        if (CMD_SUCCESS != nRet)
        {
            qDebug()<<"GTN_Reset:"<<nRet;
            break;
        }

        //清除X轴位置
        nRet = GTN_ClrSts(CORE,AXIS1,1);
        if (CMD_SUCCESS != nRet)
        {
            qDebug()<<"GTN_ClrSts X:"<<nRet;
            break;
        }

        //清除Y轴位置
        nRet = GTN_ClrSts(CORE,AXIS2,1);
        if (CMD_SUCCESS != nRet)
        {
            qDebug()<<"GTN_ClrSts Y:"<<nRet;
            break;
        }

        //清除Z轴位置
        nRet = GTN_ClrSts(CORE,AXIS3,1);
        if (CMD_SUCCESS != nRet)
        {
            qDebug()<<"GTN_ClrSts Z:"<<nRet;
            break;
        }
    } while (0);
    if(CMD_SUCCESS != nRet)
    {
        return -1;
    }
    m_gtsstatus = true;
    return 0;
}


//关闭运动板卡
int GtsThread::GtsExit()
{
    int nRet = CMD_SUCCESS;
    if(!m_gtsstatus)
    {
        return 0;
    }
    do{

        nRet = GTN_Stop(CORE,AXIS1,1);
        nRet = GTN_AxisOff(CORE,AXIS1);
        qDebug()<< "close 1";
        nRet = GTN_Stop(CORE,AXIS2,1);
        nRet = GTN_AxisOff(CORE,AXIS2);
        qDebug()<< "close 2";
        nRet = GTN_Stop(CORE,AXIS3,1);
        nRet = GTN_AxisOff(CORE,AXIS3);
        qDebug()<< "close 3";
        //关闭设备
        nRet = GTN_Close();
        if (CMD_SUCCESS != nRet)
        {
            break;
        }
    } while (0);
    return 0;
}

//清除故障
int GtsThread::GtsClearStatus()
{
    int nRet = CMD_SUCCESS;
    if(!m_gtsstatus)
    {
        return 0;
    }
    //清除X轴状态
    nRet = GTN_ClrSts(CORE,AXIS1,1);
    if (CMD_SUCCESS != nRet)
    {
        qDebug()<<"GTN_ClrSts X:"<<nRet;
    }

    //清除Y轴状态
    nRet = GTN_ClrSts(CORE,AXIS2,1);
    if (CMD_SUCCESS != nRet)
    {
        qDebug()<<"GTN_ClrSts Y:"<<nRet;
    }

    //清除Z轴状态
    nRet = GTN_ClrSts(CORE,AXIS3,1);
    if (CMD_SUCCESS != nRet)
    {
        qDebug()<<"GTN_ClrSts Z:"<<nRet;
    }
    return 0;
}

//电机回HOME操作
int GtsThread::GtsGoHome(int index)
{
    int nRet = CMD_SUCCESS;
    qint64 Tsec;
    qint64 timeout;

    if(!m_gtsstatus)
    {
        return 0;
    }
    THomePrm    HomePrm;
    THomeStatus HomeSts;

    nRet= GTN_AxisOn(CORE, index);
    qDebug()<<"GTN_AxisOn"<<nRet;
    nRet= GTN_AlarmOff(CORE, index);
    nRet= GTN_LmtsOnEx(CORE, index,-1,0);
    nRet= GTN_SetSense (CORE, MC_LIMIT_POSITIVE, index, 1); //限位为低电平触发----修改成了高电平触发，如果在配置文件中修改了反转，这里就是高电平触发
    nRet= GTN_SetSense (CORE, MC_LIMIT_NEGATIVE, index, 1); //限位为低电平触发----同上
    nRet= GTN_SetSense(CORE, MC_ENCODER,index,0); //编码器不取反
    nRet= GTN_ClrSts(CORE, index);
    nRet= GTN_ZeroPos(CORE, index);

    nRet = GTN_PrfTrap(CORE, index);
    qDebug()<<"GTN_PrfTrap"<<nRet;

    nRet = GTN_GetHomePrm(CORE,index,&HomePrm);
    if (CMD_SUCCESS != nRet)
    {
        qDebug()<<"GTN_GetHomePrm :"<<nRet;
    }
    HomePrm.mode                =   13;
    HomePrm.moveDir             =   0;   //2022-0808 何晓东改1->0：根据硬件结构修改搜寻home点的方向
    HomePrm.indexDir            =   1;   //2022-0808 何晓东改0->1：根据硬件结构修改电平触发方式
    HomePrm.edge                =   0;   //2022-0817 何晓东改1->0：根据硬件结构修改电平边缘触发方式
    HomePrm.velHigh             =   100;
    HomePrm.velLow              =   10;
    HomePrm.acc                 =   0.1;
    HomePrm.dec                 =   0.1;
    HomePrm.homeOffset          =   0;  //2022-0808 何晓东改：修改回home后的偏移值
    HomePrm.searchHomeDistance  =   0;
    HomePrm.searchIndexDistance =   0; //2022-0817 何晓东改1->0：不限制index搜索距离
    HomePrm.escapeStep          =   1000;
    nRet = GTN_GoHome(CORE,index,&HomePrm);
    if (CMD_SUCCESS != nRet)
    {
        qDebug()<<"GTN_GoHome 0:"<<nRet;
    }
    else
    {
        //timeout = QDateTime::currentDateTime().toTime_t()+5;
        do
        {
            double prfPos, prfVel;
            nRet = GTN_GetPrfPos(CORE,index, &prfPos);
            nRet = GTN_GetPrfVel(CORE,index, &prfVel);
            qDebug()<<"GTN_GetPrfVel"<<nRet<<prfVel<<"Pos"<<prfPos;
            nRet = GTN_GetHomeStatus(CORE,index,&HomeSts);
            qDebug()<<"GTN_GetHomeStatus:"<<HomeSts.stage<<HomeSts.targetPos<<HomeSts.error<<HomeSts.run;
            if (CMD_SUCCESS != nRet)
            {
                qDebug()<<"GTN_GetHomeStatus 0:"<<nRet;
                break;
            }
            if(m_Terminate)
            {
                nRet=GTN_AxisOff(CORE, index);
                m_Terminate = false;
                return -1;
            }
//            Tsec = QDateTime::currentDateTime().toTime_t();
//            if(Tsec > timeout)
//            {
//                nRet=GTN_AxisOff(CORE, index);
//                return -2;
//            }

        }
        while(HomeSts.run);
    }
    nRet=GTN_AxisOff(CORE, index);
    return 0;

}


//电机到位操作
int GtsThread::GtsGoPosition(short index,long position)
{
    int nRet = CMD_SUCCESS;
    TTrapPrm trap;
    long sts;
    double prfPos;
    if(!m_gtsstatus)
    {
        return 0;
    }
    nRet=GTN_ClrSts(CORE,index, 1);
    nRet=GTN_AxisOn(CORE, index);

    nRet=GTN_ZeroPos(CORE,index);

    nRet = GTN_SetPrfPos(CORE,index, 0);

    nRet = GTN_PrfTrap(CORE,index);


    nRet = GTN_GetTrapPrm(CORE,index, &trap);

    trap.acc = 0.25;
    trap.dec = 0.125;
    trap.smoothTime = 25;

    // 设置点位运动参数
    nRet = GTN_SetTrapPrm(CORE,index, &trap);

    nRet = GTN_SetPos(CORE,index, position);
    // 设置AXIS轴的目标速度
    nRet = GTN_SetVel(CORE,index, 50);
    // 启动AXIS轴的运动
    nRet = GTN_Update(CORE,1<<(index-1));
    do
    {
        // 读取AXIS轴的状态
        nRet = GTN_GetSts(CORE,index, &sts);
        // 读取AXIS轴的规划位置
        nRet = GTN_GetPrfPos(CORE,index, &prfPos);
        printf("sts=0x%-10lxprfPos=%-10.1lf\r", sts, prfPos);
        if(m_Terminate)
        {
            nRet=GTN_AxisOff(CORE, index);
            m_Terminate = false;
            return -1;
        }
    }while(sts&0x400); // 等待AXIS轴规划停止
    nRet=GTN_AxisOff(CORE, index);
    return 0;
}

GtsThread::GtsThread(QObject *parent)
{
    m_gtsstatus = false;
    m_Terminate = false;
    axiparam1.active = false;
    axiparam2.active = false;
    axiparam3.active = false;

    memset(&crdactive1,0,sizeof(crdactive1));
    crdactive1.active= false;
    mytimer = new QTimer();
    mytimer->setInterval(200);
    connect(mytimer,SIGNAL(timeout()),this,SLOT(onTimerOut()));
    mytimer->start();
}


void GtsThread::TermAction()
{
    m_Terminate = true;
    return;
}

int GtsThread::CrdPrmSet(int dimension,double synVelMax,double synAccMax,int evenTime,int profile0,int profile1,int setOriginFlag,long originPos0,long originPos1)
{
    int nRet = GTS_OK;
    TCrdPrm crdPrm;
    memset(&crdPrm, 0, sizeof(TCrdPrm));
    crdPrm.dimension    =   dimension;//坐标系为几维坐标系
    qDebug()<<"dimension:"<<crdPrm.dimension;
    crdPrm.synVelMax    =   synVelMax;//最大合成速度
    qDebug()<<"synVelMax:"<<crdPrm.synVelMax;
    crdPrm.synAccMax    =   synAccMax;//最大加速度
    qDebug()<<"synAccMax:"<<crdPrm.synAccMax;
    crdPrm.evenTime     =   evenTime; //最小匀速时间
    qDebug()<<"evenTime:"<<crdPrm.evenTime;
    crdPrm.profile[0]   =   profile0; //规划器1对应到轴
    qDebug()<<"profile[0]:"<<crdPrm.profile[0];
    crdPrm.profile[1]   =   profile1;  //规划器2对应到轴
    qDebug()<<"profile[1]:"<<crdPrm.profile[1];
    crdPrm.setOriginFlag=   setOriginFlag;//表示需要指定坐标系的原点坐标的规划位置
    qDebug()<<"setOriginFlag:"<<crdPrm.setOriginFlag;
    crdPrm.originPos[0] =   originPos0; //坐标系的原点坐标的规划位置x
    qDebug()<<"originPos[0]:"<<crdPrm.originPos[0];
    crdPrm.originPos[1] =   originPos1;  //坐标系的原点坐标的规划位置y
    qDebug()<<"originPos[1]:"<<crdPrm.originPos[1];

    nRet = GTN_SetCrdPrm(CORE,CRDINDEX, &crdPrm);
    qDebug()<<"GTN_SetCrdPrm:"<<nRet;
    nRet = GTN_CrdClear(CORE,CRDINDEX, 0);
    return nRet;
}


int GtsThread::AddCrdPrmC(long x,long y,long centerx,long centery,long direct,double spc,double acc,double endspc)
{
    if(crdactive1.number >= 512)
    {
        return -1;
    }
    crdactive1.param[crdactive1.number].typid = TYPEROUND;
    crdactive1.param[crdactive1.number].x = x;
    crdactive1.param[crdactive1.number].y = y;
    crdactive1.param[crdactive1.number].centerx = centerx;
    crdactive1.param[crdactive1.number].centery = centery;
    crdactive1.param[crdactive1.number].direct = direct;
    crdactive1.param[crdactive1.number].spc = spc;
    crdactive1.param[crdactive1.number].acc = acc;
    crdactive1.param[crdactive1.number].endspc = endspc;
    crdactive1.number++;
    return 0;
}

int GtsThread::AddCrdPrmR(long x,long y,long radius,long direct, double spc,double acc,double endspc)
{
    if(crdactive1.number >= 512)
    {
        return -1;
    }
    crdactive1.param[crdactive1.number].typid = TYPECRIL;
    crdactive1.param[crdactive1.number].x = x;
    crdactive1.param[crdactive1.number].y = y;
    crdactive1.param[crdactive1.number].radius = radius;
    crdactive1.param[crdactive1.number].direct = direct;
    crdactive1.param[crdactive1.number].spc = spc;
    crdactive1.param[crdactive1.number].acc = acc;
    crdactive1.param[crdactive1.number].endspc = endspc;
    crdactive1.number++;
    return 0;
}

int GtsThread::AddCrdPrmLine(long x,long y,double spc,double acc,double endspc)
{

    if(crdactive1.number >= 512)
    {
        return -1;
    }
    crdactive1.param[crdactive1.number].typid = TYPELINE;
    crdactive1.param[crdactive1.number].x = x;
    crdactive1.param[crdactive1.number].y = y;
    crdactive1.param[crdactive1.number].spc = spc;
    crdactive1.param[crdactive1.number].acc = acc;
    crdactive1.param[crdactive1.number].endspc = endspc;
    crdactive1.number++;
    return 0;
}

void GtsThread::onTimerOut()
{
    int nRet = GTS_OK;
    long sts;
    double prfPos, prfVel;
    if(axiparam1.active)
    {
        // 读取AXIS轴的状态
        nRet = GTN_GetSts(CORE,AXIS1, &sts);
        // 读取AXIS轴的规划位置
        nRet = GTN_GetPrfPos(CORE,AXIS1, &prfPos);
        // 读取AXIS轴的规划速度
        nRet = GTN_GetPrfVel(CORE,AXIS1, &prfVel);
        qDebug()<<"sts="<<sts<<":prfPos="<<prfPos<<":prfVel="<<prfVel;
        emit SendStatus(GTSJOGAX1CONF,0,prfVel,prfPos);
        if(axiparam1.nextspc!=axiparam1.spc)
        {
            nRet = GTN_SetVel(CORE,AXIS1, axiparam1.nextspc);
            // AXIS轴新的目标速度生效
            nRet = GTN_Update (CORE,1<<(AXIS1-1));
            axiparam1.spc = axiparam1.nextspc;
        }

    }
    if(axiparam2.active)
    {
        // 读取AXIS轴的状态
        nRet = GTN_GetSts(CORE,AXIS2, &sts);
        // 读取AXIS轴的规划位置
        nRet = GTN_GetPrfPos(CORE,AXIS2, &prfPos);
        // 读取AXIS轴的规划速度
        nRet = GTN_GetPrfVel(CORE,AXIS2, &prfVel);
        qDebug()<<"2 sts="<<sts<<":prfPos="<<prfPos<<":prfVel="<<prfVel;
        emit SendStatus(GTSJOGAX2CONF,0,prfVel,prfPos);
        if(axiparam2.nextspc!=axiparam2.spc)
        {
            nRet = GTN_SetVel(CORE,AXIS2, axiparam2.nextspc);
            // AXIS轴新的目标速度生效
            nRet = GTN_Update (CORE,1<<(AXIS2-1));
            axiparam2.spc = axiparam3.nextspc;
        }

    }
    if(axiparam3.active)
    {
        // 读取AXIS轴的状态
        nRet = GTN_GetSts(CORE,AXIS3, &sts);
        // 读取AXIS轴的规划位置
        nRet = GTN_GetPrfPos(CORE,AXIS3, &prfPos);
        // 读取AXIS轴的规划速度
        nRet = GTN_GetPrfVel(CORE,AXIS3, &prfVel);
        qDebug()<<"2 sts="<<sts<<":prfPos="<<prfPos<<":prfVel="<<prfVel;
        emit SendStatus(GTSJOGAX3CONF,0,prfVel,prfPos);
        if(axiparam3.nextspc!=axiparam3.spc)
        {
            nRet = GTN_SetVel(CORE,AXIS3, axiparam3.nextspc);
            // AXIS轴新的目标速度生效
            nRet = GTN_Update (CORE,1<<(AXIS3-1));
            axiparam3.spc = axiparam3.nextspc;
        }
    }

    if(crdactive1.active)
    {
        short run;
        long segment;
        double crdPos[2];
        nRet = GTN_CrdStatus(CORE,CRDINDEX,&run,&segment,0);
        qDebug()<<"segment="<<segment<<"run="<<run<<"ret="<<nRet;
        nRet = GTN_GetCrdPos(CORE,CRDINDEX, crdPos);
        qDebug()<<"x:"<<crdPos[0]<<"y:"<<crdPos[1];
        if(run)
        {
            emit SendStatus(GTSCRDPRM,0,crdPos[0],crdPos[1]);
        }
        else
        {
            emit SendStatus(GTSCRDPRM,1,crdPos[0],crdPos[1]);
            memset(&crdactive1,0,sizeof(crdactive1));
            crdactive1.active = false;
        }

    }
    return;
}


void GtsThread::GTSDoProc(int index,int value0 ,double value1,double value2)
{
    int  nRet = -1;
    long sts;
    TJogPrm jog;
    int numb = 0;
    long space;
    switch (index) {
    case GTSINIT:
        nRet = GtsInit();
        emit SendStatus(GTSINIT,nRet);
        break;
    case GTSCLEAR:
        nRet = GtsClearStatus();
        emit SendStatus(GTSCLEAR,nRet);
        break;
    case GTSGOHOME:
        nRet = GtsGoHome(value0);
        emit SendStatus(GTSGOHOME,nRet);
        break;
    case GTSGOZERO:
        nRet = GtsGoPosition(value0,value1);
        emit SendStatus(GTSGOZERO,nRet);
        break;
    case GTSGOUP:
        nRet = GtsGoPosition(value0,value1);
        emit SendStatus(GTSGOUP,nRet);
        break;
    case GTSGODOWN:
        nRet = GtsGoPosition(value0,value1);
        emit SendStatus(GTSGODOWN,nRet);
        break;
    case GTSJOGAX1EABLE:
        if(!m_gtsstatus)
        {
            break;
        }
        if(value0 == 1)
        {
            nRet = GTN_ClrSts(CORE,AXIS1);
            nRet=GTN_AxisOn(CORE, AXIS1);
            nRet=GTN_ZeroPos(CORE,AXIS1);
            axiparam1.nextspc   =   0;
            axiparam1.spc       =   0;
            emit SendStatus(GTSJOGAX1EABLE,nRet,1);
        }
        else
        {
            nRet=GTN_AxisOff(CORE, AXIS1);
            axiparam1.active = false;
            axiparam1.nextspc   =   0;
            axiparam1.spc       =   0;
            emit SendStatus(GTSJOGAX1EABLE,nRet,0);
        }

        break;
    case GTSJOGAX2EABLE:
        if(!m_gtsstatus)
        {
            break;
        }
        if(value0 == 1)
        {
            nRet = GTN_ClrSts(CORE,AXIS2);
            nRet = GTN_GetSts(CORE,AXIS3, &sts);

            nRet=GTN_AxisOn(CORE, AXIS2);
            nRet = GTN_GetSts(CORE,AXIS2, &sts);
            nRet=GTN_ZeroPos(CORE,AXIS2);
            nRet = GTN_GetSts(CORE,AXIS2, &sts);
            axiparam2.nextspc   =   0;
            axiparam2.spc       =   0;
            emit SendStatus(GTSJOGAX2EABLE,nRet,1);
        }
        else
        {
            nRet=GTN_AxisOff(CORE, AXIS2);
            axiparam2.active = false;
            axiparam2.nextspc   =   0;
            axiparam2.spc       =   0;
            emit SendStatus(GTSJOGAX2EABLE,nRet,0);
        }
        break;
    case GTSJOGAX3EABLE:
        if(!m_gtsstatus)
        {
            break;
        }
        if(value0 == 1)
        {
            nRet = GTN_ClrSts(CORE,AXIS3);
            nRet = GTN_GetSts(CORE,AXIS3, &sts);
            nRet=GTN_AxisOn(CORE, AXIS3);
            nRet=GTN_ZeroPos(CORE,AXIS3);
            axiparam3.nextspc   =   0;
            axiparam3.spc       =   0;
            emit SendStatus(GTSJOGAX3EABLE,nRet,1);
        }
        else
        {
            nRet=GTN_AxisOff(CORE, AXIS3);
            axiparam3.active = false;
            axiparam3.nextspc   =   0;
            axiparam3.spc       =   0;
            emit SendStatus(GTSJOGAX3EABLE,nRet,0);
        }
        break;
     case GTSJOGAX1CONF:
        if(!m_gtsstatus)
        {
            break;
        }
        if(value0 == 1)
        {
            if(!axiparam1.active)
            {
                nRet = GTN_PrfJog(CORE,AXIS1);
                // 读取 Jog 运动参数(需要读取全部运动参数到上位机变量)
                nRet = GTN_GetJogPrm(CORE,AXIS1, &jog);
                jog.acc = 0.0625;
                jog.dec = 0.0625;
                // 设置 Jog 运动参数
                nRet = GTN_SetJogPrm(CORE,AXIS1, &jog);
            }
            axiparam1.active    = true;
            axiparam1.nextspc   = value1;
            axiparam1.positon   = value2;
        }
        else
        {
            axiparam1.active    = false;
            axiparam1.spc       = 0;
            axiparam1.nextspc   = 0;
            nRet = GTN_Stop(CORE,AXIS1,1);
        }
        break;
     case GTSJOGAX2CONF:
        if(!m_gtsstatus)
        {
            break;
        }
        if(value0 == 1)
        {
            if(!axiparam2.active)
            {
                nRet = GTN_PrfJog(CORE,AXIS2);
                nRet = GTN_GetSts(CORE,AXIS2, &sts);
                // 读取 Jog 运动参数(需要读取全部运动参数到上位机变量)
                nRet = GTN_GetJogPrm(CORE,AXIS2, &jog);
                jog.acc = 0.0625;
                jog.dec = 0.0625;
                // 设置 Jog 运动参数
                nRet = GTN_SetJogPrm(CORE,AXIS2, &jog);
                nRet = GTN_GetSts(CORE,AXIS2, &sts);
            }
            axiparam2.active    = true;
            axiparam2.nextspc   = value1;
            axiparam2.positon   = value2;
        }
        else
        {
            axiparam2.active    = false;
            axiparam2.spc       = 0;
            axiparam2.nextspc   = 0;
            nRet = GTN_Stop(CORE,AXIS2,1);
        }
        break;
     case GTSJOGAX3CONF:
        if(!m_gtsstatus)
        {
            break;
        }
        if(value0 == 1)
        {
            if(!axiparam3.active)
            {
                nRet = GTN_PrfJog(CORE,AXIS3);
                // 读取 Jog 运动参数(需要读取全部运动参数到上位机变量)
                nRet = GTN_GetJogPrm(CORE,AXIS3, &jog);
                jog.acc = 0.0625;
                jog.dec = 0.0625;
                // 设置 Jog 运动参数
                nRet = GTN_SetJogPrm(CORE,AXIS3, &jog);
            }
            axiparam3.active    = true;
            axiparam3.nextspc   = value1;
            axiparam3.positon   = value2;
        }
        else
        {
            axiparam3.active    = false;
            axiparam3.spc       = 0;
            axiparam3.nextspc   = 0;
            nRet = GTN_Stop(CORE,AXIS3,1);
        }
        break;
      case GTSCRDPRM:
        qDebug()<<"goto GTSCRDLINE"<<crdactive1.number;
        //即将把数据存入坐标系1的FIFO0中，所以要首先清除此缓存区中的数据
        //nRet=GTN_AxisOn(CORE, AXIS1);
        //nRet=GTN_AxisOn(CORE, AXIS2);
        nRet = GTN_CrdClear(CORE,CRDINDEX, 0);
        if(crdactive1.number<1)
        {
           break;
        }
        for(numb = 0; numb<crdactive1.number; numb++)
        {
            switch(crdactive1.param[numb].typid)
            {
                case TYPELINE:
                nRet = GTN_LnXY(CORE,CRDINDEX,crdactive1.param[numb].x,crdactive1.param[numb].y,
                     crdactive1.param[numb].spc,crdactive1.param[numb].acc,crdactive1.param[numb].endspc,0);
                qDebug()<<"GTN_LnXY:"<<numb<<" ret = "<<nRet;
                break;
                case TYPEROUND:
                nRet = GTN_ArcXYC(CORE,CRDINDEX,crdactive1.param[numb].x,crdactive1.param[numb].y,crdactive1.param[numb].centerx,
                     crdactive1.param[numb].centery,crdactive1.param[numb].direct,crdactive1.param[numb].spc,crdactive1.param[numb].acc,crdactive1.param[numb].endspc,0);
                break;
                case TYPECRIL:
                nRet = GTN_ArcXYR(CORE,CRDINDEX,crdactive1.param[numb].x,crdactive1.param[numb].y,crdactive1.param[numb].radius,
                     crdactive1.param[numb].direct,crdactive1.param[numb].spc,crdactive1.param[numb].acc,crdactive1.param[numb].endspc,0);
                break;
                default:
                break;
            }

            //nRet = GTN_BufIO(CORE,CRDINDEX,MC_GPO,0xffff,0xaa,0);
            //qDebug()<<"GTN_BufIO:"<<numb<<" ret = "<<nRet;
        }
        nRet = GTN_CrdSpace(CORE,CRDINDEX, &space, 0);
        qDebug()<<"GTN_CrdSpace:"<<space<<" ret = "<<nRet;
        nRet = GTN_CrdStart(CORE,CRDINDEX, 0);
        qDebug()<<"GTN_CrdStart:ret = "<<nRet;
        crdactive1.active    = true;
        break;
    case GTSCRDSTOP:
        crdactive1.active    = false;
        GTN_Stop(CORE,AXIS1,1);
        GTN_Stop(CORE,AXIS2,1);
        nRet=GTN_AxisOff(CORE, AXIS1);
        nRet=GTN_AxisOff(CORE, AXIS2);
        break;
    default:
        break;
    }
}


