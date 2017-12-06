//EraseSelectedText.cpp
#include "EraseSelectedText.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include <afxwin.h>


EraseSelectedText::EraseSelectedText() {}

EraseSelectedText::EraseSelectedText(Long startRow, Long startColumn, Long endRow, Long endColumn){
	this->startRow = startRow;
	this->startColumn = startColumn;
	this->endRow = endRow;
	this->endColumn = endColumn;
}
EraseSelectedText::~EraseSelectedText(){}

void EraseSelectedText::Visit(Text *text){
	this->ifEraseRow = false;
	this->i = this->endRow;
	while (this->i >= this->startRow) {
		if (this->i == this->endRow || this->i == this->startRow) {
			dynamic_cast<Row*>(text->GetAt(this->i))->Accept(this);
			if (this->ifEraseRow == true) {
				text->Delete(this->i);
				this->ifEraseRow = false;
			}
		}
		//중간줄
		else {
			text->Delete(this->i);
		}
		//시작줄이나 끝줄에서 전부 없어졌을때
		
		this->i--;
	}
	
	//첫줄과 끝줄 잇기
	string str_;
	char alpha[3] = { 0, };
	char alphabet;
	Row *row = dynamic_cast<Row*>(text->GetAt(text->GetCurrent()));
	//현재위치 저장
	Long rowCurrent = row->GetCurrent();
	Long stringIndex = 0;
	while (stringIndex < this->str.length()) {
		if (this->str[stringIndex] & 0x80) {
			str_ = this->str.substr(stringIndex, 2);
			strcpy(alpha, str_.c_str());
			DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter(alpha);
			row->Add(doubleByteCharacter);
			stringIndex += 2;
		}
		else {
			str_ = this->str.substr(stringIndex, 1);
			alphabet = *str_.c_str();
			SingleByteCharacter *singleByteCharacter = new SingleByteCharacter(alphabet);
			row->Add(singleByteCharacter);
			stringIndex++;
		}
	}
	row->Move(rowCurrent);
}
void EraseSelectedText::Visit(Row *row){
	Long i;
	Long last;
	if (this->i == this->startRow&&this->i == this->endRow) {
		i = this->endColumn;
		last = this->startColumn;
	}
	else if (this->i == this->startRow&&this->i != this->endRow) {
		i = row->GetLength() - 1;
		last = this->startColumn;
	}
	else if (this->i == this->endRow&&this->i != this->startRow) {
		i = this->endColumn;
		last = 0;
	}
	while (i >= last) {
		row->Delete(i);
		i--;
	}
	if (row->GetLength() == 0&&this->i != startRow) {
		this->ifEraseRow = true;
	}
	else if (this->i != startRow&&row->GetLength() > 0) {
		Long k = 0;
		Character *character;
		while (k < row->GetLength()) {
			character = dynamic_cast<Character*>(row->GetAt(k));
			if (dynamic_cast<SingleByteCharacter*>(character)) {
				this->str += dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet();
			}
			else if (dynamic_cast<DoubleByteCharacter*>(character)) {
				this->str += dynamic_cast<DoubleByteCharacter*>(character)->GetAlphabet();
			}
			k++;
		}
		this->ifEraseRow = true;
	}
}
void EraseSelectedText::Visit(SingleByteCharacter *singleBytecharacter) { Long i = 0; }
void EraseSelectedText::Visit(DoubleByteCharacter *doubleBytecharacter) { Long i = 0; }