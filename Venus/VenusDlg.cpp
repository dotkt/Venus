
// VenusDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Venus.h"
#include "VenusDlg.h"
#include "afxdialogex.h"
#include "Label.h"

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

	// ���ô���λ��
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);  //����������ȥ��
	SetWindowPos(NULL, 5, 5, 600, 300, 0);

	// ����͸��
	SetBackgroundColor(RGB(1,11,21));
	LONG ExtendedStyle = GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE );
	SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,ExtendedStyle | WS_EX_LAYERED );
	::SetLayeredWindowAttributes(GetSafeHwnd(),RGB(1,11,21),0,LWA_COLORKEY);

	// ����������С
	editFont.CreatePointFont(260,"����");
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

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	// ����֮ǰ���
	lastKey = "";
	for (int i=0; i< 100; i++)
	{
		CStatic *pOldInfo = (CStatic *)GetDlgItem(IDC_MYINFOTEXT+i);
		delete pOldInfo;
	}
	
	CString txt;
	GetDlgItemText(IDC_EDIT1, txt);

	vector<CString> keyMatch;
	myIndex->FindIndex(txt, keyMatch);

	// �����ǩ��ÿ���ַ��Ĵ�С
	int labelWidth = 30;
	int labelHeight = 60;

	int rect_left = 10;
	int rect_top = 60;

	for (int i=0; i < keyMatch.size(); i++)
	{
		if (i == 0)
		{
			lastKey = keyMatch[i];
		}
		//CStatic *pInfo = new CStatic();
		CRect rect;
		rect.left = rect_left;
		int clen = keyMatch[i].GetLength();
		rect.right = rect_left + clen * labelWidth;  // ����
		rect.top = rect_top + i * labelHeight;
		rect.bottom = rect_top + labelHeight * 0.8 + i * labelHeight;

		CLabel *pInfo = new CLabel();
		pInfo->Create(keyMatch[i], WS_VISIBLE, rect, this, IDC_MYINFOTEXT+i);
		pInfo->SetTextColor(RGB(255, 255, 255));
		pInfo->SetFontName("Fixedsys");
		pInfo->SetFontSize(labelWidth-1);
		pInfo->SetFontBold(TRUE);
		pInfo->SetBkColor(RGB(10, 136, 255));
	}

	SetWindowPos(NULL, 5, 5, 600, rect_top + (keyMatch.size()+1)*labelHeight, 0);
}


BOOL CVenusDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->wParam==VK_RETURN)
	{
		if (lastKey.IsEmpty())
		{
			//MessageBoxA(_T("û�취ִ�У����Ϊ��"));
			return TRUE;
		}
		else
		{
			//MessageBoxA(myIndex->GetLocalPath(lastKey));
			CString exePath = myIndex->GetLocalPath(lastKey);
			WinExec(exePath, SW_SHOWNORMAL);
			//_execl(exePath);
		}
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
		pDC->SetTextColor(RGB(240, 240, 240));
		pDC->SetBkColor(RGB(10, 10, 10));
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
