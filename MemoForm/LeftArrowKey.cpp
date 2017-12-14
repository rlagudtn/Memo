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
	//control ���� ����
	Long currentLine = memoForm->text->GetCurrent();
	Long currentColumn = memoForm->row->GetCurrent();
	if (GetKeyState(VK_CONTROL) >= 0) {
		//shiftŰ +left �� ���� ������ġ �ӽ� ����
		
		//�� �̵�
		memoForm->row->Move(memoForm->row->GetCurrent() - 1);
		//ù������ �۰� ù���� �ƴ϶��
		if (memoForm->row->GetCurrent() < -1 && memoForm->text->GetCurrent() > 0) {
			//���� �ٷ� �̵�
			memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(memoForm->text->GetCurrent() - 1));
			//�������� ���� ���๮������ Ȯ��
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
	//ĳ���̵�
	CClientDC dc(memoForm);
	memoForm->caret->MoveToCurrent(memoForm, &dc);
	//ĳ���� ȭ�鿵�������̶��
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
		//���õȺκ��� ������
		else {
			memoForm->selectedText = new SelectedText;
			memoForm->selectedText->Select(memoForm, memoForm->text->GetCurrent(), memoForm->row->GetCurrent()+1, currentLine, currentColumn);
		}

	}
}