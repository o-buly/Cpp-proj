
// OpenGL1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "OpenGL1.h"
#include "OpenGL1Dlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <iostream>
#include "Mmsystem.h";
#include "windows.h";

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// COpenGL1Dlg dialog



COpenGL1Dlg::COpenGL1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OPENGL1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenGL1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpenGL1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_PIC, &COpenGL1Dlg::OnStnClickedPic)
	ON_WM_TIMER()
	ON_NOTIFY(UDN_DELTAPOS, IDC_RotateX, &COpenGL1Dlg::OnDeltaposRotatex)
	ON_NOTIFY(UDN_DELTAPOS, IDC_RotateZ, &COpenGL1Dlg::OnDeltaposRotatez)
	ON_NOTIFY(UDN_DELTAPOS, IDC_RotateY, &COpenGL1Dlg::OnDeltaposRotatey)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MoveX, &COpenGL1Dlg::OnDeltaposMovex)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MoveY, &COpenGL1Dlg::OnDeltaposMovey)
	ON_NOTIFY(UDN_DELTAPOS, IDC_MoveZ, &COpenGL1Dlg::OnDeltaposMovez)
	ON_BN_CLICKED(IDC_Roll, &COpenGL1Dlg::OnBnClickedBarrel)
	ON_BN_CLICKED(IDC_Stop, &COpenGL1Dlg::OnBnClickedStoproll)
	ON_BN_CLICKED(IDC_Reset, &COpenGL1Dlg::OnBnClickedReset)
	ON_BN_CLICKED(IDCANCEL, &COpenGL1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_Fire, &COpenGL1Dlg::OnBnClickedFire)
	ON_BN_CLICKED(IDC_ACCELERATE, &COpenGL1Dlg::OnBnClickedAccelerate)
END_MESSAGE_MAP()


// COpenGL1Dlg message handlers

BOOL COpenGL1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	view = new CGlView(GetDlgItem(IDC_PIC));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COpenGL1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpenGL1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();

		view->vDrawGLScene();
		
		BOOL PlaySound(
			LPCTSTR pszSound,
			HMODULE hmod,
			DWORD fdwSound
		);
		//PlaySound(TEXT("aircraft_flying.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		PlaySound(TEXT("topgun.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		GetDlgItem(IDC_Barrel)->EnableWindow(TRUE);

	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenGL1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COpenGL1Dlg::OnStnClickedPic()
{
	// TODO: Add your control notification handler code here
}


void COpenGL1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	if (nIDEvent == 1) {
		view->roll += 5;
		view->vDrawGLScene();
	}
	if (nIDEvent == 2) {
		view->rockets -= 0.4;
		view->vDrawGLScene();
		if (view->rockets <= -46)
		{
			BOOL PlaySound(
				LPCTSTR pszSound,
				HMODULE hmod,
				DWORD fdwSound
			);
			//PlaySound(TEXT("aircraft_flying.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			PlaySound(TEXT("topgun.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			KillTimer(2);		
		}
	}
	if (nIDEvent == 3) 
	{
		view->Movez += 0.3;
		view->vDrawGLScene();
		if (view->Movez >= 50)
		{
			view->Movez = -50;
			//KillTimer(3);
		}
	}

}
void COpenGL1Dlg::OnBnClickedAccelerate()
{
	SetTimer(3, 10, NULL);
	// TODO: Add your control notification handler code here
}

void p() {
	BOOL PlaySound(
		LPCTSTR pszSound,
		HMODULE hmod,
		DWORD fdwSound
	);
	//PlaySound(TEXT("aircraft_flying.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySound(TEXT("topgun.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}


void COpenGL1Dlg::OnDeltaposRotatex(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	view->Rotx -= 5 * pNMUpDown->iDelta;
	view->vDrawGLScene();
	*pResult = 0;
	// TODO: Add your control notification handler code here
}


void COpenGL1Dlg::OnDeltaposRotatez(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	view->Rotz += 5 * pNMUpDown->iDelta;
	view->vDrawGLScene();
	*pResult = 0;
	// TODO: Add your control notification handler code here
}


void COpenGL1Dlg::OnDeltaposRotatey(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	view->Roty += 5 * pNMUpDown->iDelta;
	view->vDrawGLScene();
	*pResult = 0;
	// TODO: Add your control notification handler code here
}


void COpenGL1Dlg::OnDeltaposMovex(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	view->Movex -= 5 * pNMUpDown->iDelta;

	view->vDrawGLScene();
	*pResult = 0;
	// TODO: Add your control notification handler code here
}


void COpenGL1Dlg::OnDeltaposMovey(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	view->Movey-= 1.5 * pNMUpDown->iDelta;

	view->vDrawGLScene();
	*pResult = 0;
	// TODO: Add your control notification handler code here
}


void COpenGL1Dlg::OnDeltaposMovez(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	view->Movez +=5 * pNMUpDown->iDelta;

	view->vDrawGLScene();
	*pResult = 0;
	// TODO: Add your control notification handler code here
}


void COpenGL1Dlg::OnBnClickedBarrel()
{

	BOOL PlaySound(
		LPCTSTR pszSound,
		HMODULE hmod,
		DWORD fdwSound
	);
	PlaySound(TEXT("roll.wav"), NULL, SND_FILENAME | SND_ASYNC);
	SetTimer(1, 10, NULL);
	GetDlgItem(IDC_StopRoll)->EnableWindow(TRUE);
	// TODO: Add your control notification handler code here
}


void COpenGL1Dlg::OnBnClickedStoproll()
{
	KillTimer(1);
	GetDlgItem(IDC_StopRoll)->EnableWindow(FALSE);
	p();
	// TODO: Add your control notification handler code here
}

void COpenGL1Dlg::OnBnClickedFire()
{
	BOOL PlaySound(
		LPCTSTR pszSound,
		HMODULE hmod,
		DWORD fdwSound
	);
	SetTimer(2, 10, NULL);
	PlaySound(TEXT("rocket.wav"), NULL, SND_FILENAME|SND_ASYNC);

	// TODO: Add your control notification handler code here
}




void COpenGL1Dlg::OnBnClickedReset()
{
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	view->Movex = 0;
	view->Movey = 0;
	view->Movez = 0;
	view->Rotx = 0;
	view->Roty = 0;
	view->Rotz = 0;
	view->roll = 0;
	view->rockets = 0;
	view->vDrawGLScene();
	BOOL PlaySound(
		LPCTSTR pszSound,
		HMODULE hmod,
		DWORD fdwSound
	);
	//PlaySound(TEXT("aircraft_flying.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySound(TEXT("topgun.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}


void COpenGL1Dlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}








