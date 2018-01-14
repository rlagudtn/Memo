//DoubleBuffer.cpp
#include "DoubleBuffer.h"
#include "MemoForm.h"
#include "PaintVisitor.h"
#include "Text.h"
#include "Paper.h"
#include "Page.h"
#include "Caret.h"
#include "SelectedText.h"
DoubleBuffer::DoubleBuffer(){}

DoubleBuffer::~DoubleBuffer(){}

void DoubleBuffer::Paint(MemoForm *memoForm) {
	CPaintDC dc(memoForm);
	dc.SelectObject(memoForm->font);
	//폰트 설정
	memoForm->fontSize = dc.GetTextExtent("T").cy;
	memoForm->CreateSolidCaret(1, memoForm->fontSize);
	CDC memDC;
	CBitmap myBitmap;
	CBitmap *pOldBitmap;
	//dc를 복사한다.
	memDC.CreateCompatibleDC(&dc);
	//비트맵에 복사한다.
	myBitmap.CreateCompatibleBitmap(&dc, memoForm->screenWidth, memoForm->screenHeight);
	//복사한 memdc에 복사한 비트맵을 선택하고 리턴으로 비트맵.
	pOldBitmap=memDC.SelectObject(&myBitmap);
	memDC.PatBlt(0, 0, memoForm->screenWidth, memoForm->screenHeight, WHITENESS);
	if (memoForm->text->GetLength()*memoForm->fontSize > (memoForm->screenHeight / memoForm->fontSize)*memoForm->fontSize) {
		memoForm->paper->ModifyHeight(memoForm->text->GetLength()*memoForm->fontSize);

	}
	else {
		memoForm->paper->ModifyPaper(memoForm->screenWidth, memoForm->screenHeight / memoForm->fontSize *memoForm->fontSize);
	}
	//종이 마지막부분을 맞춘다.
	if (memoForm->paper->GetY() + memoForm->screenHeight > memoForm->paper->GetHeight()) {
		memoForm->paper->MoveToY(memoForm->paper->GetHeight() - memoForm->screenHeight / memoForm->fontSize*memoForm->fontSize);
	}
	//두번째 화면에 그린다.
	PaintVisitor paintVisitor(memoForm, &memDC);
	memoForm->text->Accept(&paintVisitor);
	
	memoForm->scrollInfo.nMax = memoForm->paper->GetHeight() + memoForm->screenHeight%memoForm->fontSize;
	memoForm->SetScrollInfo(SB_VERT, &memoForm->scrollInfo);
	memoForm->SetScrollPos(SB_VERT, memoForm->scrollInfo.nPos);

	//스크롤 위치 저장
	memoForm->scrollPositions[memoForm->page->GetCurrent()] = memoForm->scrollInfo.nPos;
	//선택하기있으면 출력
	if (memoForm->selectedText != NULL) {
		memoForm->selectedText->DrawUnderLine(memoForm,&memDC);
	}
	dc.BitBlt(0, 0, memoForm->screenWidth, memoForm->screenHeight, &memDC, 0, 0, SRCCOPY);

	dc.SelectObject(pOldBitmap);
	//캐럿
	memoForm->caret->MoveToCurrent(memoForm);
	myBitmap.DeleteObject();
	ReleaseDC(memoForm->GetSafeHwnd(), memDC);
	DeleteDC(memDC);

}