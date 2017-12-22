//FindMenu.cpp
#include "FindMenu.h"
#include "MemoForm.h"
FindMenu::FindMenu() {}
FindMenu::~FindMenu() {}

void FindMenu::Implement(MemoForm *memoForm) {
	memoForm->pDlg = new CFindReplaceDialog;  // Must be created on the heap

	memoForm->pDlg->Create(TRUE, _T(""), _T(""), FR_HIDEUPDOWN | FR_HIDEWHOLEWORD, memoForm);
	memoForm->HideCaret();
	memoForm->pDlg->CreateSolidCaret(1, memoForm->fontSize);
}