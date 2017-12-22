//SelectAllMenu.cpp
#include "SelectAllMenu.h"
#include "MemoForm.h"
#include "SelectedText.h"
#include "Text.h"
#include "Row.h"
#include "RowInfo.h"
#include "Paper.h"
SelectAllMenu::SelectAllMenu() {}
SelectAllMenu::~SelectAllMenu() {}

void SelectAllMenu::Implement(MemoForm *memoForm) {
	if (memoForm->selectedText != NULL) {
		delete memoForm->selectedText;

	}
	memoForm->selectedText = new SelectedText;

	//�������ٷ� �̵�
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(memoForm->text->GetLength() - 1));
	RowInfo rowInfo;
	rowInfo.GetRowInfo(memoForm->row);
	memoForm->row->Move(rowInfo.GetLastIndex());
	//������ �̵�
	memoForm->paper->MoveToY(memoForm->paper->GetHeight() - memoForm->screenHeight / memoForm->fontSize*memoForm->fontSize);
	memoForm->scrollInfo.nPos = memoForm->paper->GetY();

	memoForm->selectedText->Select(memoForm, 0, 0, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
}