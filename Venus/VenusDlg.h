
// VenusDlg.h : ͷ�ļ�
//

#pragma once
#include <Windows.h>
#include "Label.h"
#include "LocalPath.h"

// CVenusDlg �Ի���
class CVenusDlg : public CDialogEx
{
// ����
public:
	CVenusDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CVenusDlg();

// �Ի�������
	enum { IDD = IDD_VENUS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	LocalPath *myIndex;
	CLabel *myInfoLabel[50];
	CFont editFont;
	CString lastKey;
	int lastInfoSize;
	bool curStatus;

public:
	bool GetShowStatus();
	void SetShowStatus(bool status);
	void RunLnkFile(LPSTR path);


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChangeEdit1();
	int IDC_MYINFOTEXT;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
