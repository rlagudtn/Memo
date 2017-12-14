//DeleteKey.cpp
#include "DeleteKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "MoveConnectedText.h"
#include "LineFeed.h"
#include "SelectedText.h"
#include "RowInfo.h"
#include <afxwin.h>
DeleteKey::DeleteKey() {

}
DeleteKey::DeleteKey(const DeleteKey& source) {

}
DeleteKey::~DeleteKey() {

}

void DeleteKey::Implement(MemoForm *memoForm) {
	if (memoForm->selectedText != NULL) {
		memoForm->selectedText->EraseSelectedText(memoForm);
		delete memoForm->selectedText;
		memoForm->selectedText = NULL;
		//선택된전후를 연결시킨다.
		MoveConnectedText connectText;
		CClientDC dc(memoForm);
		connectText.ChangeLine(memoForm, &dc, memoForm->text->GetCurrent());

	}
	else {
		RowInfo rowInfo;
		rowInfo.GetRowInfo(memoForm->row);
		bool isLastIndex = rowInfo.GetIsLastIndex();
		if (isLastIndex == false) {
			memoForm->row->Delete(memoForm->row->GetCurrent() + 1);
		}
		else {
			memoForm->row->Delete(memoForm->row->GetCurrent() + 1);
			memoForm->row->Delete(memoForm->row->GetCurrent() + 1);
			//다음 줄이랑 합친다
			MoveConnectedText connectText;
			CClientDC dc(memoForm);
			connectText.ChangeLine(memoForm, &dc, memoForm->text->GetCurrent());
		}
	}
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight));
}