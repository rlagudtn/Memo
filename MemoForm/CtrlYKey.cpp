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
		//�ǵ����� �� ���¸� ������ �ǵ����⿡ ����
		memoForm->restoreToRearStack->Push(memoForm->page);
		//���� ������ ����
		delete memoForm->page;
		//�ǵ������ ���� �������� ����
		memoForm->page = memoForm->restoreToFrontStack->Pop();
		memoForm->text = dynamic_cast<Text*>(memoForm->page->GetAt(memoForm->page->GetCurrent()));
		memoForm->row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
		

		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
}