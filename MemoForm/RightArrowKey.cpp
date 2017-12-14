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
#include "LineFeed.h"
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
	if (GetKeyState(VK_CONTROL) >= 0) {
		

		Long textIndex = memoForm->text->GetCurrent();
		Long rowIndex = memoForm->row->GetCurrent() + 1;//���� ���ڷ� �̵�
		Long previousRowIndex;
		//������ �ִ� ������ Ȯ��
		LineFeed lineFeed;
		bool isLineFeed = lineFeed.IsLineFeed(memoForm->row);
		//�����ְ� ���� �����ڶ��
		if (isLineFeed == true && rowIndex > memoForm->row->GetLength() - 3) {
			textIndex++;
			rowIndex = -1;
		}
		else if (isLineFeed == false && rowIndex >= memoForm->row->GetLength()) {
			textIndex++;
			rowIndex = -1;
		}
		//���������� �Ѿ��ٸ�.
		if (textIndex >= memoForm->text->GetLength()) {
			textIndex = memoForm->text->GetLength() - 1;
			bool isLineFeed = lineFeed.IsLineFeed(dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetLength()-1)));
			//�����ְ� ���� �����ڶ��
			if (isLineFeed == true) {
				rowIndex = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetLength() - 1))->GetLength() - 3;
			}
			else if (isLineFeed == false && memoForm->row->GetCurrent() >= memoForm->row->GetLength()) {
				rowIndex = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetLength() - 1))->GetLength() - 1;
			}
		}
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(textIndex));
		memoForm->row->Move(rowIndex);
	}
	//ĳ���̵�
	CClientDC dc(memoForm);
	memoForm->caret->MoveToCurrent(memoForm, &dc);
	//ĳ���� ȭ�鿵�������̶��
	if (memoForm->caret->GetY() >= memoForm->screenHeight/memoForm->fontSize*memoForm->fontSize) {
		memoForm->paper->MoveToY(memoForm->paper->GetY() + memoForm->fontSize);
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
	
	if (GetKeyState(VK_SHIFT) < 0) {
		if (memoForm->selectedText != NULL) {
			bool isSelected = memoForm->selectedText->SetAgainPos(currentLine, currentColumn, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
			if (isSelected == false && memoForm->text->GetCurrent() < memoForm->text->GetLength() - 1) {
				delete memoForm->selectedText;
				memoForm->selectedText = NULL;
			}
			
		}
		//���õȺκ��� ������
		else {
			memoForm->selectedText = new SelectedText;
			memoForm->selectedText->Select(memoForm, currentLine, currentColumn + 1, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
		}

	}
}