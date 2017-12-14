//EnterKey.cpp
#include "EnterKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "ConnectedInfo.h"
#include "LineFeed.h"
#include "SelectedText.h"
#include "EraseSelectedText.h"
#include "CutString.h"
#include "LineController.h"
#include "CopyToMemo.h"
#include "RowInfo.h"
#include <afxwin.h>
EnterKey::EnterKey() {

}
EnterKey::EnterKey(const EnterKey& source) {

}
EnterKey::~EnterKey() {

}

void EnterKey::Implement(MemoForm *memoForm) {
	//선택되어져 있는 줄이 있다면
	if (memoForm->selectedText != NULL) {
		//지운다.
		EraseSelectedText eraseText(memoForm->selectedText->GetStartLine(), memoForm->selectedText->GetStartColumn(), memoForm->selectedText->GetEndLine(), memoForm->selectedText->GetEndColumn());
		memoForm->text->Accept(&eraseText);
		delete memoForm->selectedText;
		memoForm->selectedText = NULL;
		
	}
	//현재 줄에 연결되어져 있는 줄이 있는지 확인한다.
	ConnectedInfo connectedInfo;
	Long endLine = connectedInfo.GetEndOfConnected(memoForm->text, memoForm->text->GetCurrent());
	//자른다.
	CutString cutString;
	CString cuttedText = CString(cutString.CutText(memoForm, memoForm->text->GetCurrent(), memoForm->row->GetCurrent() + 1, endLine, dynamic_cast<Row*>(memoForm->text->GetAt(endLine))->GetLength() - 1).c_str());
	//개행문자 추가
	LineFeed lineFeed;
	lineFeed.SetLineFeed(memoForm->row);
	//새로운 줄 생성
	LineController lineController;
	lineController.MakeNewLine(memoForm, memoForm->text->GetCurrent() + 1);
	//current저장
	Long textCurrent = memoForm->text->GetCurrent();
	Long rowCurrent = memoForm->row->GetCurrent();
	//삭제했던 텍스트를 다시 적는다.
	CClientDC dc(memoForm);
	cuttedText.Replace("\r\n", "");
	CopyToMemo copyToMemo(&dc, memoForm->screenWidth, (LPCTSTR)cuttedText);
	memoForm->text->Accept(&copyToMemo);
	//개행추가
	lineFeed.SetLineFeed(dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent())));
	//현재위치 변경
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(textCurrent));
	memoForm->row->Move(rowCurrent);
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
}