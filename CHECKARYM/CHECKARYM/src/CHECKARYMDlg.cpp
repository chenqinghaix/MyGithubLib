
// CHECKARYMDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CHECKARYM.h"
#include "CHECKARYMDlg.h"
#include "CGetDetail.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define    INI_FILE_PATH   "./data.ini"
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCHECKARYMDlg �Ի���




CCHECKARYMDlg::CCHECKARYMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCHECKARYMDlg::IDD, pParent)
	, m_InputType(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pData = NULL;
}


CCHECKARYMDlg::~CCHECKARYMDlg()
{
	free(m_pData);
}

void CCHECKARYMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_InputType);
	DDX_Control(pDX, IDC_LIST1, m_DataList);
}

BEGIN_MESSAGE_MAP(CCHECKARYMDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CCHECKARYMDlg::OnBnAddMsg)
	ON_EN_CHANGE(IDC_EDIT2, &CCHECKARYMDlg::OnEnHitWord)
END_MESSAGE_MAP()


// CCHECKARYMDlg ��Ϣ�������

BOOL CCHECKARYMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_InputType = 1;
	SetWindowText("���Դʲ�ѯv0.5");
	//��list���г�ʼ��
	LONG lStyle; 
	lStyle = GetWindowLong(m_DataList.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style 
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ 
	lStyle |= LVS_REPORT; //����style 
	SetWindowLong(m_DataList.m_hWnd, GWL_STYLE, lStyle);//����style 
	DWORD dwStyle = m_DataList.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl�� 
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl�� 
	m_DataList.SetExtendedStyle(dwStyle); //������չ��� 

	m_DataList.InsertColumn( 0, "����", LVCFMT_LEFT, 120 );//������ 
	m_DataList.InsertColumn( 1, "���Դ�", LVCFMT_LEFT, 80 );
	m_DataList.InsertColumn( 2, "ȫƴ", LVCFMT_LEFT, 150);
	m_DataList.InsertColumn( 3, "��ע", LVCFMT_LEFT, 400 );

	m_DataListCnt = 0;
	//��ini�ļ����ص�list���ڴ�
	InitData();

	InitList();

	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCHECKARYMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCHECKARYMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCHECKARYMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCHECKARYMDlg::InitData()
{
	int  i = 0;
	char acName[10];

	m_DataListCnt = GetPrivateProfileInt( "CNT", "cnt", 0, INI_FILE_PATH);
	if(m_DataListCnt == 0)
	{
		return;
	}

	//����ռ�
	m_pData = (DataStruct *)malloc(sizeof(DataStruct)*m_DataListCnt);
	if(m_pData == NULL)
	{
		MessageBox("����ռ�ʧ��!");
		return;
	}

	memset(m_pData, 0x00, sizeof(DataStruct)*m_DataListCnt);

	for(i = 0; i < m_DataListCnt; i++)
	{
		sprintf(acName, "%d", i+1);
		GetPrivateProfileString(acName, "Name",	"",		m_pData[i].acName,	sizeof(m_pData[i].acName)-1,	INI_FILE_PATH);
		GetPrivateProfileString(acName, "Acronym",	"",	m_pData[i].acAcronym,	sizeof(m_pData[i].acAcronym)-1,	INI_FILE_PATH);
		GetPrivateProfileString(acName, "FullName",	"",		m_pData[i].acFullName,	sizeof(m_pData[i].acFullName)-1,	INI_FILE_PATH);
		GetPrivateProfileString(acName, "remark",	"",		m_pData[i].acRemark,	sizeof(m_pData[i].acRemark)-1,	INI_FILE_PATH);
	}
}

void CCHECKARYMDlg::InitList()
{
	int i = 0;
	int j = 0;
	int nRow = 0;
	m_DataList.DeleteAllItems();

	for ( i = 0; i < m_DataListCnt; i++ )
	{
		j = 1;
		nRow = m_DataList.InsertItem( i,m_pData[i].acName);
		m_DataList.SetItemText( nRow, j++,  m_pData[i].acAcronym );
		m_DataList.SetItemText( nRow, j++,  m_pData[i].acFullName );
		m_DataList.SetItemText( nRow, j++,  m_pData[i].acRemark );
	}
}




void CCHECKARYMDlg::OnBnAddMsg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//OnOK();
	CCGetDetail GetDetail;
	int         i,j;
	CString strMsg;
	CString strName;
	DataStruct *pStructTmp = NULL;

	while(1)
	{
		if(GetDetail.DoModal() != IDOK)
		{
			break;
		}
		
		for(i = 0; i < m_DataListCnt; i++)
		{
			if(strcmp(GetDetail.m_AddMsg.acAcronym, m_pData[i].acAcronym) == 0)
			{
				strMsg.Format("��%s�������Դ��Ѿ�����\n����Ϊ��%s��\nȫƴΪ��%s��", m_pData[i].acAcronym, m_pData[i].acName, m_pData[i].acFullName);
				MessageBox(strMsg);
				break;
			}
		}

		if(i != m_DataListCnt)
		{
			continue;
		}

		m_DataListCnt++;
		strMsg.Format("%d", m_DataListCnt);
		strName.Format("%d", m_DataListCnt);
		WritePrivateProfileString("CNT", "cnt",	strMsg.GetBuffer(),INI_FILE_PATH);
		WritePrivateProfileString(strName.GetBuffer(), "Name",	GetDetail.m_AddMsg.acName,	INI_FILE_PATH);
		WritePrivateProfileString(strName.GetBuffer(), "Acronym",GetDetail.m_AddMsg.acAcronym,	INI_FILE_PATH);
		WritePrivateProfileString(strName.GetBuffer(), "FullName",	GetDetail.m_AddMsg.acFullName,INI_FILE_PATH);
		WritePrivateProfileString(strName.GetBuffer(), "remark",	GetDetail.m_AddMsg.acRemark,	INI_FILE_PATH);

		pStructTmp = (DataStruct *)malloc(sizeof(DataStruct)*m_DataListCnt);
		if(pStructTmp == NULL)
		{
			MessageBox("����ռ�ʧ��!");
			break;
		}

		memcpy(pStructTmp, m_pData, sizeof(DataStruct)*(m_DataListCnt-1));

		memcpy(&pStructTmp[m_DataListCnt-1], &GetDetail.m_AddMsg, sizeof(DataStruct));

		free(m_pData);

		m_pData = pStructTmp;

		int nRow;
		j = 1;
		nRow = m_DataList.InsertItem( m_DataListCnt-1,m_pData[m_DataListCnt-1].acName);
		m_DataList.SetItemText( nRow, j++,  m_pData[m_DataListCnt-1].acAcronym );
		m_DataList.SetItemText( nRow, j++,  m_pData[m_DataListCnt-1].acFullName );
		m_DataList.SetItemText( nRow, j++,  m_pData[m_DataListCnt-1].acRemark );

		break;
	}
}

void CCHECKARYMDlg::FlashListForHit()
{
	int i = 0, j, k = 0;
	
	m_DataList.DeleteAllItems();

	for(i = 0; i < m_DataListCnt; i++)
	{
		if(m_pData[i].cFlag == 0)
		{
			continue;
		}

		int nRow;
		j = 1;
		nRow = m_DataList.InsertItem(k ,m_pData[i].acName);
		m_DataList.SetItemText( nRow, j++,  m_pData[i].acAcronym );
		m_DataList.SetItemText( nRow, j++,  m_pData[i].acFullName );
		m_DataList.SetItemText( nRow, j++,  m_pData[i].acRemark );
		k++;
	}
}

void CCHECKARYMDlg::OnEnHitWord()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int i;
	char acHidWord[512];
	UpdateData(TRUE);

	memset(acHidWord, 0x00, sizeof(acHidWord));

	GetDlgItem(IDC_HITWORD)->GetWindowText(acHidWord, sizeof(acHidWord)-1);

	//��������Ϊ�գ���ȫ��ʾ
	if(strlen(acHidWord) == 0)
	{
		InitList();
		return;
	}

	for(i = 0; i < m_DataListCnt; i++)
	{
		switch(m_InputType)
		{
		case 0:
			if(strstr(m_pData[i].acName, acHidWord) == NULL)
			{
				m_pData[i].cFlag = 0;
				continue;
			}
			break;
		case 1:
			if(strstr(m_pData[i].acAcronym, acHidWord) == NULL)
			{
				m_pData[i].cFlag = 0;
				continue;
			}
			break;
		case 2:
			if(strstr(m_pData[i].acFullName, acHidWord) == NULL)
			{
				m_pData[i].cFlag = 0;
				continue;
			}
			break;
		default:
			MessageBox("ѡ������!");
			return;
		}
		m_pData[i].cFlag = 1;
	}

	FlashListForHit();
}
