#ifndef _IVM_EXPORT_H__
#define _IVM_EXPORT_H__

/* note: Interface export definition of the namespace VisionMasterSDK */

namespace VisionMasterSDK
{
    #ifdef WIN32
        #if defined(IMVS6000PLATFORMSDK_EXPORTS)
            #define IMVS_6000_PLATFORMSDK_API __declspec(dllexport)
        #else
            #define IMVS_6000_PLATFORMSDK_API __declspec(dllimport)
        #endif
    #else
        #ifndef __stdcall
            #define __stdcall
        #endif
        #ifndef IMVS_6000_PLATFORMSDK_API
            #define IMVS_6000_PLATFORMSDK_API
        #endif
    #endif

    #ifndef IN
        #define IN
    #endif

    #ifndef OUT
        #define OUT
    #endif

    #ifndef INOUT
        #define INOUT
    #endif
}

//////////////////////////////////// �������� //////////////////////////////////////
const static unsigned int MAX_PROCESS_NAME_LENGTH = 64;         // CH: ����������󳤶� | EN: Maximum length of process name
const static unsigned int MAX_PROCESS_NUM         = 1000;       // CH: ������̸��� | EN: Maximum number of processes
const static unsigned int MAX_MODULE_DISPLAY_NAME_LENGTH = 256; // CH: ģ����ʾ������󳤶� | EN: Maximum length of module display name
const static unsigned int MAX_MODULE_NAME_LENGTH  = 64;         // CH: ģ��������󳤶� | EN: Maximum length of module name
const static unsigned int MAX_MODULE_NUM          = 1024;       // CH: ���ģ����� | EN: Maximum number of modules
const static unsigned int MAX_CORE_NUM            = 64;         // ���CPU���ĸ���
const static unsigned int MAX_OBJECT_IO_NAME_LENGTH = 128;      // CH: IO������󳤶� | EN: Maximum length of IO name
const static unsigned int MAX_OBJECT_IO_NUM = 1024;             // CH: IO������ | EN: Maximum number of IO
const static unsigned int MAX_OBJECT_NUM            = 1024;     // CH: ����������� | EN: Maximum number of Objects
const static unsigned int MAX_CAMERA_SN_LEN      = 64;          // CH: ���������кų��� | EN: Maximum length of camera sn
const static unsigned int MAX_CAMERA_NAME_LEN    = 64;          // CH: ���������Ƴ��� | EN: Maximum length of camera name
const static unsigned int MAX_CAMERA_NUM         = 256;         // CH: ���������� | EN: Maximum length of camera number

// CH: VM�������� | EN: Objects type in VM
enum VMObjectType
{
    VMObjectType_Unknown = 0,       // δ֪����
    VMObjectType_Procedure = 1,     // ���̶���
    VMObjectType_Module = 2         // ģ�����
};

// CH: ������Ϣ�б�ṹ | EN: Objects information list structure
typedef struct ObjectList__
{
    VMObjectType        enType;                         // CH: �������� | EN: Object type
    unsigned int        nNum;                           // CH: ������� | EN: The number of Objects in the list
    void*               pObjects[MAX_OBJECT_NUM];       // CH: ������Ϣ�б� | EN: Object information
    unsigned int        nReserved[4];                   // CH: �����ֶ� | EN: Reserved
} ObjectList;

// CH: ������Ϣ�ṹ | EN: Process information structure
typedef struct ProcessInfo__
{
    unsigned int nProcessID;                                    // CH: ����ID | EN: Process ID
    char         strProcessName[MAX_PROCESS_NAME_LENGTH];       // CH: �������� | EN: Process name
    unsigned int nReserved[4];                                  // CH: �����ֶ� | EN: Reserved
} ProcessInfo;

// CH: ������Ϣ�б�ṹ | EN: Process information list structure
typedef struct ProcessInfoList__
{
    unsigned int         nNum;                                  // CH: ���̸��� | EN: The number of processes in the list
    ProcessInfo          astProcessInfo[MAX_PROCESS_NUM];       // CH: ������Ϣ�б� | EN: Process information
    unsigned int         nReserved[4];                          // CH: �����ֶ� | EN: Reserved
} ProcessInfoList;

// CH: ���������Ϣ�ṹ | EN: Camera information structure
typedef struct CameraInfo__
{
    char strCameraName[MAX_CAMERA_NAME_LEN];           // CH: ������� | EN: Camera Name
    char strCameraSN[MAX_CAMERA_SN_LEN];               // CH: ���SN | EN: Camera SN
    unsigned int nReserved[4];                         // CH: �����ֶ� | EN: Reserved
} CameraInfo;

// CH: �����Ϣ�б�ṹ | EN: Camera information list structure
typedef struct CameraInfoList__
{
    unsigned int nNum;                                          // CH: ������� | EN: Camera Number
    CameraInfo astCameraInfo[MAX_CAMERA_NUM];                   // CH: �����Ϣ | EN: Camera Info
    unsigned int nReserved[4];                                  // CH: �����ֶ� | EN: Reserved
} CameraInfoList;

// CH: ����ģ����Ϣ�ṹ | EN: Module information structure
typedef struct ModuInfo__
{
    unsigned int    nModuleID;                                      // CH: ģ��ID | EN: Module ID
    unsigned int    nProcessID;                                     // CH: ����ID | EN: Process ID
    char            strDisplayName[MAX_MODULE_DISPLAY_NAME_LENGTH]; // CH: ������ʾ���� | EN: Displayed module name
    char            strModuleName[MAX_MODULE_NAME_LENGTH];          // CH: ģ������ | EN: Module name
    unsigned int    nReserved[128];                                 // CH: �����ֶ� | EN: Reserved
} ModuInfo;

// CH: ģ����Ϣ�б�ṹ | EN: Module information list structure
typedef struct ModuleInfoList__
{
    unsigned int           nNum;                                     // CH: ģ����� | EN: Number of modules in list
    ModuInfo               astModuleInfo[MAX_MODULE_NUM];            // CH: ģ����Ϣ�б� | EN: Information details of a module
    unsigned int           nReserved[4];                             // CH: �����ֶ� | EN: Reserved
} ModuleInfoList;

// CH: Groupģ����Ϣ�ṹ | EN: Group module information structure
typedef struct GroupModuInfo__
{
    unsigned int    nModuleID;                                      // CH: ģ��ID | EN: Module ID
    char            strDisplayName[MAX_MODULE_DISPLAY_NAME_LENGTH]; // CH: ������ʾ���� | EN: Displayed module name
    char            strModuleName[MAX_MODULE_NAME_LENGTH];          // CH: ģ������ | EN: Module name
    unsigned int    nReserved[128];                                 // CH: �����ֶ� | EN: Reserved
} GroupModuInfo;

// CH: Groupģ����Ϣ�б�ṹ | EN: Group module information list structure
typedef struct GroupModuInfoList__
{
    unsigned int           nNum;                                     // CH: ģ����� | EN: Number of modules in list
    GroupModuInfo          astModuleInfo[MAX_MODULE_NUM];            // CH: ģ����Ϣ�б� | EN: Information details of a module
    unsigned int           nReserved[4];                             // CH: �����ֶ� | EN: Reserved
} GroupModuInfoList;

// �û��Զ����������в�����Ϣ�ṹ
typedef struct ProcedureRunPolicy__
{
    int          nThreadNum;       // ָ��������ִ���߳���Ŀ
    char         chCpuCore[MAX_CORE_NUM]; // ָ���������е�CPU���� CPU�����飬0-��Ч��1-��Ч��
                                          // chCpuCore[0]��ʾcpu0��chCpuCore[1]��ʾcpu1, chCpuCore[2]��ʾcpu2...
    unsigned int nReserved[4];     // �����ֶ�
}ProcedureRunPolicy;

// CH: ģ�鵼��������Ϣ�ṹ | EN: Module import data structure
typedef struct ModuleImportData__
{
    char *             pData;               // CH: �����ļ�����·�� | EN: The imported file's path
    unsigned int       nReserved[4];         // CH: �����ֶ� | EN: Reserved
}ModuleImportData;

// ����㷨ƽ̨��Ϣ
typedef struct OutputPlatformInfo__
{
    unsigned int  nInfoType;                                // �ص���Ϣ����
    unsigned int  nDataSize;                                // �ص����ݷ����ڴ�
    unsigned int  nDataLen;                                 // �ص�����ʵ�ʳ���
    void *        pData;                                    // �ص�����
    unsigned int  nReserved[4];                             // �����ֶ�
} OutputPlatformInfo;

// ������̬IO��Ϣ�ṹ
typedef struct DynamicIOInfoItem__
{
    unsigned int     nIOType;                    // ��̬IO���ͣ�1-���ͣ�2-�����ͣ�3-�ַ����ͣ�4-ͼ���ͣ�5-��������
    char chIOName[MAX_OBJECT_IO_NAME_LENGTH];   // ��̬IO����
}DynamicIOInfoItem;

// ��̬IO�б���Ϣ�ṹ
typedef struct DynamicIOInfoList__
{
    unsigned int      nIONum;                                 // ��̬IO����
    DynamicIOInfoItem astIOInfo[MAX_OBJECT_IO_NUM];           // ��̬IO����
    unsigned int      nReserved[4];                           // �����ֶ�
}DynamicIOInfoList;

#endif    ///< _IVM_EXPORT_H__
