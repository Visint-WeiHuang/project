#ifndef VISINT_CAMACQ_H
#define VISINT_CAMACQ_H

#include <QWidget>
#include <QtWidgets/QMainWindow>
#include "ui_visint_camacq.h"
#include <String>
#include "SapClassBasic.h"
#include "Configue_Parameters.h"

using namespace std;

class VisInt_CamAcq : public QMainWindow
{
	Q_OBJECT

public:
	VisInt_CamAcq(QWidget *parent = 0);
	~VisInt_CamAcq();

private:
	Ui::VisInt_CamAcqClass ui;
public:
	struct  StructImageProperty
	{
		LONG iImageWidth;        //图像宽度
		LONG iImageHeight;       //图像高度
		LONG iImageDepth;        //图像位深
	}StImageProperty;
	//---------------------图像信息结构体-------------------------------------------------------------------------------------------


	//---------------------相机相关变量---------------------------------------------------------------------------------------------
public:
	SapAcqDevice	*m_AcqDevice;   //相机采集相关变量
	SapBuffer		*m_Buffers;     //相机buffer，采集数据存放变量
	SapTransfer		*m_Xfer;
	SapView         *m_View;        //显示变量
	SapLocation m_ServerLocation;   //初始化相机时用到的变量
	string strConfigFileNamePath;   //配置文件路径
	string m_strServerName;         //相机名称 
	Configue_Parameters *parameters_view;//设置参数界面

	int m_iServerIndex;             //相机索引

	//CString C_ExposureTime;         //曝光时间 CString
	//CString C_Gain;                 //增益 CString
	double  dExposureTime;          //曝光时间 double
	double  dGain;                  //增益 double

	int iImgAcqIndex;              //图像采集序号
	string strSaveImagePath;       //存图路径
	bool bContinueSaveImage;       //连续存图布尔变量
	bool bSnapImage;               //单张存图布尔变量
	//---------------------相机相关变量---------------------------------------------------------------------------------------------

	//---------------------相机相关函数---------------------------------------------------------------------------------------------
public:
	BOOL LQ_CreateObjects();   //创建对象

	BOOL LQ_DestroyObjects();  //销毁对象

	static void XferCallback(SapXferCallbackInfo *pInfo);//回调函数

	bool LQ_StartGrab();     //采集函数

	bool LQ_StopGrab();   //停止采集函数

	bool LQ_InitCamera();  //初始化相机

	void LQ_GetImageProperty(StructImageProperty* stImageProperty); //获取图像信息

	void LQ_ImageProperty(StructImageProperty* stImageProperty, LONG lWidth, LONG lHeight, LONG lPixelDepth); //设置图像信息

	bool LQ_ConnectCamera();//连接相机

	bool LQ_DisConnectCamera();//断开相机

	bool LQ_SetFeatureVal(BSTR bStrFeatureName, DOUBLE dFeatureVal);//设置参数

	bool LQ_GetFeatureVal(BSTR bStrFeatureName, DOUBLE* dFeatureVal); //获取参数

	bool LQ_SaveImage(LONG ImageWidth, LONG ImageHeight, CHAR* pImageData, BSTR bstrImageSavePath); //存图

	bool OnInitCamera();

	bool SetParameters();//设置参数

public slots:
	void OnBnClickedInitcamButton();
	void OnBnClickedConnectcamButton();
	void OnBnClickedSetParametersButton();

};

#endif // VISINT_CAMACQ_H
