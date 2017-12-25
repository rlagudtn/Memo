//MakeNewPageMenu.cpp
#include "MakeNewPageMenu.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "Page.h"
#include "Paper.h"
#include "Caret.h"
#include "PageStack.h"
MakeNewPageMenu::MakeNewPageMenu() {}
MakeNewPageMenu::~MakeNewPageMenu() {}

void MakeNewPageMenu::Implement(MemoForm *memoForm) {
	memoForm->isChanged = true;
	//�ڷ� ���⿡ ����
	memoForm->restoreToRearStack->Push(memoForm->page);
	//�Էµɶ� ������ ���� ����
	if (memoForm->restoreToFrontStack != NULL) {
		delete memoForm->restoreToFrontStack;
	}
	memoForm->restoreToFrontStack = new PageStack;
	//�� ������ ����
	Text *text = new Text;
	if (memoForm->page->GetCurrent()<memoForm->page->GetLength() - 1) {
		memoForm->page->TakeIn(memoForm->page->GetCurrent() + 1, text);
	}
	else {
		memoForm->page->Add(text);
	}
	memoForm->text = dynamic_cast<Text*>(memoForm->page->GetAt(memoForm->page->GetCurrent()));
	Row *row = new Row;
	SingleByteCharacter *carriageReturn = new SingleByteCharacter('\r');
	SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
	row->Add(carriageReturn);
	row->Add(lineFeed);
	row->Move(-1);
	memoForm->text->Add(row);
	memoForm->row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
	memoForm->paper->ModifyPaper(memoForm->screenWidth, memoForm->screenHeight);
	memoForm->paper->MoveToY(0);
	//ĳ��
	memoForm->caret->MoveToCurrent(memoForm);
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
}