//CtrlXKey.cpp
#include "CtrlXKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "PageStack.h"
#include "Paper.h"
#include "SelectedText.h"
#include "ConnectedInfo.h"
#include "MoveConnectedText.h"
#include <afxwin.h>
CtrlXKey::CtrlXKey() {

}
CtrlXKey::CtrlXKey(const CtrlXKey& source) {

}
CtrlXKey::~CtrlXKey() {

}

void CtrlXKey::Implement(MemoForm *memoForm) {
	memoForm->isChanged = true;

	CString copiedStr = "";
	if (memoForm->selectedText != NULL) {
		//뒤로 가기에 저장
		memoForm->restoreToRearStack->Push(memoForm->page);
		//입력될때 앞으로 가기 리셋
		if (memoForm->restoreToFrontStack != NULL) {
			delete memoForm->restoreToFrontStack;
		}
		memoForm->restoreToFrontStack = new PageStack;
		//선택된 부분 복사
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
		Long lastIndex = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->selectedText->GetEndLine()))->GetLength() - 1;
		memoForm->selectedText->EraseSelectedText(memoForm);
		if (lastIndex == memoForm->selectedText->GetEndColumn()) {
			memoForm->row->DisConnect();
		}
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