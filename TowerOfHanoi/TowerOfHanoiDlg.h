
// TowerOfHanoiDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"

#include "Hanoi.h"
#include "afxcmn.h"

// CTowerOfHanoiDlg 대화 상자
class CTowerOfHanoiDlg : public CDialogEx
{
// 생성입니다.
public:
	CTowerOfHanoiDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOWEROFHANOI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 하노이탑의 그림을 그릴 픽쳐 콘트롤
	CStatic mctrPictureHanoi;
	CDC * GetDC(void);

	// Hanoi 연산을 수행할 클래스
	Hanoi *mpHanoi;

	// 원판의 갯수를 갖는 Edit control의 UINT형 변수. 범위 1, 10	// 원판의 갯수를 갖는 Edit control의 UINT형 변수. 범위 1, 10
	UINT muiNumPlate;
	afx_msg void OnBnClickedButtonStart();
	// DebugPrint를 표시할 Edit control.	// DebugPrint를 표시할 Edit control.

	void DebugPrint(CString msg);
	// DebugPrint를 출력할 Edit control의 CString 변수
	CString mstrDebugPrint;
	afx_msg void OnDeltaposSpinNumplate(NMHDR *pNMHDR, LRESULT *pResult);
	// 원판의 갯수를 조절하는 스핀콘트롤
	CSpinButtonCtrl mctrSpinNumPlate;
	afx_msg void OnEnChangeEditNumplate();
};
