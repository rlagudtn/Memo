//CtrlCopyKey.cpp
#include "CtrlCopyKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "LineFeed.h"
#include "SelectedText.h"
#include "RowInfo.h"
#include <afxwin.h>
CtrlCopyKey::CtrlCopyKey() {

}
CtrlCopyKey::CtrlCopyKey(const CtrlCopyKey& source) {

}
CtrlCopyKey::~CtrlCopyKey() {

}

void CtrlCopyKey::Implement(MemoForm *memoForm) {
	CString copiedStr = "";
	if (memoForm->selectedText != NULL) {
		copiedStr = CString(memoForm->selectedText->GetBuffer().c_str());
	}
	HGLOBAL hGloBal = GlobalAlloc(GHND | GMEM_SHARE, (lstrlen(copiedStr) + 1) * sizeof(TCHAR));

	PSTR pStr = (PSTR)GlobalLock(hGloBal);
	if (pStr != NULL) {
		lstrcpy(pStr, TEXT(copiedStr));

		// �� ����
		GlobalUnlock(pStr);

		// Ŭ������ ����
		memoForm->OpenClipboard();

		// Ŭ������ �ʱ�ȭ
		EmptyClipboard();

		// Ŭ�����忡 ����
		SetClipboardData(CF_TEXT, pStr);

		// Ŭ������ Ŭ����
		CloseClipboard();
	}
}