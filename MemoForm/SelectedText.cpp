//SelectedText.cpp
#include "SelectedText.h"
#include "MemoForm.h"
#include "Paper.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "GetString.h"
#include <afxwin.h>
SelectedText::SelectedText():buffer("") {
	this->startLine = -1;
	this->startColumn = -1;
	this->endLine = -1;
	this->endColumn = -1;

}
SelectedText::SelectedText(const SelectedText& source):buffer(source.buffer) {
	this->startLine = source.startLine;
	this->startColumn =source.startColumn;
	this->endLine =source.endLine;
	this->endColumn = source.endColumn;
}
SelectedText::~SelectedText(){}
SelectedText& SelectedText::operator=(const SelectedText& source) {
	this->startLine = source.startLine;
	this->startColumn = source.startColumn;
	this->endLine = source.endLine;
	this->endColumn = source.endColumn;
	this->buffer = source.buffer;
	return *this;
}
string SelectedText::Select(MemoForm *memoForm, Long startLine, Long startColumn, Long endLine, Long endColumn) {
	this->startLine = startLine;
	this->startColumn = startColumn;
	this->endLine = endLine;
	this->endColumn = endColumn;
	this->buffer = "";
	if (this->startLine < this->endLine || this->startColumn <= this->endColumn) {
		Long i = this->startLine;
		Long startRowIndex;
		Long endRowIndex;
		while (i <= this->endLine) {
			Row *row = dynamic_cast<Row*>(memoForm->text->GetAt(i));
			if (i > this->startLine&&i < this->endLine) {
				startRowIndex = 0;
				endRowIndex = row->GetLength() - 1;
			}
			else if (i == this->startLine&&i == this->endLine) {
				startRowIndex = this->startColumn;
				endRowIndex = this->endColumn;
			}
			else if (i == this->startLine&&i != this->endLine) {
				startRowIndex = this->startColumn;
				endRowIndex = row->GetLength() - 1;
			}
			else if (i == this->endLine&&i != this->startLine) {
				startRowIndex = 0;
				endRowIndex = this->endColumn;
			}
			Long j = startRowIndex;
			while (j <= endRowIndex) {
				Character *character = dynamic_cast<Character*>(row->GetAt(j));
				if (dynamic_cast<SingleByteCharacter*>(character)) {
					this->buffer += dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet();
				}
				else if (dynamic_cast<DoubleByteCharacter*>(character)) {
					this->buffer += dynamic_cast<DoubleByteCharacter*>(character)->GetAlphabet();
				}
				j++;
			}
			if (row->GetIsConnected() == false&&i<endLine) {
				buffer += "\r\n";
			}
			i++;
		}

	}
	return this->buffer;
}
void SelectedText::EraseSelectedText(MemoForm *memoForm) {
	Long lastIndex = dynamic_cast<Row*>(memoForm->text->GetAt(this->endLine))->GetLength() - 1;

	Long i = this->endLine;
	while (i >= this->startLine) {
		Row *row = dynamic_cast<Row*>(memoForm->text->Move(i));
		if (i == this->startLine || i == this->endLine) {
			Long startEraseRow;
			Long endEraseRow;
			if (i == this->startLine&&i == endLine) {
				startEraseRow = this->endColumn;
				endEraseRow = this->startColumn;
			}
			else if (i == this->startLine&&i != this->endLine) {
				startEraseRow = row->GetLength() - 1;
				endEraseRow = this->startColumn;
			}
			else if (i == this->endLine&&i != this->startLine) {
				startEraseRow = this->endColumn;
				endEraseRow = 0;
			}
			Long j = startEraseRow;
			while (j >= endEraseRow) {
				row->Delete(j);
				j--;
			}
			if (i != this->startLine&&row->GetLength()<=0) {
				memoForm->text->Delete(i);
			}
		}
		//중간줄일때
		else  {
			memoForm->text->Delete(i);
		}


		i--;
	}
	memoForm->row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));

	if (lastIndex == this->endColumn) {
		memoForm->row->DisConnect();
	}
	else {
		memoForm->row->Connect();
	}

}
bool SelectedText::SetAgainPos(Long previousLine, Long previousColumn, Long currentLine, Long currentColumn) {
	bool isSelectedSection = true;
	//오른쪽 아래 이동에 해당
	if (previousLine < currentLine || (previousLine == currentLine&&previousColumn < currentColumn)) {
		if (currentLine < this->endLine || (currentLine == this->endLine&&currentColumn < this->endColumn)) {
			this->startLine = currentLine;
			this->startColumn = currentColumn+1;
		}
		else if (currentLine > this->endLine || (currentLine == this->endLine&&currentColumn > this->endColumn)) {
			this->endLine = currentLine;
			this->endColumn = currentColumn;
		}
		//같은 위치 일때
		else {
			isSelectedSection = false;
		}
	}
	//왼쪽 위 이동에 해당.
	else if (previousLine > currentLine || (previousLine == currentLine&&previousColumn > currentColumn)) {
		if (currentLine < this->startLine || (currentLine == this->startLine&&currentColumn < this->startColumn-1)) {
			this->startLine = currentLine;
			this->startColumn = currentColumn+1;
		}
		else if (currentLine > this->startLine || (currentLine == this->startLine-1&&currentColumn > this->startColumn-1)) {
			this->endLine = currentLine;
			this->endColumn = currentColumn;
		}
		//같은위치일때
		else  {
			isSelectedSection = false;
		}
	}

		
	return isSelectedSection;
}

void SelectedText::DrawUnderLine(MemoForm *memoForm,CDC *dc) {

	if (this->startLine < this->endLine || this->startColumn <= this->endColumn) {
		Long i = this->startLine;
		Long startRowIndex;
		Long endRowIndex;
		Long left;
		Long right;
		Long top= memoForm->fontSize*this->startLine - memoForm->paper->GetY();
		GetString getString;
		dc->SelectObject(memoForm->font);
		while (i <= this->endLine) {
			Row *row = dynamic_cast<Row*>(memoForm->text->GetAt(i));
			if (i > this->startLine&&i < this->endLine) {
				startRowIndex = 0;
				endRowIndex = row->GetLength() - 1;
				//화면상 위치
				left= 0;
				right = dc->GetTextExtent(CString(getString.SubString(row, 0, row->GetLength() - 1).c_str())).cx;
			}
			else if (i == this->startLine&&i == this->endLine) {
				startRowIndex = this->startColumn;
				endRowIndex = this->endColumn;
			
				left= dc->GetTextExtent(CString(getString.SubString(row, 0,this->startColumn-1).c_str())).cx;
				right=dc->GetTextExtent(CString(getString.SubString(row, 0, this->endColumn).c_str())).cx;
			}
			else if (i == this->startLine&&i != this->endLine) {
				startRowIndex = this->startColumn;
				endRowIndex = row->GetLength() - 1;
				left = dc->GetTextExtent(CString(getString.SubString(row, 0, this->startColumn - 1).c_str())).cx;
				right = dc->GetTextExtent(CString(getString.SubString(row, 0, row->GetLength()-1).c_str())).cx;
			}
			else if (i == this->endLine&&i != this->startLine) {
				startRowIndex = 0;
				endRowIndex = this->endColumn;
				left = 0;
				right = dc->GetTextExtent(CString(getString.SubString(row, 0, this->endColumn).c_str())).cx;
			}
			CRect rect(left, top, right, top+memoForm->fontSize);
			dc->FillSolidRect(&rect, RGB(0, 0, 255));
			dc->SetTextColor(RGB(255, 255, 255));
			dc->DrawText(CString(getString.SubString(row, startRowIndex,endRowIndex).c_str()), rect, DT_VCENTER);

			top += memoForm->fontSize;
			i++;

		}
	}
}