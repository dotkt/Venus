#pragma once


// CAbout �Ի���

class CAbout : public CDialog
{
	DECLARE_DYNAMIC(CAbout)

public:
	CAbout(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAbout();

// �Ի�������
	enum { IDD = IDD_ABOUT };

private:
	// ע������������
	HKEY hKey;
	CString strRegPath, strMyKey;
	CButton* m_button;
	bool OpenRegeditRun();
	void CloseRegeditRun();
	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck1();
	virtual BOOL OnInitDialog();
};
