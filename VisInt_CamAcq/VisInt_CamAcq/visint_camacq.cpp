#include "visint_camacq.h"
#include "SapClassBasic.h"
#include "QPushButton.h"
#include "QDebug"
#include "QLabel"
#include "QMessageBox"
#include <String>

using namespace std;

VisInt_CamAcq::VisInt_CamAcq(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//OnInitCamera();

	connect(ui.BtInit, &QPushButton::released, this, &VisInt_CamAcq::OnBnClickedInitcamButton);
	connect(ui.BtConfig, &QPushButton::released, this, &VisInt_CamAcq::OnBnClickedSetParametersButton);

	//connect()
}

VisInt_CamAcq::~VisInt_CamAcq()
{
	if (parameters_view != NULL) delete parameters_view;
}


//-------�ۺ���------

//--------��ʼ������ؼ�-------
void VisInt_CamAcq::OnBnClickedInitcamButton()
{
	OnInitCamera();
}


//------��������ؼ�-----------
void VisInt_CamAcq::OnBnClickedConnectcamButton()
{
	LQ_ConnectCamera();
}

//------�����������-----------
void VisInt_CamAcq::OnBnClickedSetParametersButton()
{
	SetParameters();
}

bool VisInt_CamAcq::SetParameters()
{
	parameters_view = new Configue_Parameters;
	if (parameters_view){
		parameters_view->show();
		return true;
	} else return false;
}

//�������,ʵ��������ײ���ڴ棬�����ڴ�֮�������
bool VisInt_CamAcq::LQ_ConnectCamera()
{
	bool b = LQ_CreateObjects();//��������//�������

	QMessageBox *MesDlg = new QMessageBox;
	//MesDlg->resize(300, 300);
	//MesDlg->setFixedSize(500, 200);
	MesDlg->setAttribute(Qt::WA_DeleteOnClose);
	MesDlg->setWindowTitle(QStringLiteral("�������"));
	if (b)
	{
		MesDlg->setText(QStringLiteral("�ɹ����ӣ�"));
		return true;
	}
	else
	{
		MesDlg->setText(QStringLiteral("����ʧ�ܣ�"));
		return false;
	}

}

//��ʼ�����
bool VisInt_CamAcq::OnInitCamera()
{

	//------------------��ʼ������----------------------------------
	m_strServerName = "";
	m_iServerIndex = 0;
	//C_ExposureTime = "";                           //�ع�ʱ��
	//C_Gain = "";                                   //����
	dExposureTime = 0;
	dGain = 0;
	iImgAcqIndex = 0;                              //ͼ��ɼ����
	strConfigFileNamePath = "C:\\Users\\Lenovo\\Desktop\\T_Linea_M2048-7um_Default_Default.ccf";//�����ļ�·��
	strSaveImagePath = "C:\\Users\\Lenovo\\Desktop\\image\\";   //���ô�ͼ·��
	bContinueSaveImage = false;                    //������ͼ��������
	bSnapImage = false;                            //���Ŵ�ͼ��������
	//------------------��ʼ������----------------------------------
	QMessageBox *MesDlg = new QMessageBox;
	//MesDlg->resize(300, 300);
	//MesDlg->setFixedSize(500, 200);
	MesDlg->setAttribute(Qt::WA_DeleteOnClose);
	MesDlg->setWindowTitle(QStringLiteral("��ʼ�����!"));
	

	/*��ȡ����������*/
	char chServerName[128];//"Linea_M4096-7um_1"

	if (SapManager::GetServerName(1, chServerName, sizeof(chServerName)))
	{
		m_strServerName = string(chServerName);
		m_iServerIndex = 0;
		SapLocation location(m_strServerName.c_str(), m_iServerIndex);
		m_ServerLocation = location;
		m_AcqDevice = new SapAcqDevice(m_ServerLocation, strConfigFileNamePath.c_str());
		m_Buffers = new SapBufferWithTrash(2, m_AcqDevice);
		m_View = new SapView(m_Buffers, SapHwndAutomatic); //������������ʾ�ģ�����ѡ��Ҫ��
		m_Xfer = new SapAcqDeviceToBuf(m_AcqDevice, m_Buffers, XferCallback, this);//���ûص�����	

		//ֻ��Ϊ������
		MesDlg->setText(QStringLiteral("��ʼ���ɹ���"));
		MesDlg->show();
		return true;
	}
	else
	{
		MesDlg->setText(QStringLiteral("��ʼ��ʧ�ܣ�"));
		MesDlg->show();
		return false;
	}

}

void VisInt_CamAcq::XferCallback(SapXferCallbackInfo *pInfo)
{
	VisInt_CamAcq  *pDalsaCam = (VisInt_CamAcq *)pInfo->GetContext();

	if (pInfo->IsTrash())
	{
		//AfxMessageBox(_T("���IsTrash!"));
		return;
	}
	else
	{
		//----------------�Բɼ�����ͼ����д���----------------------------------------------------
		pDalsaCam->m_View->Show();  //��ʾ

		byte *pData = NULL;    //1WORD=2byte      1byte=λ��8  1WORD=λ��16
		pDalsaCam->m_Buffers->GetAddress((void**)&pData);   //��ȡͼ������
		if (pData == NULL)
		{
			//AfxMessageBox(_T("������ݻ�ȡʧ�ܣ�"));
			return;
		}

		//-----------------------��ͼ---------------------------------------------------------------
		pDalsaCam->iImgAcqIndex++;
		char ch_sf[20];
		itoa(pDalsaCam->iImgAcqIndex, ch_sf, 10);
		string s_status;
		s_status = s_status + "���ڲɼ���" + ch_sf + "��ͼ";

		//������������ʾ��С��ǩ�����ݵģ�����Ҫ
		//QString C_Status;
		//C_Status = s_status.c_str();
		//pDalsaCam->m_Status.SetWindowTextA(C_Status);
		//-----------------------��ͼ---------------------------------------------------------------

		//------------------------��ͼ--------------------------------------------------------------
		string strSaveImageTempPath = pDalsaCam->strSaveImagePath + ch_sf + ".bmp";
		pDalsaCam->m_Buffers->Save(strSaveImageTempPath.c_str(), "-format bmp", pDalsaCam->m_Buffers->GetIndex(), pDalsaCam->m_Buffers->GetCount());

		//if (pDalsaCam->bContinueSaveImage)//������ͼΪ��
		//{
		//	pDalsaCam->m_Buffers->Save(strSaveImageTempPath.c_str(), "-format bmp", pDalsaCam->m_Buffers->GetIndex(), pDalsaCam->m_Buffers->GetCount());
		//}

		//if (pDalsaCam->bSnapImage)//���Ŵ�ͼ
		//{
		//	pDalsaCam->m_Buffers->Save(strSaveImageTempPath.c_str(), "-format bmp", pDalsaCam->m_Buffers->GetIndex(), pDalsaCam->m_Buffers->GetCount());
		//	pDalsaCam->bSnapImage = false;
		//}
		//------------------------��ͼ--------------------------------------------------------------

		pData = NULL;

	}//else
}

BOOL VisInt_CamAcq::LQ_CreateObjects()
{
	// Create acquisition object
	if (m_AcqDevice && !*m_AcqDevice && !m_AcqDevice->Create())
	{
		LQ_DestroyObjects();
		return FALSE;
	}

	// Create buffer object
	if (m_Buffers && !*m_Buffers)
	{
		if (!m_Buffers->Create())
		{
			LQ_DestroyObjects();
			return FALSE;
		}
		// Clear all buffers
		m_Buffers->Clear();
	}

	// Create view object
	if (m_View && !*m_View && !m_View->Create())
	{
		LQ_DestroyObjects();
		return FALSE;
	}

	// Set next empty with trash cycle mode for transfer
	if (m_Xfer && m_Xfer->GetPair(0))
	{
		if (!m_Xfer->GetPair(0)->SetCycleMode(SapXferPair::CycleNextWithTrash))
		{
			LQ_DestroyObjects();
			return FALSE;
		}
	}

	// Create transfer object
	if (m_Xfer && !*m_Xfer && !m_Xfer->Create())
	{
		LQ_DestroyObjects();
		return FALSE;
	}

	return TRUE;
}

//ע������
BOOL VisInt_CamAcq::LQ_DestroyObjects()
{
	// Destroy transfer object
	if (m_Xfer && *m_Xfer) m_Xfer->Destroy();

	// Destroy view object
	if (m_View && *m_View) m_View->Destroy();

	// Destroy buffer object
	if (m_Buffers && *m_Buffers) m_Buffers->Destroy();

	// Destroy acquisition object
	if (m_AcqDevice && *m_AcqDevice) m_AcqDevice->Destroy();

	return TRUE;
}



