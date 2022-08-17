/***************************************************************************************************
 * File：IVmProcedure.h
 * Note：Interface for the procedure tool.
 *
 * Version：4.2
 * Date：2020-11
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
            * @brief 获取整型输入
            * @param 参数名称
            * @return 无，出错时抛出异常
            * @par 注解
            */
            virtual IntDataArray GetOutputInt(IN const char * const strParamName) = 0;

            /**
            * @brief 获取浮点型输入
            * @param 参数名称
            * @return 无，出错时抛出异常
            * @par 注解
            */
            virtual FloatDataArray GetOutputFloat(IN const char * const strParamName) = 0;

            /**
            * @brief 获取字符串型输入
            * @param 参数名称
            * @return 无，出错时抛出异常
            * @par 注解
            */
            virtual StringDataArray GetOutputString(IN const char * const strParamName) = 0;

            /**
            * @brief 获取二进制数据型输入
            * @param 参数名称
            * @return 二进制数据
            * @par 注解
            */
            virtual ByteArrayData GetOutputByteArray(IN const char * const strParamName) = 0;

            /**
            * @brief 获取图像结果（整个图像）
            * @param 参数名称
            * @return
            * @par 注解
            */
            virtual IoImage GetOutputImageV2(IN const char * const strParamName) = 0;

            /**
            * @brief 获取点输出数组
            * @param 参数名称
            * @return
            * @par 注解
            */
            virtual IoPointArray GetOutputPointArray(IN const char * const strParamName) = 0;

            /**
            * @brief 获取直线输出数组
            * @param 参数名称
            * @return
            * @par 注解
            */
            virtual IoLineArray GetOutputLineArray(IN const char * const strParamName) = 0;

            /**
            * @brief 获取圆输出数组
            * @param 参数名称
            * @return
            * @par 注解
            */
            virtual IoCircleArray GetOutputCircleArray(IN const char * const strParamName) = 0;

            /**
            * @brief 获取带角度矩形输出数组
            * @param 参数名称
            * @return
            * @par 注解
            */
            virtual IoRectBoxArray GetOutputBoxArray(IN const char * const strParamName) = 0;

            /**
            * @brief 获取无角度矩形(浮点型)输出数组
            * @param 参数名称
            * @return
            * @par 注解
            */
            virtual IoRectFArray GetOutputRectArray(IN const char * const strParamName) = 0;

            /**
            * @brief 获取位置修正输出数组
            * @param 参数名称
            * @return
            * @par 注解
            */
            virtual IoFixtureArray GetOutputFixtureArray(IN const char * const strParamName) = 0;

            /**
            * @brief 获取圆环输出数组
            * @param 参数名称
            * @return
            * @par 注解
            */
            virtual IoAnnulusArray GetOutputAnnulusArray(IN const char * const strParamName) = 0;

            /**
            * @brief 获取类别信息输出数组
            * @param 参数名称
            * @return
            * @par 注解
            */
            virtual IoClassInfoArray GetOutputClassInfoArray(IN const char * const strParamName) = 0;

            /**
            * @brief 获取带类别信息的图(界面可根据类别信息将灰度图显示成彩图)
            * @param 参数名称
            * @return
            * @par 注解
            */
            virtual IoPixelImage GetOutputPixelImage(IN const char * const strParamName) = 0;

            /**
            * @brief 获取位姿数组
            * @param 参数名称
            * @return
            * @par 注解
            */
            virtual IoPostureArray GetOutputPostureArray(IN const char * const strParamName) = 0;
            /**
            * @brief 获取多边形输出数组
            * @param 参数名称
            * @return
            * @par 注解
            */
            virtual IoPolygonArray GetOutputPolygonArray(IN const char * const strParamName) = 0;

            /**
            * @brief 所有所有输出名称信息（CONTOURPOINTS、POINTSET、小写的image,这三种类型不支持）
            * @param
            * @return
            * @par 注解
            */
            virtual IoNameInfoArray GetAllOutputNameInfo() = 0;

            /**
            * @brief 根据名称信息获取输出对象基类指针
            * @param
            * @return
            * @par 注解
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
            *  @brief  设置动态输入图像数据(仅当次执行起效)
            *  @param  参数名称
            *  @param  IoImage结构体指针数组
            *  @return 无
            *  @par    注解
            */
            virtual void SetInputImageV2(const char * const strParamName, const IoImage * const pstImageData) = 0;

            /** 
            *  @brief  设置动态输入矩形框数据(仅当次执行起效)
            *  @param  参数名称
            *  @param  IoRectBoxArray结构体指针数组
            *  @return 无
            *  @par    注解
            */
            virtual void SetInputBox(const char * const strParamName, const IoRectBoxArray * const pstBox) = 0;

            /** 
            *  @brief  设置动态输入圆环ROI数据(仅当次执行起效)
            *  @param  参数名称
            *  @param  IoAnnulusArray结构体指针数组
            *  @return 无
            *  @par    注解
            */
            virtual void SetInputAnnulus(const char * const strParamName, const IoAnnulusArray * const pstAnnulus) = 0;

            /** 
            *  @brief  设置动态输入圆形数据(仅当次执行起效)
            *  @param  参数名称
            *  @param  IoCircleArray结构体指针数组
            *  @return 无
            *  @par    注解
            */
            virtual void SetInputCircle(const char * const strParamName, const IoCircleArray * const pstCircle) = 0;

            /** 
            *  @brief  设置动态输入线型数据(仅当次执行起效)
            *  @param  参数名称
            *  @param  IoLineArray结构体指针数组
            *  @return 无
            *  @par    注解
            */
            virtual void SetInputLine(const char * const strParamName, const IoLineArray * const pstLine) = 0;

            /** 
            *  @brief  设置动态输入点型数据(仅当次执行起效)
            *  @param  参数名称
            *  @param  IoPointArray结构体指针数组
            *  @return 无
            *  @par    注解
            */
            virtual void SetInputPoint(const char * const strParamName, const IoPointArray * const pstPointF) = 0;

            /** 
            *  @brief  设置动态输入位置修正数据(仅当次执行起效)
            *  @param  参数名称
            *  @param  IoFixtureArray结构体指针数组
            *  @return 无
            *  @par    注解
            */
            virtual void SetInputFixture(const char * const strParamName, const IoFixtureArray * const pstFixture) = 0;

            /** 
            *  @brief  设置动态输入矩形数据(仅当次执行起效)
            *  @param  参数名称
            *  @param  IoRectFArray结构体指针数组
            *  @return 无
            *  @par    注解
            */
            virtual void SetInputRect(const char * const strParamName, const IoRectFArray * const pstRectF) = 0;

            /** 
            *  @brief  设置动态输入类别信息数据(仅当次执行起效)
            *  @param  参数名称
            *  @param  IoClassInfoArray结构体指针数组
            *  @return 无
            *  @par 注解
            */
            virtual void SetInputClassInfo(const char * const strParamName, const IoClassInfoArray * const pstClassInfo) = 0;

            /** 
            *  @brief  设置动态输入像素图像数据(仅当次执行起效)
            *  @param  参数名称
            *  @param  IoPixelImage结构体指针数组
            *  @return 无
            *  @par    注解
            */
            virtual void SetInputPixelImage(const char * const strParamName, const IoPixelImage * const pstPixelImage) = 0;
            /** 
            *  @brief  设置动态输入多边形数据(仅当次执行起效)
            *  @param  参数名称
            *  @param  IoPolygonArray结构体指针数组
            *  @return 无
            *  @par    注解
            */
            virtual void SetInputPolygon(const char * const strParamName, const IoPolygonArray * const pstPolygon) = 0;
            /** 
            *  @brief  设置动态输入位姿数据(仅当次执行起效)
            *  @param  参数名称
            *  @param  IoPostureArray结构体指针数组
            *  @return 无
            *  @par    注解
            */
            virtual void SetInputPosture(const char * const strParamName, const IoPostureArray * const pstPosture) = 0;
        };
        /*************************** Params Class End ***************************/

        /*************************** Tool Class Start ***************************/
        class IVmProcedureEvent
        {
        public:
            /**
            * @brief 流程开始执行状态回调
            * @param pstWorkStatus [IN] 流程状态
            * @par 注解
            */
            virtual void OnWorkBeginStatusCallBack(IN const IMVS_PF_MODULE_WORK_STAUS * const pstWorkStatus, IN void * const pUser) = 0;

            /**
            * @brief 流程结束执行状态回调
            * @param pstWorkStatus [IN] 流程状态
            * @par 注解
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
            * @brief 执行一次
            * @param 触发字符串
            * @param 是否等待执行结束
            * @return 无，出错时抛出异常
            * @par 注解
            * 流程执行一次
            */
            virtual void Run(IN const char * const strCmd = NULL, IN bool bIsWait = true) = 0;

            /**
            * @brief 执行一次
            * @param 触发字符串
            * @param 当前执行次数
            * @param 是否等待执行结束
            * @return 无，出错时抛出异常
            * @par 注解
            * 流程执行一次
            */
            virtual void Run(OUT unsigned int * const pnRunCount, IN const char * const strCmd = NULL, IN bool bIsWait = true) = 0;

            /**
            * @brief 执行一次点对点模式
            * @param 超时时间
            * @return 无，出错时抛出异常
            * @par 注解
            * 流程执行一次
            */
            virtual void RunP2P(IN unsigned int nTimeout) = 0;

            /**
            * @brief 连续运行
            * @param 无
            * @return 无，出错时抛出异常
            * @par 注解
            * 流程连续运行
            */
            virtual void Runing(void) = 0;

            /**
            * @brief 停止连续运行
            * @param 等待超时 （单位：秒）
            * @return 无，出错时抛出异常
            * @par 注解
            * 流程停止连续运行
            */
            virtual void StopRun(IN const unsigned int nWaitTime = 3) = 0;

            /**
            * @brief 设置连续运行时间间隔
            * @param 时间间隔 （单位：ms）
            * @return 无，出错时抛出异常
            * @par 注解
            * 设置流程连续运行时间间隔
            */
            virtual void SetRunInterval(IN const unsigned int nMilliSecond) = 0;

            /**
            * @brief 禁用流程
            * @param 无
            * @return 无
            * @par 注解
            */
            virtual void DisableProcedure(void) = 0;

            /**
            * @brief 启用流程
            * @param 无
            * @return 无
            * @par 注解
            */
            virtual void EnableProcedure(void) = 0;

            /**
            * @brief 流程是否禁用
            * @param 无
            * @return 流程禁用返回true，未禁用返回false
            * @par 注解
            */
            virtual bool IsProcedureDisable(void) = 0;

            /**
            * @brief 保存流程至文件
            * @param 流程路径
            * @param 流程文件密码（预留）
            * @return 无，出错时抛出异常
            * @par 注解
            * 弃用,推荐(SaveAsProcedure(const char * const strPrcPath, const char * const strPassword)
            */
            virtual void ExportProcess(IN const char * const strPrcPath, IN const char * const strPassword = NULL) = 0;

            /**
            * @brief 保存流程至文件
            * @param 流程路径
            * @param 流程文件密码（预留）
            * @return 无，出错时抛出异常
            * @par 注解
            */
            virtual void SaveAsProcedure(IN const char * const strPrcPath, IN const char * const strPassword = NULL) = 0;

            /**
            * @brief 获取所有模块信息列表
            * @param 空
            * @return 所有模块信息列表
            * @par 注解
            */
            virtual ModuleInfoList * GetAllModuleList(void) = 0;

            /**
            * @brief 获取流程第一层级模块列表（不包含Group内部模块）
            * @param 空
            * @return 流程第一层级模块列表
            * @par 注解
            */
            virtual ModuleInfoList * GetProcedureModuleList(void) = 0;

            /**
            * @brief 设置流程运行策略接口
            * @param pstRunPolicyInfo [IN] 流程运行策略信息
            * @return 空
            * @par 注解
            */
            virtual void SetProcedureRunPolicy(IN const ProcedureRunPolicy * const pstRunPolicyInfo) = 0;

            /**
            * @brief 注册流程回调事件对象
            * @param pProcedureEvent [IN] 事件对象指针
            * @par 注解
            */
            virtual void RegisterCallBackEvent(IN IVmProcedureEvent* pProcedureEvent, IN void * const pUser) = 0;

            /**
            * @brief 解注册流程回调事件对象
            * @par 注解
            */
            virtual void UnRegisterCallBackEvent() = 0;

            /**
            * @brief 获取结果输出配置(V4.2废弃)
            * @param 输出配置参数
            * @return 整型结果
            * @par 注解
            */
            virtual IntResultInfo * GetIntOutputResult(IN const char * const strParam) = 0;

            /**
            * @brief 获取结果输出配置(V4.2废弃)
            * @param 输出配置参数
            * @return 浮点型结果
            * @par 注解
            */
            virtual FloatResultInfo * GetFloatOutputResult(IN const char * const strParam) = 0;

            /**
            * @brief 获取结果输出配置(V4.2废弃)
            * @param 输出配置参数
            * @return 字符串型结果
            * @par 注解
            */
            virtual StringResultInfo * GetStringOutputResult(IN const char * const strParam) = 0;

            /**
            * @brief 获取结果输出配置(V4.2废弃)
            * @param 输出配置参数
            * @return 图像型结果
            * @par 注解
            */
            virtual ImageResultInfo * GetImageOutputResult(IN const char * const strParam) = 0;

            /**
            * @brief 获取结果输出配置(V4.2废弃)
            * @param 输出配置参数
            * @return 点集型结果
            * @par 注解
            */
            virtual PointsetResultInfo * GetPointsetOutputResult(IN const char * const strParam) = 0;

            /**
            * @brief 获取流程名称(UTF8格式)(预留，内部使用)
            * @param void
            * @return 流程名称
            * @par 注解
            */
            virtual const char * GetName(void) = 0;

            /**
            * @brief 获取内部所需信息(预留)
            * @param void
            * @return 流程内部信息
            * @par 注解
            */
            virtual void * GetControlInfo(void) = 0;
            /**
            * @par 说明
            * 参数对象，失败返回NULL
            * @par 注解
            * 通过参数对象可设置获取模块参数
            */
            virtual IMVSProcedureParams* GetParamObj() = 0;

            /**
            * @par 说明
            * 查找结果，未执行或执行失败返回NULL
            * @par 权限
            * 只读
            */
            virtual IMVSProcedureResults* GetResult() = 0;

        public:
            /**
            * @brief 根据名称获取模块对象
            * @param 模块显示名称
            * @return 模块对象指针
            * @par 注解
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
        brief: EN: Password parameter is reserved. | CH: 密码参数预留，暂不支持 */
    /* CH: 弃用,推荐(LoadProcedure(const char * const strPrcPath, const char * const strPassword)) | EN: Obsolete,recommend(LoadProcedure(const char * const strPrcPath, const char * const strPassword)) */
    IMVS_6000_PLATFORMSDK_API VisionMasterSDK::VmProcedure::IVmProcedure * __stdcall ImportProcess(IN const char * const strPrcPath, IN const char * const strPassword = NULL);
    /*  Note: Create tool instance for procedure.
    brief: EN: Password parameter is reserved. | CH: 密码参数预留，暂不支持 */
    IMVS_6000_PLATFORMSDK_API VisionMasterSDK::VmProcedure::IVmProcedure * __stdcall LoadProcedure(IN const char * const strPrcPath, IN const char * const strPassword = NULL);
    /*  Note: Destroy tool instance for procedure.  */
    IMVS_6000_PLATFORMSDK_API void __stdcall DestroyProcedureInstance(IN VisionMasterSDK::VmProcedure::IVmProcedure* pToolInstance);

#ifdef __cplusplus
}
#endif 

#endif    ///< _IVM_PROCEDURE_H_