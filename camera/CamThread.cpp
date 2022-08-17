#include "camthread.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <QDateTime>
#include "include/MvCameraControl.h"
#include <QDebug>

#define WIDTH 	1920
#define HIGH 	1080
#define RELOARD_NUMBER  30


void* camhandle = NULL;

extern uchar g_BitmapBuffer[1920*1080*4];

bool PrintDeviceInfo(MV_CC_DEVICE_INFO* pstMVDevInfo)
{
    if (NULL == pstMVDevInfo)
    {
        printf("The Pointer of pstMVDevInfo is NULL!\n");
        return false;
    }
    if (pstMVDevInfo->nTLayerType == MV_GIGE_DEVICE)
    {
        int nIp1 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
        int nIp2 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
        int nIp3 = ((pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
        int nIp4 = (pstMVDevInfo->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

        // ch:打印当前相机ip和用户自定义名字 | en:print current ip and user defined name
        printf("Device Model Name: %s\n", pstMVDevInfo->SpecialInfo.stGigEInfo.chModelName);
        printf("CurrentIp: %d.%d.%d.%d\n" , nIp1, nIp2, nIp3, nIp4);
        printf("UserDefinedName: %s\n\n" , pstMVDevInfo->SpecialInfo.stGigEInfo.chUserDefinedName);
    }
    else if (pstMVDevInfo->nTLayerType == MV_USB_DEVICE)
    {
        printf("Device Model Name: %s\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chModelName);
        printf("UserDefinedName: %s\n\n", pstMVDevInfo->SpecialInfo.stUsb3VInfo.chUserDefinedName);
    }
    else
    {
        printf("Not support.\n");
    }

    return true;
}

//设置摄像头曝光
int CamThread::SetExposureTime(float ExposureTime)
{
    int nRet = MV_OK;
    //设置摄像头曝光时间
    nRet = MV_CC_SetFloatValue(camhandle, "ExposureTime", ExposureTime);
    if(nRet == MV_OK)
    {
        m_ExposureTime = ExposureTime;
    }
    else
    {
        printf("Set Exp Error %d\n",nRet);
    }
    return nRet;
}

//初始化摄像头
int CamThread::CamInit()
{
    int nRet = MV_OK;
    unsigned int nIndex = 0;
    do
    {
        qDebug()<<"CamInit In";
        MV_CC_DEVICE_INFO_LIST stDeviceList;
        memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
        // 枚举设备
        nRet = MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList);
        if (MV_OK != nRet)
        {
            qDebug()<<"MV_CC_EnumDevices fail!"<<nRet;
            break;
        }
        if (stDeviceList.nDeviceNum > 0)
        {
            for (int i = 0; i < stDeviceList.nDeviceNum; i++)
            {
                qDebug()<<"[device]:"<<i;
                MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[i];
                if (NULL == pDeviceInfo)
                {
                    break;
                }
                //PrintDeviceInfo(pDeviceInfo);
            }
        }
        else
        {
            qDebug()<<"Find No Devices!";
            break;
        }
        qDebug()<<"MV_CC_EnumDevices";

        if (nIndex >= stDeviceList.nDeviceNum)
        {
            qDebug()<<"Intput error!";
            break;
        }

        // 选择设备并创建句柄
        nRet = MV_CC_CreateHandle(&camhandle, stDeviceList.pDeviceInfo[nIndex]);
        if (MV_OK != nRet)
        {
            qDebug()<<"MV_CC_CreateHandle fail! nRet:"<<nRet;
            break;
        }
        qDebug()<<"MV_CC_CreateHandle";
        // 打开设备
        nRet = MV_CC_OpenDevice(camhandle);
        if (MV_OK != nRet)
        {
            qDebug()<<"MV_CC_OpenDevice fail! nRet:\n"<<nRet;
            break;
        }
        qDebug()<<"MV_CC_OpenDevice";
        // ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
        if (stDeviceList.pDeviceInfo[nIndex]->nTLayerType == MV_GIGE_DEVICE)
        {
            int nPacketSize = MV_CC_GetOptimalPacketSize(camhandle);
            if (nPacketSize > 0)
            {
                nRet = MV_CC_SetIntValue(camhandle,"GevSCPSPacketSize",nPacketSize);
                if(nRet != MV_OK)
                {
                    qDebug()<<"Warning: Set Packet Size fail nRet="<<nRet;
                }
            }
            else
            {
                qDebug()<<"Warning: Get Packet Size fail nRet="<<nPacketSize;
            }
        }

         //设置触发模式为off
         //set trigger mode as on
        nRet = MV_CC_SetEnumValue(camhandle, "TriggerMode", 0);
        if (MV_OK != nRet)
        {
            printf("MV_CC_SetTriggerMode fail! nRet [%x]\n", nRet);
            break;
        }

        //设置曝光时间为2ms

        //SetExposureTime(2000);

        //设置摄像头增益为2倍
//        nRet = MV_CC_SetFloatValue(camhandle, "Gain", 2);
//        if (MV_OK != nRet)
//        {
//            printf("MV_CC_SetFloatValue fail! nRet [%x]\n", nRet);
//            break;
//        }
    } while (0);
    if(MV_OK != nRet)
    {
        qDebug()<< "open camera fail";
        return -1;
    }
    //设置缓冲区大小
    //system("echo 500 > /sys/module/usbcore/parameters/usbfs_memory_mb");
    qDebug()<<"CamInit Out";
    return 0;
}
//开启摄像头数据流
int CamThread::CamStart()
{
    int nRet = MV_OK;
    if(camhandle == NULL)
    {
        return -1;
    }
    //开始取流
    nRet = MV_CC_StartGrabbing(camhandle);
    if (MV_OK != nRet)
    {
        printf("MV_CC_StartGrabbing fail! nRet [%x]\n", nRet);
        return -1;
    }
    return 0;
}

//关闭摄像头数据流
int CamThread::CamStop()
{
    int nRet = MV_OK;
    if(camhandle == NULL)
    {
        return -1;
    }
    qDebug()<<"CamStop";
    // 停止取流
    nRet = MV_CC_StopGrabbing(camhandle);
    if (MV_OK != nRet)
    {
        printf("MV_CC_StopGrabbing fail! nRet [%x]\n", nRet);
        return -1;
    }
    return 0;

}

//关闭摄像头硬件
int CamThread::CamExit()
{
    int nRet = MV_OK;
    if(camhandle == NULL)
    {
        return -1;
    }
    do{
        qDebug()<<"CamExit";
        //关闭设备
        nRet = MV_CC_CloseDevice(camhandle);
        if (MV_OK != nRet)
        {
            printf("MV_CC_CloseDevice fail! nRet [%x]\n", nRet);
            break;
        }
        // 销毁句柄
        nRet = MV_CC_DestroyHandle(camhandle);
        if (MV_OK != nRet)
        {
            printf("MV_CC_DestroyHandle fail! nRet [%x]\n", nRet);
            break;
        }
    } while (0);
    camhandle = NULL;
    return 0;
}

CamThread::CamThread(QObject *parent)
    :QThread(parent)
{
    CamInit();
}

//保存位图图像
int SaveImageFull(const char* filename,unsigned char* bmp,int w ,int h)
{
   int i = 0;
   char color = 0;
   char end[2] = {0,0};
   char patte[1024] = {0};
   int pos = 0;
   FILE *outfile;
   char heard[54] = {0x42,0x4d,0x30,0x0C,0x01,0,0,0,0,0,0x36,04,0,0,0x28,0,\
                 0,0,0xF5,0,0,0,0x46,0,0,0,0x01,0,8,0,0,0,\
                 0,0,0xF8,0x0b,0x01,0,0x12,0x0b,0,0,0x12,0x0b,0,0,0,0,\
                 0,0,0,0,0,0};
   int size = w*h;
   int allsize = size +1080;

   heard[2] = allsize&0xFF;
   heard[3] = (allsize>>8)&0xFF;
   heard[4] = (allsize>>16)&0xFF;
   heard[5] = (allsize>>24)&0xFF;

   heard[18] = w&0xFF;
   heard[19] = (w>>8)&0xFF;
   heard[20] = (w>>16)&0xFF;
   heard[21] = (w>>24)&0xFF;

   heard[22] = h&0xFF;
   heard[23] = (h>>8)&0xFF;
   heard[24] = (h>>16)&0xFF;
   heard[25] = (h>>24)&0xFF;

   allsize -=1078;
   heard[34] = allsize&0xFF;
   heard[35] = (allsize>>8)&0xFF;
   heard[36] = (allsize>>16)&0xFF;
   heard[37] = (allsize>>24)&0xFF;

   for(i=0;i<1024;i+=4)
   {
       patte[pos++] = color;
       patte[pos++] = color;
       patte[pos++] = color;
       patte[pos++] = 0;
       color++;
   }
   outfile = fopen( filename, "w" );
   if(outfile!=NULL){
       fwrite(heard,54,1,outfile);
       fwrite(patte,1024,1,outfile);
       fwrite(bmp,size,1,outfile);
       fwrite(end,2,1,outfile);
       fclose(outfile);
   }
   return 0;
}
void CamThread::StopThread()
{
    m_bStop = true;
    return;
}

void CamThread::ResumeThread()
{
    m_bStop = false;
    return;
}



void CamThread::run()
{
    int nRet = MV_OK;
    m_bRun = true;
    m_bStop = false;
    int frameindex = 0;
    MV_FRAME_OUT stOutFrame = {0};

    CamStart();

    while(m_bRun)
    {
        if(m_bStop)
        {
            QThread::msleep(50);
            continue;
        }
        nRet = MV_CC_GetImageBuffer(camhandle, &stOutFrame, 200);
        if (nRet == MV_OK)
        {
            if(frameindex > 65535)
            {
                frameindex = 0;
            }
            if(frameindex%3 == 1)
            {
                //拷贝摄像头图像数据 Gray模式
                memcpy(g_BitmapBuffer,stOutFrame.pBufAddr,stOutFrame.stFrameInfo.nFrameLen);
                qDebug()<<"Get Image Success";
                if(m_bRun)
                {
                    //发送到主线程显示
                    emit showimage(0);
                }
            }
            frameindex++;
            nRet = MV_CC_FreeImageBuffer(camhandle, &stOutFrame);
        }
        else
        {
            //如果摄像头发生异常需要重启摄像头
            qDebug()<<"Reset Camera";
            CamInit();
            CamStart();
        }
    }
    qDebug()<<"exit camera thread";
    CamStop();
    CamExit();
    return;
}

void CamThread::DestroyThread()
{
    m_bRun = false;
}
