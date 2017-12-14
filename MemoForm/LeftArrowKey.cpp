//LeftArrowKey.cpp
#include "LeftArrowKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "LineFeed.h"
#include "SelectedText.h"
#include <afxwin.h>
LeftArrowKey::LeftArrowKey() {

}
LeftArrowKey::LeftArrowKey(const LeftArrowKey& source) {

}
LeftArrowKey::~LeftArrowKey() {

}

void LeftArrowKey::Implement(MemoForm *memoForm) {
	//control 제외 상태
	Long currentLine = memoForm->text->GetCurrent();
	Long currentColumn = memoForm->row->GetCurrent();
	if (GetKeyState(VK_CONTROL) >= 0) {
		//shift키 +left 를 위해 현재위치 임시 저장
		
		//열 이동
		memoForm->row->Move(memoForm->row->GetCurrent() - 1);
		//첫열보다 작고 첫줄이 아니라면
		if (memoForm->row->GetCurrent() < -1 && memoForm->text->GetCurrent() > 0) {
			//앞의 줄로 이동
			memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(memoForm->text->GetCurrent() - 1));
			//앞의줄의 끝이 개행문자인지 확인
			LineFeed line;
			bool isLineFeed = line.IsLineFeed(memoForm->row);
			if (isLineFeed == true) {
				memoForm->row->Move(memoForm->row->GetLength() - 3);
			}
			else {
				memoForm->row->Move(memoForm->row->GetLength() - 1);
			}
		}
		else if (memoForm->row->GetCurrent() < -1 && memoForm->text->GetCurrent() <= 0) {
			memoForm->row->Move(-1);
		}
		
	}
	//캐럿이동
	CClientDC dc(memoForm);
	memoForm->caret->MoveToCurrent(memoForm, &dc);
	//캐럿이 화면영역위쪽이라면
	if (memoForm->caret->GetY() < 0) {
		memoForm->paper->MoveToY(memoForm->paper->GetY() - memoForm->fontSize);
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
	if (GetKeyState(VK_SHIFT) < 0) {
		if (memoForm->selectedText != NULL) {
			bool isSelected = memoForm->selectedText->SetAgainPos(currentLine, currentColumn, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
			if (isSelected == false && memoForm->text->GetCurrent() >0) {
				delete memoForm->selectedText;
				memoForm->selectedText = NULL;
			}
		
		}
		//선택된부분이 없을때
		else {
			memoForm->selectedText = new SelectedText;
			memoForm->selectedText->Select(memoForm, memoForm->text->GetCurrent(), memoForm->row->GetCurrent()+1, currentLine, currentColumn);
		}

	}
}