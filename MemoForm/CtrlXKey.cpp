//CtrlXKey.cpp
#include "CtrlXKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "SelectedText.h"
#include "MoveConnectedText.h"
#include <afxwin.h>
CtrlXKey::CtrlXKey() {

}
CtrlXKey::CtrlXKey(const CtrlXKey& source) {

}
CtrlXKey::~CtrlXKey() {

}

void CtrlXKey::Implement(MemoForm *memoForm) {
	CString copiedStr = "";
	if (memoForm->selectedText != NULL) {
		copiedStr = CString(memoForm->selectedText->GetBuffer().c_str());

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
		memoForm->selectedText->EraseSelectedText(memoForm);
		//현재줄 보정하기
		MoveConnectedText moveConnectedText;
		CClientDC dc(memoForm);
		moveConnectedText.ChangeLine(memoForm, &dc, memoForm->text->GetCurrent());
		if (memoForm->selectedText != NULL) {
			delete memoForm->selectedText;
			memoForm->selectedText = NULL;
		}
		
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
}