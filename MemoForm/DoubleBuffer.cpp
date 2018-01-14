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
	//��Ʈ ����
	memoForm->fontSize = dc.GetTextExtent("T").cy;
	memoForm->CreateSolidCaret(1, memoForm->fontSize);
	CDC memDC;
	CBitmap myBitmap;
	CBitmap *pOldBitmap;
	//dc�� �����Ѵ�.
	memDC.CreateCompatibleDC(&dc);
	//��Ʈ�ʿ� �����Ѵ�.
	myBitmap.CreateCompatibleBitmap(&dc, memoForm->screenWidth, memoForm->screenHeight);
	//������ memdc�� ������ ��Ʈ���� �����ϰ� �������� ��Ʈ��.
	pOldBitmap=memDC.SelectObject(&myBitmap);
	memDC.PatBlt(0, 0, memoForm->screenWidth, memoForm->screenHeight, WHITENESS);
	if (memoForm->text->GetLength()*memoForm->fontSize > (memoForm->screenHeight / memoForm->fontSize)*memoForm->fontSize) {
		memoForm->paper->ModifyHeight(memoForm->text->GetLength()*memoForm->fontSize);

	}
	else {
		memoForm->paper->ModifyPaper(memoForm->screenWidth, memoForm->screenHeight / memoForm->fontSize *memoForm->fontSize);
	}
	//���� �������κ��� �����.
	if (memoForm->paper->GetY() + memoForm->screenHeight > memoForm->paper->GetHeight()) {
		memoForm->paper->MoveToY(memoForm->paper->GetHeight() - memoForm->screenHeight / memoForm->fontSize*memoForm->fontSize);
	}
	//�ι�° ȭ�鿡 �׸���.
	PaintVisitor paintVisitor(memoForm, &memDC);
	memoForm->text->Accept(&paintVisitor);
	
	memoForm->scrollInfo.nMax = memoForm->paper->GetHeight() + memoForm->screenHeight%memoForm->fontSize;
	memoForm->SetScrollInfo(SB_VERT, &memoForm->scrollInfo);
	memoForm->SetScrollPos(SB_VERT, memoForm->scrollInfo.nPos);

	//��ũ�� ��ġ ����
	memoForm->scrollPositions[memoForm->page->GetCurrent()] = memoForm->scrollInfo.nPos;
	//�����ϱ������� ���
	if (memoForm->selectedText != NULL) {
		memoForm->selectedText->DrawUnderLine(memoForm,&memDC);
	}
	dc.BitBlt(0, 0, memoForm->screenWidth, memoForm->screenHeight, &memDC, 0, 0, SRCCOPY);

	dc.SelectObject(pOldBitmap);
	//ĳ��
	memoForm->caret->MoveToCurrent(memoForm);
	myBitmap.DeleteObject();
	ReleaseDC(memoForm->GetSafeHwnd(), memDC);
	DeleteDC(memDC);

}