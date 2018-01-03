//DeleteKey.cpp
#include "DeleteKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "PageStack.h"
#include "MoveConnectedText.h"
#include "SelectedText.h"
#include <afxwin.h>
DeleteKey::DeleteKey() {

}
DeleteKey::DeleteKey(const DeleteKey& source) {

}
DeleteKey::~DeleteKey() {

}

void DeleteKey::Implement(MemoForm *memoForm) {
	memoForm->isChanged = true;

	//�ڷ� ���⿡ ����
	memoForm->restoreToRearStack->Push(memoForm->page);
	//�Էµɶ� ������ ���� ����
	if (memoForm->restoreToFrontStack != NULL) {
		delete memoForm->restoreToFrontStack;
	}
	memoForm->restoreToFrontStack = new PageStack;

	//���õ� �κ� ������ ����
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
		bool isLastIndex = memoForm->row->GetLength() - 1;
		if (isLastIndex == false) {
			memoForm->row->Delete(memoForm->row->GetCurrent() + 1);
		}
		else if(isLastIndex==true&& memoForm->text->GetCurrent()<memoForm->text->GetLength()-1){
			memoForm->row->Connect();
			//���� ���̶� ��ģ��
			MoveConnectedText connectText;
			CClientDC dc(memoForm);
			connectText.ChangeLine(memoForm, &dc, memoForm->text->GetCurrent());
		}
	}
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight));
}