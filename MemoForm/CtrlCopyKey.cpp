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

		// 락 해제
		GlobalUnlock(pStr);

		// 클립보드 오픈
		memoForm->OpenClipboard();

		// 클립보드 초기화
		EmptyClipboard();

		// 클립보드에 복사
		SetClipboardData(CF_TEXT, pStr);

		// 클립보드 클로즈
		CloseClipboard();
	}
}