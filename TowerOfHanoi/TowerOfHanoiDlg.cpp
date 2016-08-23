
// TowerOfHanoiDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TowerOfHanoi.h"
#include "TowerOfHanoiDlg.h"
#include "afxdialogex.h"

#include "hanoi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTowerOfHanoiDlg 대화 상자

CTowerOfHanoiDlg::CTowerOfHanoiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TOWEROFHANOI_DIALOG, pParent)
	, muiNumPlate(0)
	, mstrDebugPrint(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// 원판갯수를 가지고 있는 콘트롤의 초기값 설정.
	mpHanoi = NULL;
	muiNumPlate = 3;	// 초기값 3.
}

void CTowerOfHanoiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_HANOI, mctrPictureHanoi);
	DDX_Text(pDX, IDC_EDIT_NUMPLATE, muiNumPlate);
	DDV_MinMaxUInt(pDX, muiNumPlate, 1, 10);
	DDX_Text(pDX, IDC_EDIT_DEBUGPRINT, mstrDebugPrint);
	DDX_Control(pDX, IDC_SPIN_NUMPLATE, mctrSpinNumPlate);
}

BEGIN_MESSAGE_MAP(CTowerOfHanoiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CTowerOfHanoiDlg::OnBnClickedButtonStart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_NUMPLATE, &CTowerOfHanoiDlg::OnDeltaposSpinNumplate)
	ON_EN_CHANGE(IDC_EDIT_NUMPLATE, &CTowerOfHanoiDlg::OnEnChangeEditNumplate)
END_MESSAGE_MAP()


// CTowerOfHanoiDlg 메시지 처리기

BOOL CTowerOfHanoiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	mctrSpinNumPlate.SetRange(1, 10);
	mpHanoi = new Hanoi(muiNumPlate, (void *)this);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTowerOfHanoiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTowerOfHanoiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		UINT index;
		CDC *pDC = mctrPictureHanoi.GetWindowDC();
		CRect rect;

		GetClientRect(&rect);
		pDC->FillSolidRect(rect, RGB(255, 255, 255));	

		mpHanoi->DrawPeg(pDC);

		UpdateData(TRUE);
		if (muiNumPlate != mpHanoi->mNumPlates)
		{			
			mstrDebugPrint = _T("");
			mpHanoi->InitPlateStatus(muiNumPlate);
		}
		UpdateData(FALSE);

		for (index = 0; index < muiNumPlate; index++)
			mpHanoi->DrawPlate(pDC, index);
		mctrPictureHanoi.ReleaseDC(pDC);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTowerOfHanoiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTowerOfHanoiDlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	mpHanoi->DoHanoi();
}


void CTowerOfHanoiDlg::DebugPrint(CString msg)
{
	UpdateData(TRUE);
	mstrDebugPrint += msg;
	UpdateData(FALSE);
}

CDC * CTowerOfHanoiDlg::GetDC(void)
{
	return mctrPictureHanoi.GetWindowDC();
}

void CTowerOfHanoiDlg::OnDeltaposSpinNumplate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void CTowerOfHanoiDlg::OnEnChangeEditNumplate()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Invalidate();
}
