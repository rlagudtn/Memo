//MemoApp.cpp
#include "MemoApp.h"
#include "MemoForm.h"

BOOL MemoApp::InitInstance() {
	MemoForm *memoForm = new MemoForm;
	this->m_pMainWnd = memoForm;
	CRect rect(300, 300, 1000, 816);
	memoForm->Create(NULL, "¸Þ¸ðÀå", WS_OVERLAPPEDWINDOW | WS_VSCROLL, rect);
	this->m_pMainWnd->ShowWindow(SW_SHOW);
	this->m_pMainWnd->UpdateWindow();

	return TRUE;
}
MemoApp memoApp;