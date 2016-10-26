
// VenusDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Venus.h"
#include "VenusDlg.h"
#include "afxdialogex.h"
#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CVenusDlg �Ի���

CVenusDlg::CVenusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVenusDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	IDC_MYINFOTEXT = 0;
}
CVenusDlg::~CVenusDlg()
{
	delete myIndex;
}

void CVenusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVenusDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_EN_CHANGE(IDC_EDIT1, &CVenusDlg::OnChangeEdit1)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CVenusDlg ��Ϣ�������

bool CVenusDlg::GetShowStatus()
{
	return this->curStatus;
}

void CVenusDlg::SetShowStatus(bool status)
{
	if (status)
	{
		myIndex->InitIndex();
		this->ShowWindow(SW_SHOWNORMAL);
	}
	else
	{
		this->ShowWindow(SW_HIDE);
	}
	this->curStatus = status;
}

void CVenusDlg::RunLnkFile(LPSTR path)
{
	//WinExec(exePath, SW_SHOWNORMAL);
	//ShellExecute(NULL, "open", path, NULL, NULL, SW_SHOWNORMAL);   // hack: ��open��������ڴ��޷��ͷţ�
	ShellExecute(NULL, NULL, path, NULL, NULL, SW_SHOWNORMAL);
}

BOOL CVenusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	IDC_MYINFOTEXT = 63301;
	myIndex = new LocalPath();
	lastKey = "";
	lastInfoSize = 0;
	curStatus = false;

	// ���ô���λ��
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);  //����������ȥ��
	SetWindowPos(NULL, 5, 5, 600, 300, 0);

	// ����͸��
	SetBackgroundColor(RGB(1,11,21));
	LONG ExtendedStyle = GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE );
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,ExtendedStyle | WS_EX_LAYERED );
	::SetLayeredWindowAttributes(GetSafeHwnd(),RGB(1,11,21),0,LWA_COLORKEY);

	// ����������С
	editFont.CreatePointFont(240,"����");
	CEdit *myInput = (CEdit *)GetDlgItem(IDC_EDIT1);
	myInput->SetFont(&editFont);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVenusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVenusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// ���ذ����¼�
void CVenusDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CVenusDlg::OnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// ����֮ǰ���
	lastKey = "";
	for (int i=0; i<lastInfoSize; ++i)
	{
		myInfoLabel[i]->DestroyWindow();
		delete myInfoLabel[i];
	}
	
	CString txt;
	GetDlgItemText(IDC_EDIT1, txt);

	vector<CString> keyMatch;
	myIndex->FindIndex(txt, keyMatch);

	// �����ǩ��ÿ���ַ��Ĵ�С
	int labelWidth = 26;
	int labelHeight = 50;

	int rect_left = 10;
	int rect_top = 50;

	for (int i=0; i < keyMatch.size(); i++)
	{
		if (i == 0)
		{
			lastKey = keyMatch[i];
		}
		if (i >= 50)
		{
			break;
		}
		CRect rect;
		rect.left = rect_left;
		int clen = keyMatch[i].GetLength();
		rect.right = rect_left + clen * labelWidth;  // ������̬�������
		rect.top = rect_top + i * labelHeight;
		rect.bottom = rect_top + labelHeight * 0.8 + i * labelHeight;

		myInfoLabel[i] = new CLabel();
		myInfoLabel[i]->Create(keyMatch[i], WS_VISIBLE, rect, this, IDC_MYINFOTEXT+i);
		myInfoLabel[i]->SetTextColor(RGB(255, 255, 255));
		myInfoLabel[i]->SetFontName("Courier New");
		myInfoLabel[i]->SetFontSize(labelWidth-1);
		myInfoLabel[i]->SetFontBold(TRUE);
		myInfoLabel[i]->SetBkColor(RGB(10, 136, 255));
		//myInfoLabel[i]->SetTransparent(TRUE);
	}

	lastInfoSize = keyMatch.size() > 50 ? 50: keyMatch.size();
	SetWindowPos(NULL, 5, 5, 600, rect_top + (keyMatch.size()+1)*labelHeight, 0);
	//_CrtDumpMemoryLeaks();  // ����ڴ�
}


BOOL CVenusDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->wParam==VK_RETURN || pMsg->wParam==VK_ESCAPE)
	{
		// ���ش���
		SetShowStatus(false);

		CString txt;
		GetDlgItemText(IDC_EDIT1, txt);

		if (pMsg->wParam == VK_RETURN)
		{
			// ctrl + enter �ٶ���������Ĺؼ���
			if (GetAsyncKeyState(VK_CONTROL)<0)
			{
				CString url;
				url.Format("www.baidu.com/s?wd=%s", txt);
				ShellExecute(NULL, _T("open"), _T(url), NULL, NULL, SW_SHOWNORMAL);
			}
			// shift + enter ��ѯDICT�ֵ�
			else if (GetAsyncKeyState(VK_SHIFT)<0)
			{
				CString url;
				url.Format("dict.cn/%s", txt);
				ShellExecute(NULL, _T("open"), _T(url), NULL, NULL, SW_SHOWNORMAL);
			}
			// ���س�ʱִ�е�ǰƥ�䵽��ݳ���
			else
			{
				if (!lastKey.IsEmpty())
				{
					CString exePath = myIndex->GetLocalPath(lastKey);
					if (lastKey == ";lnk")
					{
						system(exePath);
					}
					else
					{
						RunLnkFile((LPSTR)(LPCSTR)exePath);
					}
				}

			}
		}

		// �����������
		CEdit *myInput = (CEdit *)GetDlgItem(IDC_EDIT1);
		myInput->SetSel(0, -1);
		myInput->Clear();

		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CVenusDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// �ı�༭��������ɫ
	if (pWnd->GetDlgCtrlID() == IDC_EDIT1)
	{
		pDC->SetTextColor(RGB(248, 252, 255));
		pDC->SetBkColor(RGB(15, 15, 15));
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
