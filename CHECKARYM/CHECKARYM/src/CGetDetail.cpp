// E:\gitlib\MyLib\CHECKARYM\CHECKARYM\src\CGetDetail.cpp : 实现文件
//

#include "stdafx.h"
#include "CHECKARYM.h"
#include "CGetDetail.h"


// CCGetDetail 对话框

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


// CCGetDetail 消息处理程序
BOOL CCGetDetail::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_NAME)->SetWindowText(m_AddMsg.acName);
	GetDlgItem(IDC_ARYM)->SetWindowText(m_AddMsg.acAcronym);
	GetDlgItem(IDC_FULLNAME)->SetWindowText(m_AddMsg.acFullName);
	GetDlgItem(IDC_REMARK)->SetWindowText(m_AddMsg.acRemark);

	SetWindowText("添加新条目");

	return TRUE;
}
void CCGetDetail::OnBnAddMsg()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_NAME)->GetWindowText(m_AddMsg.acName, sizeof(m_AddMsg.acName));
	GetDlgItem(IDC_ARYM)->GetWindowText(m_AddMsg.acAcronym, sizeof(m_AddMsg.acAcronym));
	GetDlgItem(IDC_FULLNAME)->GetWindowText(m_AddMsg.acFullName, sizeof(m_AddMsg.acFullName));
	GetDlgItem(IDC_REMARK)->GetWindowText(m_AddMsg.acRemark, sizeof(m_AddMsg.acRemark));

	if(strlen(m_AddMsg.acName) == 0)
	{
		MessageBox("名称不可为空!");
		return;
	}

	if(strlen(m_AddMsg.acAcronym) == 0)
	{
		MessageBox("缩略词不可为空!");
		return;
	}

	if(strlen(m_AddMsg.acFullName) == 0)
	{
		MessageBox("全称不可为空!");
		return;
	}

	OnOK();
}
