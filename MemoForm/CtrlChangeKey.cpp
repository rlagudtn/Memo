//CtrlChangeKey.cpp
#include "CtrlChangeKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "LineFeed.h"
#include "SelectedText.h"
#include "RowInfo.h"
#include <afxwin.h>
CtrlChangeKey::CtrlChangeKey() {

}
CtrlChangeKey::CtrlChangeKey(const CtrlChangeKey& source) {

}
CtrlChangeKey::~CtrlChangeKey() {

}

void CtrlChangeKey::Implement(MemoForm *memoForm) {

	if (memoForm->pDlg == NULL)
	{
		memoForm->pDlg = new CFindReplaceDialog;  // Must be created on the heap

		memoForm->pDlg->Create(FALSE, _T(""), _T(""), FR_HIDEUPDOWN | FR_HIDEWHOLEWORD, memoForm);

	}
}