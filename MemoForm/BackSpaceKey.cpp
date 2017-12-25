//BackSpaceKey.cpp
#include "BackSpaceKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "PageStack.h"
#include "LineFeed.h"
#include "SelectedText.h"
#include "RowInfo.h"
#include "MoveConnectedText.h"
#include <afxwin.h>
BackSpaceKey::BackSpaceKey() {

}
BackSpaceKey::BackSpaceKey(const BackSpaceKey& source) {

}
BackSpaceKey::~BackSpaceKey() {

}

void BackSpaceKey::Implement(MemoForm *memoForm) {
	//������� ���Ѱ� ������
	memoForm->isChanged = true;
	//�ڷ� ���⿡ ����
	memoForm->restoreToRearStack->Push(memoForm->page);
	//�Էµɶ� ������ ���� ����
	if (memoForm->restoreToFrontStack != NULL) {
		delete memoForm->restoreToFrontStack;
	}
	memoForm->restoreToFrontStack = new PageStack;
	//���� �Ǿ��� �ִ� �κ� ������ �����.
	if (memoForm->selectedText != NULL) {
		memoForm->selectedText->EraseSelectedText(memoForm);
		delete memoForm->selectedText;
		memoForm->selectedText = NULL;
		//���õ����ĸ� �����Ų��.
		MoveConnectedText connectText;
		CClientDC dc(memoForm);
		connectText.ChangeLine(memoForm, &dc, memoForm->text->GetCurrent());

	}
	else {
		if (memoForm->text->GetCurrent() != 0 || memoForm->row->GetCurrent() != -1) {
			Long currentText;
			Long currentRow;
			if (memoForm->row->GetCurrent() >= 0) {
				memoForm->row->Delete(memoForm->row->GetCurrent());
				//������ ���� ����.

			}
			//���� �� ó���϶�
			else {
				//�������� \r\n�� �����.
				memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(memoForm->text->GetCurrent() - 1));
				memoForm->row->Delete(memoForm->row->GetLength() - 1);
				memoForm->row->Delete(memoForm->row->GetLength() - 1);

			}
			currentText = memoForm->text->GetCurrent();
			currentRow = memoForm->row->GetCurrent();
			MoveConnectedText moveConnectedText;
			CClientDC dc(memoForm);
			moveConnectedText.ChangeLine(memoForm, &dc, currentText);
			//�����ٷ� �ٽ� �̵�
			memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(currentText));
			memoForm->row->Move(currentRow);
		}
	}

	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);

}