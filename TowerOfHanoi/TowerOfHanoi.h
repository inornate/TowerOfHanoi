
// TowerOfHanoi.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTowerOfHanoiApp:
// �� Ŭ������ ������ ���ؼ��� TowerOfHanoi.cpp�� �����Ͻʽÿ�.
//

class CTowerOfHanoiApp : public CWinApp
{
public:
	CTowerOfHanoiApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTowerOfHanoiApp theApp;