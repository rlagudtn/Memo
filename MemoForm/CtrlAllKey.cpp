//CtrlAllKey.cpp
#include "CtrlAllKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "LineFeed.h"
#include "SelectedText.h"
#include "RowInfo.h"
#include <afxwin.h>
CtrlAllKey::CtrlAllKey() {

}
CtrlAllKey::CtrlAllKey(const CtrlAllKey& source) {

}
CtrlAllKey::~CtrlAllKey() {

}

void CtrlAllKey::Implement(MemoForm *memoForm) {
	if (memoForm->selectedText != NULL) {
		delete memoForm->selectedText;

	}
	memoForm->selectedText = new SelectedText;

	//마지막줄로 이동
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(memoForm->text->GetLength() - 1));
	RowInfo rowInfo;
	rowInfo.GetRowInfo(memoForm->row);
	memoForm->row->Move(rowInfo.GetLastIndex());
	//페이퍼 이동
	memoForm->paper->MoveToY(memoForm->paper->GetHeight() - memoForm->screenHeight / memoForm->fontSize*memoForm->fontSize);
	memoForm->selectedText->Select(memoForm,0, 0, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight),true);
}