//HomeKey.cpp
#include "HomeKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "SelectedText.h"
#include <afxwin.h>
HomeKey::HomeKey() {

}
HomeKey::HomeKey(const HomeKey& source) {

}
HomeKey::~HomeKey() {

}

void HomeKey::Implement(MemoForm *memoForm) {
	Long currentLine = memoForm->text->GetCurrent();
	Long currentColumn = memoForm->row->GetCurrent();
	if (GetKeyState(VK_CONTROL) < 0) {
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(0));
		memoForm->paper->MoveToY(0);
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
	memoForm->row->Move(-1);

	//캐럿이동
	CClientDC dc(memoForm);
	memoForm->caret->MoveToCurrent(memoForm);
	//캐럿이 화면영역위쪽이라면
	

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
			memoForm->selectedText->Select(memoForm, memoForm->text->GetCurrent(), 0, memoForm->text->GetCurrent(), currentColumn);
		}
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
}