// About.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Venus.h"
#include "About.h"
#include "afxdialogex.h"


// CAbout �Ի���

IMPLEMENT_DYNAMIC(CAbout, CDialog)

CAbout::CAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CAbout::IDD, pParent)
{
}

CAbout::~CAbout()
{
}

void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAbout, CDialog)
	ON_BN_CLICKED(IDC_CHECK1, &CAbout::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &CAbout::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAbout ��Ϣ�������


// ��ע���������
bool CAbout::OpenRegeditRun()
{
	if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// �ر�ע���
void CAbout::CloseRegeditRun()
{
	RegCloseKey(hKey);
}


void CAbout::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_button->GetCheck())
	{
		if (OpenRegeditRun())
		{
			TCHAR szModule[MAX_PATH];
			GetModuleFileName(NULL, szModule, MAX_PATH);//�õ������������ȫ·��  

			RegSetValueEx(hKey, strMyKey, 0, REG_SZ, (LPBYTE)szModule, (lstrlen(szModule) + 1)*sizeof(TCHAR));

			CloseRegeditRun();
		}
		else
		{
			AfxMessageBox(_T("ϵͳ��������,������ϵͳ����"));
		}
	}
	else
	{
		if (OpenRegeditRun())
		{
			RegDeleteValue(hKey, strMyKey);
			CloseRegeditRun();
		}
	}
}


BOOL CAbout::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// ��鵱ǰ�Ƿ�����������
	strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	strMyKey = "Venus";
	m_button = (CButton *)GetDlgItem(IDC_CHECK1);

	wchar_t strMyValue[MAX_PATH];
	unsigned long i,j;
	if (OpenRegeditRun())
	{
		// �������������Ƿ����и�����
		if (RegQueryValueEx(hKey, strMyKey, 0, &j, (LPBYTE)strMyValue, &i)==ERROR_SUCCESS)
		{
			m_button->SetCheck(1);
		}
		else
		{
			m_button->SetCheck(0);
		}
		CloseRegeditRun();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CAbout::OnBnClickedButton1()
{
	// �򿪰�װĿ¼
	char szFilePath[MAX_PATH + 1]={0};
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	(strrchr(szFilePath, '\\'))[0] = 0; // ɾ���ļ�����ֻ���·���ִ�
	char szOpera[MAX_PATH + 1] = "explorer /e \"";
	strcat_s(szOpera, szFilePath);
	strcat_s(szOpera, "\"");
	system(szOpera);
}
