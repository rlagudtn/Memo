//SelectAllMenu.cpp
#include "SelectAllMenu.h"
#include "MemoForm.h"
#include "SelectedText.h"
#include "Text.h"
#include "Row.h"
#include "Paper.h"
SelectAllMenu::SelectAllMenu() {}
SelectAllMenu::~SelectAllMenu() {}

void SelectAllMenu::Implement(MemoForm *memoForm) {
	if (memoForm->selectedText != NULL) {
		delete memoForm->selectedText;

	}
	memoForm->selectedText = new SelectedText;

	//마지막줄로 이동
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(memoForm->text->GetLength() - 1));
	memoForm->row->Move(memoForm->row->GetLength()-1);
	//페이퍼 이동
	memoForm->paper->MoveToY(memoForm->paper->GetHeight() - memoForm->screenHeight / memoForm->fontSize*memoForm->fontSize);
	memoForm->scrollInfo.nPos = memoForm->paper->GetY();

	memoForm->selectedText->Select(memoForm, 0, 0, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
}