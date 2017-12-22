//ChangeTextMenu.cpp
#include "ChangeTextMenu.h"
#include "MemoForm.h"
ChangeTextMenu::ChangeTextMenu() {}
ChangeTextMenu::~ChangeTextMenu() {}

void ChangeTextMenu::Implement(MemoForm *memoForm) {
	if (memoForm->pDlg == NULL)
	{
		memoForm->pDlg = new CFindReplaceDialog;  // Must be created on the heap

		memoForm->pDlg->Create(FALSE, _T(""), _T(""), FR_HIDEUPDOWN | FR_HIDEWHOLEWORD, memoForm);

	}
}