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
		//�ڷ� ���⿡ ����
		memoForm->restoreToRearStack->Push(memoForm->page);
		//�Էµɶ� ������ ���� ����
		if (memoForm->restoreToFrontStack != NULL) {
			delete memoForm->restoreToFrontStack;
		}
		memoForm->restoreToFrontStack = new PageStack;
		//���õ� �κ� ����
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
		Long lastIndex = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->selectedText->GetEndLine()))->GetLength() - 1;
		memoForm->selectedText->EraseSelectedText(memoForm);
		if (lastIndex == memoForm->selectedText->GetEndColumn()) {
			memoForm->row->DisConnect();
		}
		//������ �����ϱ�
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