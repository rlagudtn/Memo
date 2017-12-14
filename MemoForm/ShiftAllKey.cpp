//ShiftAllKey.cpp
#include "ShiftAllKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "LineFeed.h"
#include "SelectedText.h"
#include "RowInfo.h"
#include <afxwin.h>
ShiftAllKey::ShiftAllKey() {

}
ShiftAllKey::ShiftAllKey(const ShiftAllKey& source) {

}
ShiftAllKey::~ShiftAllKey() {

}

void ShiftAllKey::Implement(MemoForm *memoForm) {
	if (memoForm->selectedText != NULL) {
		delete memoForm->selectedText;

	}
	memoForm->selectedText = new SelectedText;

	//마지막줄로 이동
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(memoForm->text->GetLength() - 1));
	RowInfo rowInfo;
	rowInfo.GetRowInfo(memoForm->row);
	memoForm->row->Move(rowInfo.GetLastIndex());

	memoForm->selectedText->Select(memoForm,0, 0, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
}