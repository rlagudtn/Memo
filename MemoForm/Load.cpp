//Load.cpp
#include "Load.h"
#include "Page.h"
#include "Text.h"
#include "Row.h"
#include "DoubleByteCharacter.h"
#include "SingleByteCharacter.h"
#include <afxwin.h>
#pragma warning(disable:4996)
Load::Load():str(""){
}
Load::Load(CDC *pdc,Long screenWidth,string str):str(str),temp(""){
	this->pdc = pdc;
	this->screenWidth = screenWidth;
}
Load::~Load(){}
void Load::Visit(Page *page) {
	//if(str=='\f')
}
void Load::Visit(Text *text) {
	Long index;
	Row *row = new Row;
	index=text->Add(row);
	this->ifChangeLine = false;
	this->i = 0;
	dynamic_cast<Row*>(text->GetAt(index))->Accept(this);
	while(this->ifChangeLine == true) {
		char alpha[3] = { 0, };
		char alphabet;
		Row *changedLine = new Row;
		if (this->deleteChar[0]& 0x80) {
			strcpy(alpha,this->deleteChar.c_str());
			DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter(alpha);
			changedLine->Add(doubleByteCharacter);
		}
		else {
			alphabet = *this->deleteChar.c_str();
			SingleByteCharacter *singleByteCharacter = new SingleByteCharacter(alphabet);
			changedLine->Add(singleByteCharacter);
		}
		text->Add(changedLine);
		this->temp = this->deleteChar;
		this->ifChangeLine = false;
		dynamic_cast<Row*>(text->GetAt(text->GetCurrent()))->Accept(this);
	}
	
}
void Load::Visit(Row *row) {
	string str_;
	char temp[3] = { 0, };
	char alphabet;
	Long stringLength = 0;
	CSize size;
	while (this->i < this->str.length()&&stringLength<=this->screenWidth) {
		if (str[i] & 0x80) {
			str_ = this->str.substr(i, 2);
			this->temp += str_;
			strcpy(temp, str_.c_str());
			DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter(temp);
			row->Add(doubleByteCharacter);
			this->i += 2;
		}
		else {
			str_ = this->str.substr(i, 1);
			this->temp += str_;
			alphabet=*str_.c_str();
			SingleByteCharacter *singleByteCharacter = new SingleByteCharacter(alphabet);
			row->Add(singleByteCharacter);
			this->i++;
		}
		size = this->pdc->GetTextExtent(CString(this->temp.c_str()));
		stringLength = size.cx;
	}
	//화면의 길이를 넘어선다면
	if (this->i < this->str.length()) {
		this->ifChangeLine = true;
		this->deleteChar = str_;
		row->Delete(row->GetCurrent());
	}
	else {
		SingleByteCharacter *singleByteCharacterCR = new SingleByteCharacter('\r');
		SingleByteCharacter *singleByteCharacterLF = new SingleByteCharacter('\n');
		row->Add(singleByteCharacterCR);
		row->Add(singleByteCharacterLF);
	}
	row->Move(-1);
	
}

void Load::Visit(SingleByteCharacter *singleByteCharacter) {
	Long i;
}
void Load::Visit(DoubleByteCharacter *doubleByteCharacter) {
	Long i;
}
