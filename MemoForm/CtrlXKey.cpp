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
		memoForm->selectedText->EraseSelectedText(memoForm);
		//������ �����ϱ�
		MoveConnectedText moveConnectedText;
		CClientDC dc(memoForm);
		moveConnectedText.ChangeLine(memoForm, &dc, memoForm->text->GetCurrent());
		if (memoForm->selectedText != NULL) {
			delete memoForm->selectedText;
			memoForm->selectedText = NULL;
		}
		memoForm->caret->MoveToCurrent(memoForm, &dc);
		if (memoForm->caret->GetY() < 0) {
			memoForm->paper->MoveToY(memoForm->text->GetCurrent()*memoForm->fontSize);
		}
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
}