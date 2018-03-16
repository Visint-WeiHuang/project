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


//-------槽函数------

//--------初始化相机控件-------
void VisInt_CamAcq::OnBnClickedInitcamButton()
{
	OnInitCamera();
}


//------连接相机控件-----------
void VisInt_CamAcq::OnBnClickedConnectcamButton()
{
	LQ_ConnectCamera();
}

//------设置相机参数-----------
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

//连接相机,实质是申请底层的内存，建立内存之间的连接
bool VisInt_CamAcq::LQ_ConnectCamera()
{
	bool b = LQ_CreateObjects();//创建对象//连接相机

	QMessageBox *MesDlg = new QMessageBox;
	//MesDlg->resize(300, 300);
	//MesDlg->setFixedSize(500, 200);
	MesDlg->setAttribute(Qt::WA_DeleteOnClose);
	MesDlg->setWindowTitle(QStringLiteral("连接相机"));
	if (b)
	{
		MesDlg->setText(QStringLiteral("成功连接！"));
		return true;
	}
	else
	{
		MesDlg->setText(QStringLiteral("连接失败！"));
		return false;
	}

}

//初始化相机
bool VisInt_CamAcq::OnInitCamera()
{

	//------------------初始化变量----------------------------------
	m_strServerName = "";
	m_iServerIndex = 0;
	//C_ExposureTime = "";                           //曝光时间
	//C_Gain = "";                                   //增益
	dExposureTime = 0;
	dGain = 0;
	iImgAcqIndex = 0;                              //图像采集序号
	strConfigFileNamePath = "C:\\Users\\Lenovo\\Desktop\\T_Linea_M2048-7um_Default_Default.ccf";//配置文件路径
	strSaveImagePath = "C:\\Users\\Lenovo\\Desktop\\image\\";   //设置存图路径
	bContinueSaveImage = false;                    //连续存图布尔变量
	bSnapImage = false;                            //单张存图布尔变量
	//------------------初始化变量----------------------------------
	QMessageBox *MesDlg = new QMessageBox;
	//MesDlg->resize(300, 300);
	//MesDlg->setFixedSize(500, 200);
	MesDlg->setAttribute(Qt::WA_DeleteOnClose);
	MesDlg->setWindowTitle(QStringLiteral("初始化相机!"));
	

	/*获取服务器名字*/
	char chServerName[128];//"Linea_M4096-7um_1"

	if (SapManager::GetServerName(1, chServerName, sizeof(chServerName)))
	{
		m_strServerName = string(chServerName);
		m_iServerIndex = 0;
		SapLocation location(m_strServerName.c_str(), m_iServerIndex);
		m_ServerLocation = location;
		m_AcqDevice = new SapAcqDevice(m_ServerLocation, strConfigFileNamePath.c_str());
		m_Buffers = new SapBufferWithTrash(2, m_AcqDevice);
		m_View = new SapView(m_Buffers, SapHwndAutomatic); //这里是用来显示的，可以选择不要了
		m_Xfer = new SapAcqDeviceToBuf(m_AcqDevice, m_Buffers, XferCallback, this);//设置回调函数	

		//只是为了提醒
		MesDlg->setText(QStringLiteral("初始化成功！"));
		MesDlg->show();
		return true;
	}
	else
	{
		MesDlg->setText(QStringLiteral("初始化失败！"));
		MesDlg->show();
		return false;
	}

}

void VisInt_CamAcq::XferCallback(SapXferCallbackInfo *pInfo)
{
	VisInt_CamAcq  *pDalsaCam = (VisInt_CamAcq *)pInfo->GetContext();

	if (pInfo->IsTrash())
	{
		//AfxMessageBox(_T("相机IsTrash!"));
		return;
	}
	else
	{
		//----------------对采集到的图像进行处理----------------------------------------------------
		pDalsaCam->m_View->Show();  //显示

		byte *pData = NULL;    //1WORD=2byte      1byte=位深8  1WORD=位深16
		pDalsaCam->m_Buffers->GetAddress((void**)&pData);   //获取图像数据
		if (pData == NULL)
		{
			//AfxMessageBox(_T("相机数据获取失败！"));
			return;
		}

		//-----------------------采图---------------------------------------------------------------
		pDalsaCam->iImgAcqIndex++;
		char ch_sf[20];
		itoa(pDalsaCam->iImgAcqIndex, ch_sf, 10);
		string s_status;
		s_status = s_status + "正在采集第" + ch_sf + "张图";

		//这是是设置显示的小标签的内容的，不需要
		//QString C_Status;
		//C_Status = s_status.c_str();
		//pDalsaCam->m_Status.SetWindowTextA(C_Status);
		//-----------------------采图---------------------------------------------------------------

		//------------------------存图--------------------------------------------------------------
		string strSaveImageTempPath = pDalsaCam->strSaveImagePath + ch_sf + ".bmp";
		pDalsaCam->m_Buffers->Save(strSaveImageTempPath.c_str(), "-format bmp", pDalsaCam->m_Buffers->GetIndex(), pDalsaCam->m_Buffers->GetCount());

		//if (pDalsaCam->bContinueSaveImage)//连续存图为真
		//{
		//	pDalsaCam->m_Buffers->Save(strSaveImageTempPath.c_str(), "-format bmp", pDalsaCam->m_Buffers->GetIndex(), pDalsaCam->m_Buffers->GetCount());
		//}

		//if (pDalsaCam->bSnapImage)//单张存图
		//{
		//	pDalsaCam->m_Buffers->Save(strSaveImageTempPath.c_str(), "-format bmp", pDalsaCam->m_Buffers->GetIndex(), pDalsaCam->m_Buffers->GetCount());
		//	pDalsaCam->bSnapImage = false;
		//}
		//------------------------存图--------------------------------------------------------------

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

//注销对象
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



