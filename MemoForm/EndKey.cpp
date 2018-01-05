//EndKey.cpp
#include "EndKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "SelectedText.h"
#include <afxwin.h>
EndKey::EndKey() {

}
EndKey::EndKey(const EndKey& source) {

}
EndKey::~EndKey() {

}

void EndKey::Implement(MemoForm *memoForm) {
	Long currentLine = memoForm->text->GetCurrent();
	Long currentColumn = memoForm->row->GetCurrent();
	if (GetKeyState(VK_CONTROL) < 0) {
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(memoForm->text->GetLength()-1));
		memoForm->paper->MoveToY(memoForm->paper->GetHeight()-memoForm->screenHeight/memoForm->fontSize*memoForm->fontSize);
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
	memoForm->row->Move(memoForm->row->GetLength()-1);

	//ĳ���̵�
	CClientDC dc(memoForm);
	memoForm->caret->MoveToCurrent(memoForm);
	//ĳ���� ȭ�鿵�������̶��


	if (GetKeyState(VK_SHIFT) < 0) {
		if (memoForm->selectedText != NULL) {
			bool isSelected = memoForm->selectedText->SetAgainPos(currentLine, currentColumn, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
			if (isSelected == false) {
				delete memoForm->selectedText;
				memoForm->selectedText = NULL;
			}
		}
		else {
			memoForm->selectedText = new SelectedText;
			memoForm->selectedText->Select(memoForm, memoForm->text->GetCurrent(), currentColumn+1, memoForm->text->GetCurrent(),memoForm->row->GetCurrent());
		}
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);

	}
}