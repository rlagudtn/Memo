//MovePreviousPageMenu.cpp
#include "MovePreviousPageMenu.h"
#include "MemoForm.h"
#include "Page.h"
#include "PageStack.h"
#include "Paper.h"
#include "Text.h"
#include "Row.h"
MovePreviousPageMenu::MovePreviousPageMenu() {}
MovePreviousPageMenu::~MovePreviousPageMenu() {}

void MovePreviousPageMenu::Implement(MemoForm *memoForm) {
	if (memoForm->page->GetCurrent() > 0) {
		//뒤로 가기에 저장
		memoForm->restoreToRearStack->Push(memoForm->page);
		//입력될때 앞으로 가기 리셋
		if (memoForm->restoreToFrontStack != NULL) {
			delete memoForm->restoreToFrontStack;
		}
		memoForm->restoreToFrontStack = new PageStack;
		//페이지 이동
		memoForm->text = dynamic_cast<Text*>(memoForm->page->Move(memoForm->page->GetCurrent() - 1));
		memoForm->row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
		//스크롤 위치 변경f
		memoForm->paper->MoveToY(memoForm->scrollPositions[memoForm->page->GetCurrent()]);
		memoForm->scrollInfo.nPos = memoForm->scrollPositions[memoForm->page->GetCurrent()];
		memoForm->SetScrollPos(SB_VERT, memoForm->scrollInfo.nPos);

		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
}