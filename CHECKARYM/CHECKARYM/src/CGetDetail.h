#pragma once

#include "CHECKARYMDlg.h"
// CCGetDetail 对话框

class CCGetDetail : public CDialog
{
	DECLARE_DYNAMIC(CCGetDetail)

public:
	CCGetDetail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCGetDetail();

// 对话框数据
	enum { IDD = IDD_GETDETAIL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()	
	BOOL OnInitDialog();
public:
	afx_msg void OnBnAddMsg();
	DataStruct m_AddMsg;
};
