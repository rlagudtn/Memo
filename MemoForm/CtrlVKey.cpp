//CtrlVKey.cpp
#include "CtrlVKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "PageStack.h"
#include "SelectedText.h"
#include "CutString.h"
#include "ConnectedInfo.h"
#include "CopyToMemo.h"
#include <afxwin.h>
CtrlVKey::CtrlVKey() {

}
CtrlVKey::CtrlVKey(const CtrlVKey& source) {

}
CtrlVKey::~CtrlVKey() {

}

void CtrlVKey::Implement(MemoForm *memoForm) {
	memoForm->isChanged = true;
	//뒤로 가기에 저장
	memoForm->restoreToRearStack->Push(memoForm->page);
	//입력될때 앞으로 가기 리셋
	if (memoForm->restoreToFrontStack != NULL) {
		delete memoForm->restoreToFrontStack;
	}
	memoForm->restoreToFrontStack = new PageStack;

	//선택된부분있으면 삭제
	if (memoForm->selectedText != NULL) {
		memoForm->selectedText->EraseSelectedText(memoForm);
		delete memoForm->selectedText;
		memoForm->selectedText = NULL;
	}
	if (IsClipboardFormatAvailable(CF_TEXT)) {
		memoForm->OpenClipboard();
		HANDLE hClipboardData = GetClipboardData(CF_TEXT);
		CString *str = (CString*)GlobalLock(hClipboardData);
		GlobalUnlock(hClipboardData);
		//붙여넣기 하기 전의 선택된줄 뒤의 텍스트들을 복사한다
		ConnectedInfo connectedInfo;
		Long endLine = connectedInfo.GetEndOfConnected(memoForm->text, memoForm->text->GetCurrent());
		//자른다.
		CutString cutString;
		CString cuttedText = CString(cutString.CutText(memoForm, memoForm->text->GetCurrent(), memoForm->row->GetCurrent() + 1, endLine, dynamic_cast<Row*>(memoForm->text->GetAt(endLine))->GetLength() - 1).c_str());
		CClientDC dc(memoForm);
		CopyToMemo copyToMemo;
		copyToMemo.WriteToMemo(memoForm, (LPCTSTR)str);
		memoForm->row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
		//현 위치 임시저장
		Long textCurrent = memoForm->text->GetCurrent();
		Long rowCurrent = memoForm->row->GetCurrent();
		//임시저장한 텍스트를 다시 적는다.
		CopyToMemo copyAgain;
		copyAgain.WriteToMemo(memoForm, (LPCTSTR)cuttedText);
		//현재 위치를 원 상태로 돌린다
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(textCurrent));
		memoForm->row->Move(rowCurrent);

	}
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);

}