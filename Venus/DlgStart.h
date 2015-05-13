#pragma once

#include "VenusDlg.h"

#define WM_SHOW_TASK      WM_USER+101
#define ID_OPEN_USER_DLG  WM_USER+102

// CDlgStart �Ի���

class CDlgStart : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStart)

public:
	CDlgStart(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStart();

// �Ի�������
	enum { IDD = IDD_DLGSTART };

private:
	// �������봰��
	CVenusDlg *pDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnHotKey ( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnShowTask ( WPARAM wParam, LPARAM lParam );
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	void ShowSys2Task();
	afx_msg void OnBnClicked1();
	afx_msg void On32771();
	afx_msg void On32772();
};
