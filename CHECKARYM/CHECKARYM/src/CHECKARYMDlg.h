
// CHECKARYMDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

typedef struct _DataStruct
{
	char acName[64];
	char acAcronym[32];
	char acFullName[64];
	char acRemark[512];
	char cFlag;        //是否被匹配标志
}DataStruct;

// CCHECKARYMDlg 对话框
class CCHECKARYMDlg : public CDialog
{
// 构造
public:
	CCHECKARYMDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHECKARYM_DIALOG };
	virtual ~CCHECKARYMDlg();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持	

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_InputType;
	CListCtrl m_DataList;
	DataStruct *m_pData;
	int m_DataListCnt;
	void InitData();
	void InitList();
	afx_msg void OnBnAddMsg();
	afx_msg void OnEnHitWord();
	void FlashListForHit();
};
