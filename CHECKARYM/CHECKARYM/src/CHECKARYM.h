
// CHECKARYM.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCHECKARYMApp:
// �йش����ʵ�֣������ CHECKARYM.cpp
//

class CCHECKARYMApp : public CWinAppEx
{
public:
	CCHECKARYMApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCHECKARYMApp theApp;