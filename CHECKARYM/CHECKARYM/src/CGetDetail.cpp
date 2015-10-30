// E:\gitlib\MyLib\CHECKARYM\CHECKARYM\src\CGetDetail.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CHECKARYM.h"
#include "CGetDetail.h"


// CCGetDetail �Ի���

IMPLEMENT_DYNAMIC(CCGetDetail, CDialog)

CCGetDetail::CCGetDetail(CWnd* pParent /*=NULL*/)
	: CDialog(CCGetDetail::IDD, pParent)
{
	memset(&m_AddMsg, 0x00, sizeof(m_AddMsg));
}

CCGetDetail::~CCGetDetail()
{
}

void CCGetDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCGetDetail, CDialog)
	ON_BN_CLICKED(IDOK, &CCGetDetail::OnBnAddMsg)
END_MESSAGE_MAP()


// CCGetDetail ��Ϣ�������
BOOL CCGetDetail::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_NAME)->SetWindowText(m_AddMsg.acName);
	GetDlgItem(IDC_ARYM)->SetWindowText(m_AddMsg.acAcronym);
	GetDlgItem(IDC_FULLNAME)->SetWindowText(m_AddMsg.acFullName);
	GetDlgItem(IDC_REMARK)->SetWindowText(m_AddMsg.acRemark);

	SetWindowText("�������Ŀ");

	return TRUE;
}
void CCGetDetail::OnBnAddMsg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_NAME)->GetWindowText(m_AddMsg.acName, sizeof(m_AddMsg.acName));
	GetDlgItem(IDC_ARYM)->GetWindowText(m_AddMsg.acAcronym, sizeof(m_AddMsg.acAcronym));
	GetDlgItem(IDC_FULLNAME)->GetWindowText(m_AddMsg.acFullName, sizeof(m_AddMsg.acFullName));
	GetDlgItem(IDC_REMARK)->GetWindowText(m_AddMsg.acRemark, sizeof(m_AddMsg.acRemark));

	if(strlen(m_AddMsg.acName) == 0)
	{
		MessageBox("���Ʋ���Ϊ��!");
		return;
	}

	if(strlen(m_AddMsg.acAcronym) == 0)
	{
		MessageBox("���Դʲ���Ϊ��!");
		return;
	}

	if(strlen(m_AddMsg.acFullName) == 0)
	{
		MessageBox("ȫ�Ʋ���Ϊ��!");
		return;
	}

	OnOK();
}
