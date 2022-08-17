/***************************************************************************************************
 * File��IVmSolution.h
 * Note��Interface for the solution tool.
 *
 * Version��4.2
 * Date��2020-11
 ***************************************************************************************************/
#ifndef _IVM_SOLUTION_H_
#define _IVM_SOLUTION_H_

#include "IVmExport.h"
#include "iMVS-6000PlatformSDKDefine.h"
#include "IVmProcedure.h"

namespace VisionMasterSDK
{
    namespace VmSolution
    {
        class IVmSolutionEvent
        {
        public:
            /**
            * @brief ���ȡͼ��Ϣ�ص�
            * @param pstCameraCollect [IN] ���ȡͼ��Ϣ
            * @par ע��
            */
            virtual void OnCameraCollectInfoCallBack(IN const IMVS_PF_CAMERA_COLLECT_INFO * const pstCameraCollect, IN void * const pUser) = 0;

            /**
            * @brief ͨ������״̬�ص�
            * @param pstCommuConnect [IN] ͨ������״̬
            * @par ע��
            */
            virtual void OnCommunicationConnectInfoCallBack(IN const IMVS_PF_COMMUNICATION_CONNECT_INFO * const pstCommuConnect, IN void * const pUser) = 0;
        };

        class IVmSolution
        {
        public:
            ///< Constructor and Destructor
            explicit IVmSolution() {}
            virtual ~IVmSolution() {}

        public:
            /**
             * @brief ִ��һ��
             * @param �����ַ���
             * @return �ޣ�����ʱ�׳��쳣
             * @par ע��
             * ȫ����ִ��һ��
             */
            virtual void Run(IN const char * const strCmd = NULL) = 0;

            /**
             * @brief ��������
             * @param ��
             * @return �ޣ�����ʱ�׳��쳣
             * @par ע��
             * ȫ������������
             */
            virtual void Runing(void) = 0;

            /**
             * @brief ֹͣ��������
             * @param �ȴ���ʱ ����λ���룩
             * @return �ޣ�����ʱ�׳��쳣
             * @par ע��
             * ȫ����ֹͣ��������
             */
            virtual void StopRun(IN const unsigned int nWaitTime = 3) = 0;

            /**
             * @brief ������������ʱ����
             * @param ʱ���� ����λ��ms��
             * @return �ޣ�����ʱ�׳��쳣
             * @par ע��
             * ����ȫ������������ʱ����
             */
            virtual void SetRunInterval(IN const unsigned int nMilliSecond) = 0;

            /**
             * @brief ���淽�����ļ�
             * @param ����·��
             * @param ��������
             * @return �ޣ�����ʱ�׳��쳣
             * @par ע��
             * ����,�Ƽ�(SaveAsSolution(char * strSolPath, char * strPassword))
             */
            virtual void ExportSolution(IN const char * const strSolPath, IN const char * const strPassword) = 0;

            /**
            * @brief ���淽�����ļ�,ʹ������·��������
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            */
            virtual void SaveSolution() = 0;

            /**
            * @brief ���淽�����ļ�
            * @param ����·��
            * @param ��������
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            */
            virtual void SaveAsSolution(IN const char * const strSolPath, IN const char * const strPassword) = 0;

            /**
             * @brief �����Ƿ�������
             * @param ��
             * @return �����뷵��true�������뷵��false
             * @par ע��
             */
            virtual bool HasPassword(void) = 0;

            /**
             * @brief ��ȡ��ǰ�����汾
             * @param ��
             * @return ��ǰ�����汾
             * @par ע��
             */
            virtual const char * GetSolutionVersion(void) = 0;

            /**
             * @brief ɾ��һ������
             * @param ������ʾ����
             * @return ��
             * @par ע��
             */
            virtual void DeleteOneProcedure(IN const char * const strProcedureName) = 0;

            

            /**
             * @brief ����һ������
             * @param ������ʾ����
             * @return ��
             * @par ע��
             */
            virtual void DisableProcedure(IN const char * const strProcedureName) = 0;

            /**
             * @brief ����һ������
             * @param ������ʾ����
             * @return ��
             * @par ע��
             */
            virtual void EnableProcedure(IN const char * const strProcedureName) = 0;

            /**
             * @brief �����Ƿ����
             * @param ������ʾ����
             * @return ���̽��÷���true��δ���÷���false
             * @par ע��
             */
            virtual bool IsProcedureDisable(IN const char * const strProcedureName) = 0;

            /**
             * @brief ��ȡ����������Ϣ�б�
             * @param ��
             * @return ����������Ϣ�б�
             * @par ע��
             */
            virtual ProcessInfoList * GetAllProcedureList(void) = 0;

            /**
            * @brief ��ȡ�������̶����б�
            * @param ��
            * @return �������̶����б�
            * @par ע��
            */
            virtual ObjectList GetAllProcedureObjects(void) = 0;

            /**
             * @brief ��ȡ����ģ����Ϣ�б�
             * @param ��
             * @return ����ģ����Ϣ�б�
             * @par ע��
             */
            virtual ModuleInfoList * GetAllModuleList(void) = 0;

            /**
             * @brief ��ȡ��ǰ����·��
             * @param ��
             * @return ��ǰ����·��
             * @par ע��
             */
            virtual const char * GetSolutionPath(void) = 0;
            
            /**
            * @brief ��ȡ��ǰ�������
            * @param ��
            * @return ��ǰ�������
            * @par ע��
            */
            virtual void * GetSolutionHandle(void) = 0;

            /**
            * @brief ��������ģ�����ص�
            ���ú�Ҫ����Ҫ��ģ��ص�ʹ�ܵ����򿪣�CxxxTool.EnableResultCallback()���������޷��ٻص��������õ�ģ������
            * @param ��
            * @return ��
            * @par ע��
            */
            virtual void DisableModulesCallback(void) = 0;

            /**
            * @brief ��������ģ�����ص����������غ�Ĭ����������ģ��ص�
            ���ú��ڻص����������յ�ģ����������������IMVS_ENUM_CTRLC_OUTPUT_PLATFORM_INFO_MODULE_RESULT == pstOutputInfo->nInfoType
            ģ������IMVS_PF_MODULE_RESULT_INFO_LIST* pstModuResultList = (IMVS_PF_MODULE_RESULT_INFO_LIST *)pstOutputInfo->pData;
            * @param ��
            * @return ��
            * @par ע��
            */
            virtual void EnableModulesCallback(void) = 0;

            /**
             * @brief ע��ص�����
             * @param cbOutputInfo [IN] �ص�����ָ��
             * @param pUser        [IN] �û�ָ��
             * @par ע��
             */
            virtual void RegisterCallBack(IN int(__stdcall * cbOutputInfo)(OUT OutputPlatformInfo * const pstOutputInfo, IN void * const pUser), IN void * const pUser) = 0;

            /**
             * @brief ��ע��ص�����
             * @par ע��
             */
            virtual void UnRegisterCallBack() = 0;

            /**
            * @brief ע�᷽���ص��¼�����
            * @param pSolutionEvent [IN] �¼�����ָ��
            * @par ע��
            */
            virtual void RegisterCallBackEvent(IN IVmSolutionEvent* pSolutionEvent, IN void * const pUser) = 0;

            /**
            * @brief ��ע�᷽���ص��¼�����
            * @par ע��
            */
            virtual void UnRegisterCallBackEvent() = 0;

            /**
            * @brief ����ģ������������
            * @param ����ʹ��
            * @param ����������
            * @return ��
            * @par ע��
            */
            virtual void SetModuleResultBuffer(IN bool bBufferEnable, IN unsigned int nBufferNum) = 0;

            /**
            * @brief ��ȡģ������������
            * @param ����ʹ��
            * @param ����������
            * @return ��
            * @par ע��
            */
            virtual void GetModuleResultBuffer(OUT bool * const pbBufferEnable, OUT unsigned int * const pnBufferNum) = 0;

        public:
            /**
             * @brief �������ƻ�ȡ����ģ�����
             * @param ģ��������ʾ����
             * @return ����ģ�����ָ��
             * @par ע��
             */
            virtual void * operator[] (IN const char * const strKey) = 0;
        };
    }
}

/*  Note:Interfaces to export.  */
#ifdef __cplusplus
extern "C" {
#endif

    /* CH: ����,�Ƽ�(LoadSolution(char * strSolPath, char * strPassword, bool bSilentRun)) | EN: Obsolete,recommend(LoadSolution(char * strSolPath, char * strPassword, bool bSilentRun)) */
    /*  Note: Create tool instance for solution.  */
    IMVS_6000_PLATFORMSDK_API VisionMasterSDK::VmSolution::IVmSolution * __stdcall ImportSolution(IN const char * const strSolPath, IN const char * const strPassword, IN bool bSilentRun = false);

    /*  Note: Create tool instance for solution.  */
    IMVS_6000_PLATFORMSDK_API VisionMasterSDK::VmSolution::IVmSolution * __stdcall LoadSolution(IN const char * const strSolPath, IN const char * const strPassword, IN bool bSilentRun = false);

    /*  Note: Create tool instance for empty solution. This solution has no procedure.  */
    IMVS_6000_PLATFORMSDK_API VisionMasterSDK::VmSolution::IVmSolution * __stdcall CreateSolutionInstance(IN void * pCtrlHandle = NULL);
    
    /*  Note: Get tool instance for existed solution.  */
    IMVS_6000_PLATFORMSDK_API VisionMasterSDK::VmSolution::IVmSolution * __stdcall GetSolutionExistedInstance();

    /*  Note: Destroy tool instance for solution.  */
    IMVS_6000_PLATFORMSDK_API void __stdcall DestroySolutionInstance(IN VisionMasterSDK::VmSolution::IVmSolution* pToolInstance);

    /*  Note: Set server path.  */
    IMVS_6000_PLATFORMSDK_API void __stdcall SetServerPath(IN const char * const strServerPath);
#ifdef __cplusplus
}
#endif 

#endif    ///< _IVM_SOLUTION_H_