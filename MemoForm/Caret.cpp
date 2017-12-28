//Caret.cpp
#include "Caret.h"
#include "MemoForm.h"
#include "Row.h"
#include "Text.h"
#include "Paper.h"
#include "GetString.h"
#include "MoveColumnByStringLength.h"
Caret::Caret() {
	this->caretX = 0;
	this->caretY = 0;
}

Caret::Caret(const Caret& source) {
	this->caretX = source.caretX;
	this->caretY= source.caretY;
}

Caret::~Caret() {}

void Caret::Move(Long x, Long y) {

	this->caretX = x;
	this->caretY = y;
}
void Caret::MoveX(Long x) {
	this->caretY = x;
}
void Caret::MoveY(Long y) {
	this->caretY = y;
}
void Caret::MoveToCurrent(MemoForm *memoForm) {
	CClientDC dc(memoForm);
	dc.SelectObject(memoForm->font);
	this->caretY = memoForm->text->GetCurrent()*memoForm->fontSize - memoForm->paper->GetY();
	//caretX��ǥ ���ϱ�
	GetString getStr;
	dc.SelectObject(memoForm->font);
	this->caretX = dc.GetTextExtent(CString(getStr.SubString(memoForm->row,0,memoForm->row->GetCurrent()).c_str())).cx;
	//ĳ�� �����ֱ�
	memoForm->CreateSolidCaret(1, memoForm->fontSize);
	memoForm->SetCaretPos(CPoint(this->caretX, this->caretY));
	memoForm->ShowCaret();
	
}

void Caret::MoveToPoint(MemoForm *memoForm, CDC *dc, CPoint point) {
	dc->SelectObject(memoForm->font);

	//���� ��ġ�� ã�´�.
	Long textCurrent = (memoForm->paper->GetY() + point.y) / memoForm->fontSize;
	if (textCurrent >= memoForm->text->GetLength()) {
		textCurrent = memoForm->text->GetLength() - 1;
	}
	this->caretY = (textCurrent*memoForm->fontSize-memoForm->paper->GetY());

	//�̵�
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(textCurrent));
	//x���̵�
	MoveColumnByStringLength temp;
	temp.MoveColumn(memoForm->row, dc, point.x);
	//caretX��ǥ ���ϱ�
	GetString getStr;
	this->caretX = dc->GetTextExtent(CString(getStr.SubString(memoForm->row, 0, memoForm->row->GetCurrent()).c_str())).cx;
	//ĳ�� �����ֱ�
	memoForm->CreateSolidCaret(1, memoForm->fontSize);
	memoForm->SetCaretPos(CPoint(this->caretX, this->caretY));
	memoForm->ShowCaret();

}

Caret& Caret::operator=(const Caret& source) {
	this->caretX = source.caretX;
	this->caretY = source.caretY;
	return *this;
}