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
	//���� �̵�
	//ù�� �ƴҶ�
	if (memoForm->text->GetCurrent() > 0) {
		//���ٷ� �̵�
		memoForm->row=dynamic_cast<Row*>(memoForm->text->Move(memoForm->text->GetCurrent() - 1));
		MoveColumnByStringLength moveUp;
		CClientDC dc(memoForm);
		moveUp.MoveColumn(memoForm->row, &dc, caretPosX);
	}
	
	
	//ĳ���̵�
	CClientDC dc(memoForm);
	memoForm->caret->MoveToCurrent(memoForm, &dc);
	//ĳ���� ȭ�鿵�������̶��
	if (memoForm->caret->GetY() < 0) {
		memoForm->paper->MoveToY(memoForm->paper->GetY() - memoForm->fontSize);
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
	//Shift+up
	if (GetKeyState(VK_SHIFT) < 0) {
		if (memoForm->selectedText != NULL) {
			delete memoForm->selectedText;
		}
		memoForm->selectedText = new SelectedText(&dc, memoForm->paper->GetX(), memoForm->paper->GetY());
		memoForm->selectedText->SetTextPosition(memoForm->text->GetCurrent(), memoForm->row->GetCurrent() + 1, memoForm->keyDownTextIndex, memoForm->keyDownRowIndex);

	}
}