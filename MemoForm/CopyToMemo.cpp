//CopyToMemo.cpp
#include "CopyToMemo.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include <afxwin.h>
CopyToMemo::CopyToMemo() :str("") {}

CopyToMemo::CopyToMemo(CDC *pdc,Long screenWidth,string str):str(str){
	this->pdc = pdc;
	this->screenWidth = screenWidth;
	this->stringIndex = 0;
	this->ifMakeRow = false;
}
CopyToMemo::~CopyToMemo(){}
void CopyToMemo::Visit(Text *text) {
	//���� ���ڿ� �ޱ�
	Row *currentRow = dynamic_cast<Row*>(text->GetAt(text->GetCurrent()));
	Long k = 0;
	Character *character;
	while (k < currentRow->GetLength()) {
		character = dynamic_cast<Character*>(currentRow->GetAt(k));
		if (dynamic_cast<SingleByteCharacter*>(character)) {
			dynamic_cast<SingleByteCharacter*>(character)->Accept(this);
		}
		else if (dynamic_cast<DoubleByteCharacter*>(character)) {
			dynamic_cast<DoubleByteCharacter*>(character)->Accept(this);
		}
		k++;
	}


	//���� ���ڿ� ó��
	while (this->stringIndex < this->str.length()) {
		dynamic_cast<Row*>(text->GetAt(text->GetCurrent()))->Accept(this);
		if (this->ifMakeRow == true) {
			Row *row = new Row;
			if (text->GetCurrent() < text->GetLength() - 1) {
				text->TakeIn(text->GetCurrent()+1, row);
			}
			else if (text->GetCurrent() >= text->GetLength() - 1) {
				text->Add(row);
			}
			this->ifMakeRow = false;
			this->currentString = "";
		}
		if (this->ifChangeRow == true) {
			//�ӽ������Ѱ� �ٲ��ٿ� �����ϱ�
			//�� ����
			Row *newRow = new Row;
			//������ ���� �����
			char alpha[3] = { 0, };
			char alphabet;
			if (this->tempChar[0] & 0x80) {
				strcpy(alpha, this->tempChar.c_str());
				DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter(alpha);
				newRow->Add(doubleByteCharacter);
			}
			else {
				alphabet = *this->tempChar.c_str();
				SingleByteCharacter *singleByteCharacter = new SingleByteCharacter(alphabet);
				newRow->Add(singleByteCharacter);
			}
			if (text->GetCurrent() < text->GetLength() - 1) {
				text->TakeIn(text->GetCurrent() + 1, newRow);
			}
			else if (text->GetCurrent() >= text->GetLength() - 1) {
				text->Add(newRow);
			}
			this->currentString = this->tempChar;
			this->ifChangeRow = false;
		}
	}

}
void CopyToMemo::Visit(Row *row) {
	//Long i = 0;
	string str_;
	char alpha[3] = { 0, };
	char alphabet;
	if (this->str[this->stringIndex] & 0x80) {
			str_ = this->str.substr(this->stringIndex, 2);
			//�ڵ����� �ٹٲ��ҰͿ� ���� ���ڿ� �߰�
			this->currentString += str_;
			strcpy(alpha, str_.c_str());
			DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter(alpha);
			if (row->GetCurrent() < row->GetLength() - 1) {
				row->TakeIn(row->GetCurrent() + 1, doubleByteCharacter);
			}
			else if (row->GetCurrent() >= row->GetLength() - 1) {
				row->Add(doubleByteCharacter);
			}
			this->stringIndex += 2;
		}
	else {
		str_ = this->str.substr(this->stringIndex, 1);
		//�ڵ����� �ٹٲ��ҰͿ� ���� ���ڿ� �߰�
		if (*str_.c_str() != '\r'&&*str_.c_str() != '\n') {
			this->currentString += str_;
		}
		alphabet = *str_.c_str();
		SingleByteCharacter *singleByteCharacter = new SingleByteCharacter(alphabet);
		if (row->GetCurrent() < row->GetLength() - 1) {
			row->TakeIn(row->GetCurrent() + 1, singleByteCharacter);
		}
		else if (row->GetCurrent() >= row->GetLength() - 1) {
			row->Add(singleByteCharacter);
		}
		if (*str_.c_str() == '\n') {
			this->ifMakeRow = true;
		}
		this->stringIndex++;
	}
	//��ũ���� �Ѿ����� Ȯ��
	CSize size;
	size = this->pdc->GetTextExtent(CString(this->currentString.c_str()));
	Long stringLength = size.cx;
	if (stringLength > this->screenWidth) {
		this->tempChar = str_;
		row->Delete(row->GetCurrent());
		this->ifChangeRow = true;
	}
	
}
void CopyToMemo::Visit(SingleByteCharacter *singleByteCharacter) {
	if (singleByteCharacter->GetAlphabet() != '\n'&&singleByteCharacter->GetAlphabet() != '\r') {
		this->currentString += singleByteCharacter->GetAlphabet();
	}
}
void CopyToMemo::Visit(DoubleByteCharacter *doubleByteCharacter) {
	if (strcmp(doubleByteCharacter->GetAlphabet(), "") != 0) {
		this->currentString += doubleByteCharacter->GetAlphabet();
	}

}