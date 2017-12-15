//CtrlLeftArrowKey.cpp
#include "CtrlLeftArrowKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "RowInfo.h"
#include <afxwin.h>
CtrlLeftArrowKey::CtrlLeftArrowKey() {

}
CtrlLeftArrowKey::CtrlLeftArrowKey(const CtrlLeftArrowKey& source) {

}
CtrlLeftArrowKey::~CtrlLeftArrowKey() {

}

void CtrlLeftArrowKey::Implement(MemoForm *memoForm) {
	if (memoForm->selectedText != NULL) {
		delete memoForm->selectedText;
		memoForm->selectedText = NULL;
	}
	bool isStop = false;
	Long firstCurrent = memoForm->row->GetCurrent();
	Long i = memoForm->row->GetCurrent() -1;
	while (i >=0 && isStop == false) {
		memoForm->row->Move(i);
		Character *character = dynamic_cast<Character*>(memoForm->row->GetAt(i));
		if (dynamic_cast<SingleByteCharacter*>(character)) {
			char temp = dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet();
			//sp,],},),,',',>
			if (temp == 0x20 || temp == 0x5B || temp == 0x7B || temp == 0x28 || temp == 0x2C || temp == 0x3C) {
				isStop = true;
				memoForm->row->Move(memoForm->row->GetCurrent() - 1);
			}
		}
		i--;
	}
	//끝열이 아닌곳에서 키가 눌렸을때
	if (memoForm->row->GetCurrent() >=0&&isStop!=true) {
		memoForm->row->Move(-1);
		isStop = true;
	}
	//맨끝열에서 키가 눌렸을때
	else if (memoForm->row->GetCurrent() == -1&&memoForm->row->GetCurrent() == firstCurrent) {
		isStop = false;
	}

	if (isStop == false && memoForm->text->GetCurrent()>0) {
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move((memoForm->text->GetCurrent() -1)));
		RowInfo rowInfo;
		rowInfo.GetRowInfo(memoForm->row);
		memoForm->row->Move(rowInfo.GetLastIndex());
	}
	//캐럿이동
	CClientDC dc(memoForm);
	memoForm->caret->MoveToCurrent(memoForm, &dc);
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
}