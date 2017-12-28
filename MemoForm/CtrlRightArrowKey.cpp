//CtrlRightArrowKey.cpp
#include "CtrlRightArrowKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "Character.h"
#include "SingleByteCharacter.h";
#include "DoubleByteCharacter.h"
#include <afxwin.h>
#include <string>	
#pragma warning(disable :4996)
CtrlRightArrowKey::CtrlRightArrowKey() {

}
CtrlRightArrowKey::CtrlRightArrowKey(const CtrlRightArrowKey& source) {

}
CtrlRightArrowKey::~CtrlRightArrowKey() {

}

void CtrlRightArrowKey::Implement(MemoForm *memoForm) {
	if (memoForm->selectedText != NULL) {
		delete memoForm->selectedText;
		memoForm->selectedText = NULL;
	}
	bool isStop =false;
	Long firstCurrent= memoForm->row->GetCurrent();
	Long i = memoForm->row->GetCurrent()+1;
	Long lastIndex = memoForm->row->GetLength() - 1;
	while (i<=lastIndex && isStop==false) {
		Character *character= dynamic_cast<Character*>(memoForm->row->GetAt(i));
		if (dynamic_cast<SingleByteCharacter*>(character)) {
			char temp = dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet();
			//sp,],},),,',',>
			if (temp == 0x20 || temp == 0x5D || temp == 0x7D || temp == 0x29 || temp == 0x2C || temp == 0x3E) {
				isStop = true;
			}
		}
		memoForm->row->Move(i);
		i++;
	}
	//끝열이 아닌곳에서 키가 눌렸을때
	if (memoForm->row->GetCurrent() == lastIndex&&memoForm->row->GetCurrent() != firstCurrent) {
		isStop = true;
	}
	//맨끝열에서 키가 눌렸을때
	else if(memoForm->row->GetCurrent() == lastIndex&&memoForm->row->GetCurrent() == firstCurrent){
		isStop = false;
	}
	
	if (isStop==false&&memoForm->text->GetCurrent()<memoForm->text->GetLength()-1) {
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move((memoForm->text->GetCurrent() + 1)));
		memoForm->row->Move(-1);
	}
	//캐럿이동
	CClientDC dc(memoForm);
	memoForm->caret->MoveToCurrent(memoForm);
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
}