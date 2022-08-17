/***************************************************************************************************
 * File��IVmProcedure.h
 * Note��Interface for the procedure tool.
 *
 * Version��4.2
 * Date��2020-11
 ***************************************************************************************************/
#ifndef _IVM_PROCEDURE_H_
#define _IVM_PROCEDURE_H_

#include "IVmExport.h"
#include "VmModuleResultBase.h"
#include "VmToolBase.h"
#include "IVmDynamicIoDefine.h"

namespace VisionMasterSDK
{
    namespace VmProcedure
    {
        /*************************** Results Class Start ***************************/
        /*  Note: Interface Classes of the result of the IMVSProcedureResults.  */
        class IMVSProcedureResults : public CModuleResultBase
        {
        protected:
            ///< Constructor and Destructor
            explicit IMVSProcedureResults() {}
            virtual ~IMVSProcedureResults() {}

        public:

            /**
            * @brief ��ȡ��������
            * @param ��������
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            */
            virtual IntDataArray GetOutputInt(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡ����������
            * @param ��������
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            */
            virtual FloatDataArray GetOutputFloat(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡ�ַ���������
            * @param ��������
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            */
            virtual StringDataArray GetOutputString(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡ����������������
            * @param ��������
            * @return ����������
            * @par ע��
            */
            virtual ByteArrayData GetOutputByteArray(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡͼ����������ͼ��
            * @param ��������
            * @return
            * @par ע��
            */
            virtual IoImage GetOutputImageV2(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡ���������
            * @param ��������
            * @return
            * @par ע��
            */
            virtual IoPointArray GetOutputPointArray(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡֱ���������
            * @param ��������
            * @return
            * @par ע��
            */
            virtual IoLineArray GetOutputLineArray(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡԲ�������
            * @param ��������
            * @return
            * @par ע��
            */
            virtual IoCircleArray GetOutputCircleArray(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡ���ǶȾ����������
            * @param ��������
            * @return
            * @par ע��
            */
            virtual IoRectBoxArray GetOutputBoxArray(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡ�޽ǶȾ���(������)�������
            * @param ��������
            * @return
            * @par ע��
            */
            virtual IoRectFArray GetOutputRectArray(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡλ�������������
            * @param ��������
            * @return
            * @par ע��
            */
            virtual IoFixtureArray GetOutputFixtureArray(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡԲ���������
            * @param ��������
            * @return
            * @par ע��
            */
            virtual IoAnnulusArray GetOutputAnnulusArray(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡ�����Ϣ�������
            * @param ��������
            * @return
            * @par ע��
            */
            virtual IoClassInfoArray GetOutputClassInfoArray(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡ�������Ϣ��ͼ(����ɸ��������Ϣ���Ҷ�ͼ��ʾ�ɲ�ͼ)
            * @param ��������
            * @return
            * @par ע��
            */
            virtual IoPixelImage GetOutputPixelImage(IN const char * const strParamName) = 0;

            /**
            * @brief ��ȡλ������
            * @param ��������
            * @return
            * @par ע��
            */
            virtual IoPostureArray GetOutputPostureArray(IN const char * const strParamName) = 0;
            /**
            * @brief ��ȡ������������
            * @param ��������
            * @return
            * @par ע��
            */
            virtual IoPolygonArray GetOutputPolygonArray(IN const char * const strParamName) = 0;

            /**
            * @brief �����������������Ϣ��CONTOURPOINTS��POINTSET��Сд��image,���������Ͳ�֧�֣�
            * @param
            * @return
            * @par ע��
            */
            virtual IoNameInfoArray GetAllOutputNameInfo() = 0;

            /**
            * @brief ����������Ϣ��ȡ����������ָ��
            * @param
            * @return
            * @par ע��
            */
            virtual VmIoBase* GetOutputObject(IN const IoNameInfo& stNameInfo) = 0;
        };
        /*************************** Results Class End ***************************/

        /*************************** Params Class Start ***************************/
        /*  Note: Interface Classes of the parameter of the IMVSProcedureParams.  */
        class IMVSProcedureParams : public CModuParamsBase
        {
        protected:
            ///< Constructor and Destructor
            explicit IMVSProcedureParams() {}
            virtual ~IMVSProcedureParams() {}

        public:

            /**   
            *  @brief  ���ö�̬����ͼ������(������ִ����Ч)
            *  @param  ��������
            *  @param  IoImage�ṹ��ָ������
            *  @return ��
            *  @par    ע��
            */
            virtual void SetInputImageV2(const char * const strParamName, const IoImage * const pstImageData) = 0;

            /** 
            *  @brief  ���ö�̬������ο�����(������ִ����Ч)
            *  @param  ��������
            *  @param  IoRectBoxArray�ṹ��ָ������
            *  @return ��
            *  @par    ע��
            */
            virtual void SetInputBox(const char * const strParamName, const IoRectBoxArray * const pstBox) = 0;

            /** 
            *  @brief  ���ö�̬����Բ��ROI����(������ִ����Ч)
            *  @param  ��������
            *  @param  IoAnnulusArray�ṹ��ָ������
            *  @return ��
            *  @par    ע��
            */
            virtual void SetInputAnnulus(const char * const strParamName, const IoAnnulusArray * const pstAnnulus) = 0;

            /** 
            *  @brief  ���ö�̬����Բ������(������ִ����Ч)
            *  @param  ��������
            *  @param  IoCircleArray�ṹ��ָ������
            *  @return ��
            *  @par    ע��
            */
            virtual void SetInputCircle(const char * const strParamName, const IoCircleArray * const pstCircle) = 0;

            /** 
            *  @brief  ���ö�̬������������(������ִ����Ч)
            *  @param  ��������
            *  @param  IoLineArray�ṹ��ָ������
            *  @return ��
            *  @par    ע��
            */
            virtual void SetInputLine(const char * const strParamName, const IoLineArray * const pstLine) = 0;

            /** 
            *  @brief  ���ö�̬�����������(������ִ����Ч)
            *  @param  ��������
            *  @param  IoPointArray�ṹ��ָ������
            *  @return ��
            *  @par    ע��
            */
            virtual void SetInputPoint(const char * const strParamName, const IoPointArray * const pstPointF) = 0;

            /** 
            *  @brief  ���ö�̬����λ����������(������ִ����Ч)
            *  @param  ��������
            *  @param  IoFixtureArray�ṹ��ָ������
            *  @return ��
            *  @par    ע��
            */
            virtual void SetInputFixture(const char * const strParamName, const IoFixtureArray * const pstFixture) = 0;

            /** 
            *  @brief  ���ö�̬�����������(������ִ����Ч)
            *  @param  ��������
            *  @param  IoRectFArray�ṹ��ָ������
            *  @return ��
            *  @par    ע��
            */
            virtual void SetInputRect(const char * const strParamName, const IoRectFArray * const pstRectF) = 0;

            /** 
            *  @brief  ���ö�̬���������Ϣ����(������ִ����Ч)
            *  @param  ��������
            *  @param  IoClassInfoArray�ṹ��ָ������
            *  @return ��
            *  @par ע��
            */
            virtual void SetInputClassInfo(const char * const strParamName, const IoClassInfoArray * const pstClassInfo) = 0;

            /** 
            *  @brief  ���ö�̬��������ͼ������(������ִ����Ч)
            *  @param  ��������
            *  @param  IoPixelImage�ṹ��ָ������
            *  @return ��
            *  @par    ע��
            */
            virtual void SetInputPixelImage(const char * const strParamName, const IoPixelImage * const pstPixelImage) = 0;
            /** 
            *  @brief  ���ö�̬������������(������ִ����Ч)
            *  @param  ��������
            *  @param  IoPolygonArray�ṹ��ָ������
            *  @return ��
            *  @par    ע��
            */
            virtual void SetInputPolygon(const char * const strParamName, const IoPolygonArray * const pstPolygon) = 0;
            /** 
            *  @brief  ���ö�̬����λ������(������ִ����Ч)
            *  @param  ��������
            *  @param  IoPostureArray�ṹ��ָ������
            *  @return ��
            *  @par    ע��
            */
            virtual void SetInputPosture(const char * const strParamName, const IoPostureArray * const pstPosture) = 0;
        };
        /*************************** Params Class End ***************************/

        /*************************** Tool Class Start ***************************/
        class IVmProcedureEvent
        {
        public:
            /**
            * @brief ���̿�ʼִ��״̬�ص�
            * @param pstWorkStatus [IN] ����״̬
            * @par ע��
            */
            virtual void OnWorkBeginStatusCallBack(IN const IMVS_PF_MODULE_WORK_STAUS * const pstWorkStatus, IN void * const pUser) = 0;

            /**
            * @brief ���̽���ִ��״̬�ص�
            * @param pstWorkStatus [IN] ����״̬
            * @par ע��
            */
            virtual void OnWorkEndStatusCallBack(IN const IMVS_PF_MODULE_WORK_STAUS * const pstWorkStatus, IN void * const pUser) = 0;
        };

        class IVmProcedure : public CVmToolBase
        {
        protected:
            ///< Constructor and Destructor
            explicit IVmProcedure() {}
            virtual ~IVmProcedure() {}

        public:
            /**
            * @brief ִ��һ��
            * @param �����ַ���
            * @param �Ƿ�ȴ�ִ�н���
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            * ����ִ��һ��
            */
            virtual void Run(IN const char * const strCmd = NULL, IN bool bIsWait = true) = 0;

            /**
            * @brief ִ��һ��
            * @param �����ַ���
            * @param ��ǰִ�д���
            * @param �Ƿ�ȴ�ִ�н���
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            * ����ִ��һ��
            */
            virtual void Run(OUT unsigned int * const pnRunCount, IN const char * const strCmd = NULL, IN bool bIsWait = true) = 0;

            /**
            * @brief ִ��һ�ε�Ե�ģʽ
            * @param ��ʱʱ��
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            * ����ִ��һ��
            */
            virtual void RunP2P(IN unsigned int nTimeout) = 0;

            /**
            * @brief ��������
            * @param ��
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            * ������������
            */
            virtual void Runing(void) = 0;

            /**
            * @brief ֹͣ��������
            * @param �ȴ���ʱ ����λ���룩
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            * ����ֹͣ��������
            */
            virtual void StopRun(IN const unsigned int nWaitTime = 3) = 0;

            /**
            * @brief ������������ʱ����
            * @param ʱ���� ����λ��ms��
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            * ����������������ʱ����
            */
            virtual void SetRunInterval(IN const unsigned int nMilliSecond) = 0;

            /**
            * @brief ��������
            * @param ��
            * @return ��
            * @par ע��
            */
            virtual void DisableProcedure(void) = 0;

            /**
            * @brief ��������
            * @param ��
            * @return ��
            * @par ע��
            */
            virtual void EnableProcedure(void) = 0;

            /**
            * @brief �����Ƿ����
            * @param ��
            * @return ���̽��÷���true��δ���÷���false
            * @par ע��
            */
            virtual bool IsProcedureDisable(void) = 0;

            /**
            * @brief �����������ļ�
            * @param ����·��
            * @param �����ļ����루Ԥ����
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            * ����,�Ƽ�(SaveAsProcedure(const char * const strPrcPath, const char * const strPassword)
            */
            virtual void ExportProcess(IN const char * const strPrcPath, IN const char * const strPassword = NULL) = 0;

            /**
            * @brief �����������ļ�
            * @param ����·��
            * @param �����ļ����루Ԥ����
            * @return �ޣ�����ʱ�׳��쳣
            * @par ע��
            */
            virtual void SaveAsProcedure(IN const char * const strPrcPath, IN const char * const strPassword = NULL) = 0;

            /**
            * @brief ��ȡ����ģ����Ϣ�б�
            * @param ��
            * @return ����ģ����Ϣ�б�
            * @par ע��
            */
            virtual ModuleInfoList * GetAllModuleList(void) = 0;

            /**
            * @brief ��ȡ���̵�һ�㼶ģ���б�������Group�ڲ�ģ�飩
            * @param ��
            * @return ���̵�һ�㼶ģ���б�
            * @par ע��
            */
            virtual ModuleInfoList * GetProcedureModuleList(void) = 0;

            /**
            * @brief �����������в��Խӿ�
            * @param pstRunPolicyInfo [IN] �������в�����Ϣ
            * @return ��
            * @par ע��
            */
            virtual void SetProcedureRunPolicy(IN const ProcedureRunPolicy * const pstRunPolicyInfo) = 0;

            /**
            * @brief ע�����̻ص��¼�����
            * @param pProcedureEvent [IN] �¼�����ָ��
            * @par ע��
            */
            virtual void RegisterCallBackEvent(IN IVmProcedureEvent* pProcedureEvent, IN void * const pUser) = 0;

            /**
            * @brief ��ע�����̻ص��¼�����
            * @par ע��
            */
            virtual void UnRegisterCallBackEvent() = 0;

            /**
            * @brief ��ȡ����������(V4.2����)
            * @param ������ò���
            * @return ���ͽ��
            * @par ע��
            */
            virtual IntResultInfo * GetIntOutputResult(IN const char * const strParam) = 0;

            /**
            * @brief ��ȡ����������(V4.2����)
            * @param ������ò���
            * @return �����ͽ��
            * @par ע��
            */
            virtual FloatResultInfo * GetFloatOutputResult(IN const char * const strParam) = 0;

            /**
            * @brief ��ȡ����������(V4.2����)
            * @param ������ò���
            * @return �ַ����ͽ��
            * @par ע��
            */
            virtual StringResultInfo * GetStringOutputResult(IN const char * const strParam) = 0;

            /**
            * @brief ��ȡ����������(V4.2����)
            * @param ������ò���
            * @return ͼ���ͽ��
            * @par ע��
            */
            virtual ImageResultInfo * GetImageOutputResult(IN const char * const strParam) = 0;

            /**
            * @brief ��ȡ����������(V4.2����)
            * @param ������ò���
            * @return �㼯�ͽ��
            * @par ע��
            */
            virtual PointsetResultInfo * GetPointsetOutputResult(IN const char * const strParam) = 0;

            /**
            * @brief ��ȡ��������(UTF8��ʽ)(Ԥ�����ڲ�ʹ��)
            * @param void
            * @return ��������
            * @par ע��
            */
            virtual const char * GetName(void) = 0;

            /**
            * @brief ��ȡ�ڲ�������Ϣ(Ԥ��)
            * @param void
            * @return �����ڲ���Ϣ
            * @par ע��
            */
            virtual void * GetControlInfo(void) = 0;
            /**
            * @par ˵��
            * ��������ʧ�ܷ���NULL
            * @par ע��
            * ͨ��������������û�ȡģ�����
            */
            virtual IMVSProcedureParams* GetParamObj() = 0;

            /**
            * @par ˵��
            * ���ҽ����δִ�л�ִ��ʧ�ܷ���NULL
            * @par Ȩ��
            * ֻ��
            */
            virtual IMVSProcedureResults* GetResult() = 0;

        public:
            /**
            * @brief �������ƻ�ȡģ�����
            * @param ģ����ʾ����
            * @return ģ�����ָ��
            * @par ע��
            */
            virtual void * operator[] (IN const char * const strKey) = 0;
        };
        /*************************** Tool Class End ***************************/
    }
}

/*  Note:Interfaces to export.  */
#ifdef __cplusplus
extern "C" {
#endif

    /*  Note: Create tool instance for procedure. 
        brief: EN: Password parameter is reserved. | CH: �������Ԥ�����ݲ�֧�� */
    /* CH: ����,�Ƽ�(LoadProcedure(const char * const strPrcPath, const char * const strPassword)) | EN: Obsolete,recommend(LoadProcedure(const char * const strPrcPath, const char * const strPassword)) */
    IMVS_6000_PLATFORMSDK_API VisionMasterSDK::VmProcedure::IVmProcedure * __stdcall ImportProcess(IN const char * const strPrcPath, IN const char * const strPassword = NULL);
    /*  Note: Create tool instance for procedure.
    brief: EN: Password parameter is reserved. | CH: �������Ԥ�����ݲ�֧�� */
    IMVS_6000_PLATFORMSDK_API VisionMasterSDK::VmProcedure::IVmProcedure * __stdcall LoadProcedure(IN const char * const strPrcPath, IN const char * const strPassword = NULL);
    /*  Note: Destroy tool instance for procedure.  */
    IMVS_6000_PLATFORMSDK_API void __stdcall DestroyProcedureInstance(IN VisionMasterSDK::VmProcedure::IVmProcedure* pToolInstance);

#ifdef __cplusplus
}
#endif 

#endif    ///< _IVM_PROCEDURE_H_