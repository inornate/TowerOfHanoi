
// TowerOfHanoiDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"

#include "Hanoi.h"
#include "afxcmn.h"

// CTowerOfHanoiDlg ��ȭ ����
class CTowerOfHanoiDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CTowerOfHanoiDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOWEROFHANOI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �ϳ���ž�� �׸��� �׸� ���� ��Ʈ��
	CStatic mctrPictureHanoi;
	CDC * GetDC(void);

	// Hanoi ������ ������ Ŭ����
	Hanoi *mpHanoi;

	// ������ ������ ���� Edit control�� UINT�� ����. ���� 1, 10	// ������ ������ ���� Edit control�� UINT�� ����. ���� 1, 10
	UINT muiNumPlate;
	afx_msg void OnBnClickedButtonStart();
	// DebugPrint�� ǥ���� Edit control.	// DebugPrint�� ǥ���� Edit control.

	void DebugPrint(CString msg);
	// DebugPrint�� ����� Edit control�� CString ����
	CString mstrDebugPrint;
	afx_msg void OnDeltaposSpinNumplate(NMHDR *pNMHDR, LRESULT *pResult);
	// ������ ������ �����ϴ� ������Ʈ��
	CSpinButtonCtrl mctrSpinNumPlate;
	afx_msg void OnEnChangeEditNumplate();
};
