//SelectedText.cpp
#include "SelectedText.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include <afxwin.h>
SelectedText::SelectedText() {
	this->pdc = NULL;
	this->isPaint = false;
	this->startRow = -1;
	this->startColumn = -1;
	this->endRow = -1;
	this->endColumn = -1;
	this->startX = 0;
	this->startY = 0;
	this->endX = 0;
	this->endY = 0;
}
SelectedText::SelectedText(CDC *pdc,Long paperX,Long paperY):str(""),buffer("") {
	this->isPaint = false;
	this->pdc = pdc;
	this->paperX = paperX;
	this->paperY = paperY;
	this->startRow = -1;
	this->startColumn = -1;
	this->endRow = -1;
	this->endColumn = -1;
	this->startX = 0;
	this->startY = 0;
	this->endX = 0;
	this->endY = 0;
	this->font = 20;//짜맞춘것임.
}

SelectedText::~SelectedText(){}
void SelectedText::SetTextPosition(Long startRow, Long startColumn, Long endRow, Long endColumn) {
	this->startRow = startRow;
	this->startColumn = startColumn;
	this->endRow = endRow;
	this->endColumn = endColumn;
	this->buffer = "";
}
void SelectedText::SetInfoPosition(CDC *dc,bool isPaint,Long paperX, Long paperY) {
	this->isPaint = isPaint;
	this->pdc = dc;
	this->paperX = paperX;
	this->paperY = paperY;
}

void SelectedText::Visit(Text *text) {
	//위치 구하기
	if (this->pdc != NULL) {
		Row *row_ = dynamic_cast<Row*>(text->GetAt(this->startRow));
		Character *character;

		Long k = 0;
		string startString = "";
		while (k <= this->startColumn - 1) {
			character = dynamic_cast<Character*>(row_->GetAt(k));
			if (dynamic_cast<SingleByteCharacter*>(character)) {
				startString += dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet();
			}
			else if (dynamic_cast<DoubleByteCharacter*>(character)) {
				startString += dynamic_cast<DoubleByteCharacter*>(character)->GetAlphabet();
			}
			k++;
		}
		CSize size = this->pdc->GetTextExtent(startString.c_str(), startString.length());
		this->startX = size.cx;
		if (size.cy != 0) {
			this->font = size.cy;
		}
		this->startY = font *this->startRow - paperY;
		//마지막

		string endString = "";
		row_ = dynamic_cast<Row*>(text->GetAt(this->endRow));
		k = 0;
		while (k <= this->endColumn) {
			character = dynamic_cast<Character*>(row_->GetAt(k));
			if (dynamic_cast<SingleByteCharacter*>(character)) {
				endString += dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet();
			}
			else if (dynamic_cast<DoubleByteCharacter*>(character)) {
				endString += dynamic_cast<DoubleByteCharacter*>(character)->GetAlphabet();
			}
			k++;
		}

		size = this->pdc->GetTextExtent(endString.c_str(), endString.length());
		this->endX = size.cx;
		if (size.cy != 0) {
			this->font = size.cy;
		}
		endY = font *this->endRow - this->paperY;

	}
	this->i = this->startRow;
	this->top = this->startY;
	while (i <=this->endRow ) {
		
		dynamic_cast<Row*>(text->GetAt(i))->Accept(this);
		this->str = "";
		
		this->i++;
	}
}
void SelectedText::Visit(Row *row) {
	Character *character;
	Long j;
	Long last;
	Long left;
	Long right;
	Long top;
	Long bottom;
	if (this->i > this->startRow&&this->i < this->endRow) {
		j = 0;
		last = row->GetLength() - 1;

	}
	else if (this->i == this->startRow&&this->i == this->endRow) {
		j = this->startColumn;
		last = this->endColumn;
	}
	else if (this->i == this->startRow&&this->i != this->endRow) {
		j = this->startColumn;
		last = row->GetLength() - 1;
	}
	else if (this->i == this->endRow&&this->i != this->startRow) {
		j = 0;
		last = this->endColumn;
	}
	//문자열 받아오기
	while (j <= last) {
		character = dynamic_cast<Character*>(row->GetAt(j));
		if (dynamic_cast<SingleByteCharacter*>(character)) {
			dynamic_cast<SingleByteCharacter*>(character)->Accept(this);
		}
		else if (dynamic_cast<DoubleByteCharacter*>(character)) {
			dynamic_cast<DoubleByteCharacter*>(character)->Accept(this);
		}
		j++;
	}
	if (this->isPaint==true) {
		//문자열 사이즈 구하기
		CSize size = this->pdc->GetTextExtent(this->str.c_str(), this->str.length());
		//사각형 위치 설정
		//중간줄 left,right
		if (this->i > this->startRow&&this->i < this->endRow) {
			left = 0;
			right = size.cx;

		}
		//줄한칸 left right
		else if (this->i == this->startRow&&this->i == this->endRow) {
			left = this->startX;
			right = this->endX;
		}
		//처음줄 left,right
		else if (this->i == this->startRow&&this->i != this->endRow) {
			left = this->startX;
			right = left + size.cx;
		}
		//마지막줄 left,right
		else if (this->i == this->endRow&&this->i != this->startRow) {
			left = 0;
			right = this->endX;
		}

		if (size.cy != 0) {
			this->font = size.cy;
		}

		top = this->top;
		bottom = this->top + font;
		CRect rect(left, top, right, bottom);
		this->pdc->FillSolidRect(&rect, RGB(0, 0, 255));
		this->pdc->SetTextColor(RGB(255, 255, 255));
		if (this->isPaint == true) {
			this->pdc->DrawText(CString(this->str.c_str()), rect, DT_VCENTER);
		}

		this->top = this->top + font;
	}

}

void SelectedText::Visit(SingleByteCharacter *singleByteCharacter) {
	if (singleByteCharacter->GetAlphabet() != '\n'&&singleByteCharacter->GetAlphabet() != '\r') {
		this->str += singleByteCharacter->GetAlphabet();
	}
	//if (this->i != this->endRow||singleByteCharacter->GetAlphabet()!='\n') {
		this->buffer += singleByteCharacter->GetAlphabet();
	//}
}
void SelectedText::Visit(DoubleByteCharacter *doubleByteCharacter) {
	if (strcmp(doubleByteCharacter->GetAlphabet(), "") != 0) {
		this->str += doubleByteCharacter->GetAlphabet();
		this->buffer += doubleByteCharacter->GetAlphabet();;
	}
}
