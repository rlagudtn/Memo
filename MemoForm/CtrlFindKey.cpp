//CtrlFindKey.cpp
#include "CtrlFindKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "SelectedText.h"
#include <afxwin.h>
CtrlFindKey::CtrlFindKey() {

}
CtrlFindKey::CtrlFindKey(const CtrlFindKey& source) {

}
CtrlFindKey::~CtrlFindKey() {

}

void CtrlFindKey::Implement(MemoForm *memoForm) {
		memoForm->pDlg = new CFindReplaceDialog;  // Must be created on the heap

		memoForm->pDlg->Create(TRUE, _T(""), _T(""), FR_HIDEUPDOWN | FR_HIDEWHOLEWORD, memoForm);
		memoForm->HideCaret();
		memoForm->pDlg->CreateSolidCaret(1, memoForm->fontSize);
}