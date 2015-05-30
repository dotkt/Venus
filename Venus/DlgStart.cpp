// DlgStart.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Venus.h"
#include "DlgStart.h"
#include "afxdialogex.h"
#include "About.h"
#include "resource.h"


// CDlgStart �Ի���

IMPLEMENT_DYNAMIC(CDlgStart, CDialogEx)

CDlgStart::CDlgStart(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgStart::IDD, pParent)
{

}

CDlgStart::~CDlgStart()
{
}

void CDlgStart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgStart, CDialogEx)
	ON_MESSAGE ( WM_HOTKEY, OnHotKey )
	ON_MESSAGE ( WM_SHOW_TASK, OnShowTask )
	ON_WM_SYSCOMMAND()
	ON_COMMAND(ID_32771, &CDlgStart::On32771)
	ON_COMMAND(ID_32772, &CDlgStart::On32772)
END_MESSAGE_MAP()


// CDlgStart ��Ϣ�������


BOOL CDlgStart::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	pDlg = new CVenusDlg(this);
	pDlg->Create(IDD_VENUS_DIALOG);
	pDlg->SetShowStatus(false);

	// ע���ȼ�
	UINT iHotKey = VK_SPACE;
#ifdef _DEBUG
	iHotKey = VK_F1;
#endif
	if (FALSE == ::RegisterHotKey(this->GetSafeHwnd(), ID_OPEN_USER_DLG, MOD_ALT, iHotKey))
	{
		MessageBoxA("ע��Alt+Space�ȼ�ʧ�ܣ����ܱ���������ռ�ã����顣", "������", MB_ICONWARNING);
	}

	// ����ʱ����ʾ����
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);  //����������ȥ��

	// ��ʾ����ͼ��
	ShowSys2Task();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


LRESULT CDlgStart::OnHotKey ( WPARAM wPARAM, LPARAM lPARAM )
{
	if (wPARAM == ID_OPEN_USER_DLG)
	{
		if ( !pDlg->GetShowStatus() )
		{
			pDlg->SetShowStatus(true);

			// ʹ�´��ڻ�ȡϵͳ����
			typedef void (WINAPI *PSWITCHTOTHISWINDOW) (HWND,BOOL);
			PSWITCHTOTHISWINDOW SwitchToThisWindow;
			HMODULE hUser32=GetModuleHandle(_T("user32"));
			SwitchToThisWindow=(PSWITCHTOTHISWINDOW)GetProcAddress(hUser32,"SwitchToThisWindow");
			SwitchToThisWindow(pDlg->GetSafeHwnd(), TRUE);
		}
		else
		{
			pDlg->SetShowStatus(false);
		}
	}
	return 0;
}

LRESULT CDlgStart::OnShowTask(WPARAM wParam, LPARAM lParam)   
{   
	if(wParam != IDR_MAINFRAME)   
		return 1;
	if(WM_LBUTTONDBLCLK == lParam)  
	{
		CAbout about;
		about.DoModal();
	}
	if (WM_RBUTTONDOWN == lParam)
	{
		LPPOINT point=new tagPOINT; 
		::GetCursorPos(point);     //�õ����λ��

		CMenu menu;
		menu.LoadMenu(IDR_MENU1);//���ز˵���Դ

		CMenu *pPopup = menu.GetSubMenu(0);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point->x,point->y,this);

		delete point;
	}
	return 0;
}

// ����ϵͳ����
void CDlgStart::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (nID == SC_CLOSE) // �رմ���
	{
		NOTIFYICONDATA nd;
		nd.cbSize    = sizeof (NOTIFYICONDATA);
		nd.hWnd    = this->m_hWnd;
		nd.uID   =   IDR_MAINFRAME;
		Shell_NotifyIcon(NIM_DELETE, &nd);    // ����ͼ�겻��ʾ
	}

	CDialogEx::OnSysCommand(nID, lParam);
}

void CDlgStart::ShowSys2Task()
{
	NOTIFYICONDATA nid; 
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd = this->m_hWnd; 
	nid.uID = IDR_MAINFRAME; 
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP ; 
	nid.uCallbackMessage = WM_SHOW_TASK;        // �Զ������Ϣ���� 
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy_s(nid.szTip, "������");              // ��Ϣ��ʾ��
	Shell_NotifyIcon(NIM_ADD, &nid);            // �����������ͼ�� 
}

void CDlgStart::On32771()
{
	// TODO: �ڴ���������������
	CAbout about;
	about.DoModal();
}

void CDlgStart::On32772()
{
	// TODO: �ڴ���������������
	//this->DestroyWindow();
	this->OnOK();
}
