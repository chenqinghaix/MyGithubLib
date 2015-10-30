
// CHECKARYMDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

typedef struct _DataStruct
{
	char acName[64];
	char acAcronym[32];
	char acFullName[64];
	char acRemark[512];
	char cFlag;        //�Ƿ�ƥ���־
}DataStruct;

// CCHECKARYMDlg �Ի���
class CCHECKARYMDlg : public CDialog
{
// ����
public:
	CCHECKARYMDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHECKARYM_DIALOG };
	virtual ~CCHECKARYMDlg();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��	

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
