//DownArrowKey.cpp
#include "DownArrowKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "MoveColumnByStringLength.h"
#include "SelectedText.h"
#include "RowInfo.h"
#include <afxwin.h>
DownArrowKey::DownArrowKey() {

}
DownArrowKey::DownArrowKey(const DownArrowKey& source) {

}
DownArrowKey::~DownArrowKey() {

}

void DownArrowKey::Implement(MemoForm *memoForm) {
	Long caretPosX = memoForm->caret->GetX();
	Long currentLine = memoForm->text->GetCurrent();
	Long currentColumn = memoForm->row->GetCurrent();
	//���� �̵�
	//���������� �ƴҶ�
	if (memoForm->text->GetCurrent() < memoForm->text->GetLength() - 1) {
		//�������� ������ �����´�.
		RowInfo rowInfo;
		rowInfo.GetRowInfo(memoForm->row);
		//���ٷ� �̵�
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(memoForm->text->GetCurrent() + 1));
		bool isLastIndex = rowInfo.GetIsLastIndex();
		//������ ���̶��
		if (isLastIndex == true) {
			rowInfo.GetRowInfo(memoForm->row);
			memoForm->row->Move(rowInfo.GetLastIndex());
		}
		else {
		
			MoveColumnByStringLength moveUp;
			CClientDC dc(memoForm);
			moveUp.MoveColumn(memoForm->row, &dc, caretPosX);
		}
	}


	//ĳ���̵�
	CClientDC dc(memoForm);
	memoForm->caret->MoveToCurrent(memoForm, &dc);
	//ĳ���� ȭ�鿵�������̶��
	if (memoForm->caret->GetY() >= memoForm->screenHeight / memoForm->fontSize*memoForm->fontSize) {
		memoForm->paper->MoveToY(memoForm->paper->GetY() + memoForm->fontSize);
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
	//Shift+up
	if (GetKeyState(VK_SHIFT) < 0) {
			if (memoForm->selectedText != NULL) {
				bool isSelected = memoForm->selectedText->SetAgainPos(currentLine, currentColumn, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
				if (isSelected == false && memoForm->text->GetCurrent() < memoForm->text->GetLength() - 1) {
					delete memoForm->selectedText;
					memoForm->selectedText = NULL;
				}
			}
			else {
				memoForm->selectedText = new SelectedText;
				memoForm->selectedText->Select(memoForm, currentLine, currentColumn + 1, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
			}
	}
}		