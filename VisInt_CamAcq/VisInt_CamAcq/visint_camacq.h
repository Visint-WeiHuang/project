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
		LONG iImageWidth;        //ͼ����
		LONG iImageHeight;       //ͼ��߶�
		LONG iImageDepth;        //ͼ��λ��
	}StImageProperty;
	//---------------------ͼ����Ϣ�ṹ��-------------------------------------------------------------------------------------------


	//---------------------�����ر���---------------------------------------------------------------------------------------------
public:
	SapAcqDevice	*m_AcqDevice;   //����ɼ���ر���
	SapBuffer		*m_Buffers;     //���buffer���ɼ����ݴ�ű���
	SapTransfer		*m_Xfer;
	SapView         *m_View;        //��ʾ����
	SapLocation m_ServerLocation;   //��ʼ�����ʱ�õ��ı���
	string strConfigFileNamePath;   //�����ļ�·��
	string m_strServerName;         //������� 
	Configue_Parameters *parameters_view;//���ò�������

	int m_iServerIndex;             //�������

	//CString C_ExposureTime;         //�ع�ʱ�� CString
	//CString C_Gain;                 //���� CString
	double  dExposureTime;          //�ع�ʱ�� double
	double  dGain;                  //���� double

	int iImgAcqIndex;              //ͼ��ɼ����
	string strSaveImagePath;       //��ͼ·��
	bool bContinueSaveImage;       //������ͼ��������
	bool bSnapImage;               //���Ŵ�ͼ��������
	//---------------------�����ر���---------------------------------------------------------------------------------------------

	//---------------------�����غ���---------------------------------------------------------------------------------------------
public:
	BOOL LQ_CreateObjects();   //��������

	BOOL LQ_DestroyObjects();  //���ٶ���

	static void XferCallback(SapXferCallbackInfo *pInfo);//�ص�����

	bool LQ_StartGrab();     //�ɼ�����

	bool LQ_StopGrab();   //ֹͣ�ɼ�����

	bool LQ_InitCamera();  //��ʼ�����

	void LQ_GetImageProperty(StructImageProperty* stImageProperty); //��ȡͼ����Ϣ

	void LQ_ImageProperty(StructImageProperty* stImageProperty, LONG lWidth, LONG lHeight, LONG lPixelDepth); //����ͼ����Ϣ

	bool LQ_ConnectCamera();//�������

	bool LQ_DisConnectCamera();//�Ͽ����

	bool LQ_SetFeatureVal(BSTR bStrFeatureName, DOUBLE dFeatureVal);//���ò���

	bool LQ_GetFeatureVal(BSTR bStrFeatureName, DOUBLE* dFeatureVal); //��ȡ����

	bool LQ_SaveImage(LONG ImageWidth, LONG ImageHeight, CHAR* pImageData, BSTR bstrImageSavePath); //��ͼ

	bool OnInitCamera();

	bool SetParameters();//���ò���

public slots:
	void OnBnClickedInitcamButton();
	void OnBnClickedConnectcamButton();
	void OnBnClickedSetParametersButton();

};

#endif // VISINT_CAMACQ_H
