
// OpenGL1Dlg.h : header file
//

#pragma once


#include "GlView.h"

// COpenGL1Dlg dialog
class COpenGL1Dlg : public CDialog
{
// Construction
public:
	COpenGL1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGL1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
private:
	CGlView* view;

public:

	afx_msg void OnStnClickedPic();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDeltaposRotatex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposRotatez(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposRotatey(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMovex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMovey(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposMovez(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBarrel();
	afx_msg void OnBnClickedStoproll();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedFire();
	afx_msg void OnBnClickedAccelerate();
};
