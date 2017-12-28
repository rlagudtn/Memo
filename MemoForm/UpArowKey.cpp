//UpArrowKey.cpp
#include "UpArrowKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "MoveColumnByStringLength.h"
#include "SelectedText.h"
#include <afxwin.h>
UpArrowKey::UpArrowKey() {

}
UpArrowKey::UpArrowKey(const UpArrowKey& source) {

}
UpArrowKey::~UpArrowKey() {

}

void UpArrowKey::Implement(MemoForm *memoForm) {
	Long caretPosX = memoForm->caret->GetX();
	Long currentLine = memoForm->text->GetCurrent();
	Long currentColumn = memoForm->row->GetCurrent();
	//위로 이동
	//첫줄 아닐때
	if (memoForm->text->GetCurrent() > 0) {
		//현재줄의 정보를 가져온다.
		Row *previousRow = memoForm->row;
		//윗줄로 이동
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(memoForm->text->GetCurrent() - 1));
		
		if (previousRow->GetCurrent()>=previousRow->GetLength()-1) {
			memoForm->row->Move(memoForm->row->GetLength()-1);
		}
		else {
			MoveColumnByStringLength moveUp;
			CClientDC dc(memoForm);
			moveUp.MoveColumn(memoForm->row, &dc, caretPosX);
		}
	}
	//캐럿이동
	CClientDC dc(memoForm);
	memoForm->caret->MoveToCurrent(memoForm);
	//캐럿이 화면영역위쪽이라면
	if (memoForm->caret->GetY() < 0) {
		memoForm->paper->MoveToY(memoForm->paper->GetY() - memoForm->fontSize);
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
	//Shift+up
	if (GetKeyState(VK_SHIFT) < 0) {
		if (memoForm->selectedText != NULL) {

			bool isSelected = memoForm->selectedText->SetAgainPos(currentLine, currentColumn, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
			if (isSelected == false && memoForm->text->GetCurrent() > 0) {
				delete memoForm->selectedText;
				memoForm->selectedText = NULL;
			}
		}
	//선택된부분이 없을때
		else {
			memoForm->selectedText = new SelectedText;
			memoForm->selectedText->Select(memoForm, memoForm->text->GetCurrent(), memoForm->row->GetCurrent() + 1, currentLine, currentColumn);
		}
	}

}