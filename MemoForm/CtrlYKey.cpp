//CtrlYKey.cpp
#include "CtrlYKey.h"
#include "MemoForm.h"
#include "Page.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "PageStack.h"
#include <afxwin.h>
CtrlYKey::CtrlYKey() {

}
CtrlYKey::CtrlYKey(const CtrlYKey& source) {

}
CtrlYKey::~CtrlYKey() {

}

void CtrlYKey::Implement(MemoForm *memoForm) {
	if (memoForm->restoreToFrontStack->GetTop() >= 0) {
		//되돌리기 전 상태를 앞으로 되돌리기에 저장
		memoForm->restoreToRearStack->Push(memoForm->page);
		//현재 페이지 삭제
		delete memoForm->page;
		//되돌리기로 현재 페이지로 설정
		memoForm->page = memoForm->restoreToFrontStack->Pop();
		memoForm->text = dynamic_cast<Text*>(memoForm->page->GetAt(memoForm->page->GetCurrent()));
		memoForm->row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
		

		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
}