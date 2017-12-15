//ConnectedInfo.cpp
#include "ConnectedInfo.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
ConnectedInfo::ConnectedInfo(){}
ConnectedInfo::ConnectedInfo(const ConnectedInfo& source) {
	this->lastConnectedLine = source.lastConnectedLine;
}
ConnectedInfo::~ConnectedInfo() {}

ConnectedInfo& ConnectedInfo::operator=(const ConnectedInfo& source) {
	this->lastConnectedLine = source.lastConnectedLine;

	return *this;
}
Long ConnectedInfo::GetEndOfConnected(Text *text,Long index) {
	this->isConnected = false;
	Row *currentLine = dynamic_cast<Row*>(text->GetAt(index));
	this->lastConnectedLine =index;
	//현재줄의 마지막글자를 받는다.
	if (currentLine->GetLength() > 0) {
		Character *lastCharacter = dynamic_cast<Character*>(currentLine->GetAt(currentLine->GetLength() - 1));
		if (dynamic_cast<SingleByteCharacter*>(lastCharacter)) {
			if (dynamic_cast<SingleByteCharacter*>(lastCharacter)->GetAlphabet() != '\n') {
				this->isConnected = true;
			}
		}
		else if (dynamic_cast<DoubleByteCharacter*>(lastCharacter)) {
			this->isConnected = true;
		}
	}
	else {
		this->isConnected = true;
	}
	//연결되져 있는 줄이 있다면.
	if (this->isConnected == true) {
		Long i =index+1;
		bool isLineFeed = false;
		Row *row;
		Character *character;
		char alphabet;
		while (isLineFeed != true) {
			row = dynamic_cast<Row*>(text->GetAt(i));
			character = dynamic_cast<Character*>(row->GetAt(row->GetLength() - 1));
			if (dynamic_cast<SingleByteCharacter*>(character)) {
				if (dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet() == '\n') {
					isLineFeed = true;
				}
			}
			i++;
		}
		//저장한다.
		this->lastConnectedLine=i-1;
	}
	return this->lastConnectedLine;
}
