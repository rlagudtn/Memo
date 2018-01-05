//RightArrowKey.cpp
#include "RightArrowKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "SelectedText.h"
#include <afxwin.h>
RightArrowKey::RightArrowKey() {

}
RightArrowKey::RightArrowKey(const RightArrowKey& source) {

}
RightArrowKey::~RightArrowKey() {

}

void RightArrowKey::Implement(MemoForm *memoForm) {
	Long currentLine = memoForm->text->GetCurrent();
	Long currentColumn = memoForm->row->GetCurrent();

	Long textIndex = memoForm->text->GetCurrent();
	Long rowIndex = memoForm->row->GetCurrent() + 1;//다음 글자로 이동
	Long previousRowIndex;
	//개행이 있는 줄인지 확인
	//개행있고 줄의 끝글자라면
	if ( rowIndex >= memoForm->row->GetLength()) {
		textIndex++;
		rowIndex = -1;
	}
	//마지막줄을 넘었다면.
	if (textIndex >= memoForm->text->GetLength()) {
		textIndex = memoForm->text->GetLength() - 1;
		rowIndex = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetLength() - 1))->GetLength() - 1;
	}
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(textIndex));
	memoForm->row->Move(rowIndex);
	//캐럿이동
	CClientDC dc(memoForm);
	memoForm->caret->MoveToCurrent(memoForm);
	//캐럿이 화면영역위쪽이라면
	if (memoForm->caret->GetY() >= memoForm->screenHeight / memoForm->fontSize*memoForm->fontSize) {
		memoForm->paper->MoveToY(memoForm->paper->GetY() + memoForm->fontSize);
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}

	if (GetKeyState(VK_SHIFT) < 0) {
		if (memoForm->selectedText != NULL) {
			bool isSelected = memoForm->selectedText->SetAgainPos(currentLine, currentColumn, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
			if (isSelected == false ) {
				delete memoForm->selectedText;
				memoForm->selectedText = NULL;
			}

		}
		//선택된부분이 없을때
		else {
			memoForm->selectedText = new SelectedText;
			memoForm->selectedText->Select(memoForm, currentLine, currentColumn + 1, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
		}
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
}