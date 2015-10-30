
// CHECKARYMDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CHECKARYM.h"
#include "CHECKARYMDlg.h"
#include "CGetDetail.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define    INI_FILE_PATH   "./data.ini"
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCHECKARYMDlg 对话框




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


// CCHECKARYMDlg 消息处理程序

BOOL CCHECKARYMDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_InputType = 1;
	SetWindowText("缩略词查询v0.5");
	//对list进行初始化
	LONG lStyle; 
	lStyle = GetWindowLong(m_DataList.m_hWnd, GWL_STYLE);//获取当前窗口style 
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位 
	lStyle |= LVS_REPORT; //设置style 
	SetWindowLong(m_DataList.m_hWnd, GWL_STYLE, lStyle);//设置style 
	DWORD dwStyle = m_DataList.GetExtendedStyle(); 
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl） 
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl） 
	m_DataList.SetExtendedStyle(dwStyle); //设置扩展风格 

	m_DataList.InsertColumn( 0, "名称", LVCFMT_LEFT, 120 );//插入列 
	m_DataList.InsertColumn( 1, "缩略词", LVCFMT_LEFT, 80 );
	m_DataList.InsertColumn( 2, "全拼", LVCFMT_LEFT, 150);
	m_DataList.InsertColumn( 3, "备注", LVCFMT_LEFT, 400 );

	m_DataListCnt = 0;
	//将ini文件加载到list及内存
	InitData();

	InitList();

	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCHECKARYMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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

	//申请空间
	m_pData = (DataStruct *)malloc(sizeof(DataStruct)*m_DataListCnt);
	if(m_pData == NULL)
	{
		MessageBox("申请空间失败!");
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
	// TODO: 在此添加控件通知处理程序代码
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
				strMsg.Format("【%s】此缩略词已经存在\n名称为【%s】\n全拼为【%s】", m_pData[i].acAcronym, m_pData[i].acName, m_pData[i].acFullName);
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
			MessageBox("申请空间失败!");
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
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int i;
	char acHidWord[512];
	UpdateData(TRUE);

	memset(acHidWord, 0x00, sizeof(acHidWord));

	GetDlgItem(IDC_HITWORD)->GetWindowText(acHidWord, sizeof(acHidWord)-1);

	//如果输入框为空，则全显示
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
			MessageBox("选项有误!");
			return;
		}
		m_pData[i].cFlag = 1;
	}

	FlashListForHit();
}
