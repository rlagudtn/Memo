//MakeNewFileMenu.cpp
#include "MakeNewFileMenu.h"
#include "MemoForm.h"
MakeNewFileMenu::MakeNewFileMenu() {}
MakeNewFileMenu::~MakeNewFileMenu() {}

void MakeNewFileMenu::Implement(MemoForm *memoForm) {
	memoForm->MessageBox(_T("¤·¤·"), _T("¤¡¤¡"), MB_YESNO);
}