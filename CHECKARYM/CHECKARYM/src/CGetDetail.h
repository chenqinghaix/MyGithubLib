#pragma once

#include "CHECKARYMDlg.h"
// CCGetDetail �Ի���

class CCGetDetail : public CDialog
{
	DECLARE_DYNAMIC(CCGetDetail)

public:
	CCGetDetail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCGetDetail();

// �Ի�������
	enum { IDD = IDD_GETDETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()	
	BOOL OnInitDialog();
public:
	afx_msg void OnBnAddMsg();
	DataStruct m_AddMsg;
};
