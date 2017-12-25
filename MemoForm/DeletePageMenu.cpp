//DeletePageMenu.cpp
#include "DeletePageMenu.h"
#include "PageStack.h"
#include "MemoForm.h"
#include "Page.h"
#include "Text.h"	
#include "Row.h"
#include "SingleByteCharacter.h"
DeletePageMenu::DeletePageMenu() {}
DeletePageMenu::~DeletePageMenu() {}

void DeletePageMenu::Implement(MemoForm *memoForm) {
	memoForm->isChanged = true;

	//뒤로 가기에 저장
	memoForm->restoreToRearStack->Push(memoForm->page);
	//입력될때 앞으로 가기 리셋
	if (memoForm->restoreToFrontStack != NULL) {
		delete memoForm->restoreToFrontStack;
	}
	memoForm->restoreToFrontStack = new PageStack;
	//페이지 삭제
	memoForm->page->Delete(memoForm->page->GetCurrent());
	if (memoForm->page->GetCurrent() < memoForm->page->GetLength() - 1) {
		memoForm->page->Move(memoForm->page->GetCurrent() + 1);
	}
	//페이지가 아예 없으면 새로 생성
	if (memoForm->page->GetLength() == 0) {
		Text *text = new Text;
		memoForm->page->Add(text);
		memoForm->text = dynamic_cast<Text*>(memoForm->page->GetAt(memoForm->page->GetCurrent()));
		Row *row = new Row;
		SingleByteCharacter *carriageReturn = new SingleByteCharacter('\r');
		SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
		row->Add(carriageReturn);
		row->Add(lineFeed);
		row->Move(-1);
		memoForm->text->Add(row);
		memoForm->row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));

		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}
}