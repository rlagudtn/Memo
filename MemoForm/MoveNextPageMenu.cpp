//MoveNextPageMenu.cpp
#include "MoveNextPageMenu.h"
#include "MemoForm.h"
#include "Page.h"
#include "Paper.h"
#include "PageStack.h"
#include "Text.h"
#include "Row.h"
MoveNextPageMenu::MoveNextPageMenu() {}
MoveNextPageMenu::~MoveNextPageMenu() {}

void MoveNextPageMenu::Implement(MemoForm *memoForm) {

	if (memoForm->page->GetCurrent()  <memoForm->page->GetLength() - 1) {
		//�ڷ� ���⿡ ����
		memoForm->restoreToRearStack->Push(memoForm->page);
		//�Էµɶ� ������ ���� ����
		if (memoForm->restoreToFrontStack != NULL) {
			delete memoForm->restoreToFrontStack;
		}
		memoForm->restoreToFrontStack = new PageStack;
		//������ �̵�
		memoForm->text = dynamic_cast<Text*>(memoForm->page->Move(memoForm->page->GetCurrent() + 1));
		memoForm->row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
		//��ũ�� ��ġ ����
		memoForm->paper->MoveToY(memoForm->scrollPositions[memoForm->page->GetCurrent()]);
		memoForm->scrollInfo.nPos = memoForm->scrollPositions[memoForm->page->GetCurrent()];

		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);

	}
}