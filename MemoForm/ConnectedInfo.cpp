//ConnectedInfo.cpp
#include "ConnectedInfo.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
ConnectedInfo::ConnectedInfo(){}
ConnectedInfo::ConnectedInfo(const ConnectedInfo& source) {
	this->lastConnectedRow = source.lastConnectedRow;
}
ConnectedInfo::~ConnectedInfo() {}

ConnectedInfo& ConnectedInfo::operator=(const ConnectedInfo& source) {
	this->lastConnectedRow = source.lastConnectedRow;

	return *this;
}
Long ConnectedInfo::GetEndOfConnected(Text *text,Long index) {
	bool isConnected = false;
	Row *currentLine = dynamic_cast<Row*>(text->GetAt(index));
	this->lastConnectedRow =currentLine->GetCurrent();
	//현재줄의 마지막글자를 받는다.
	Character *lastCharacter = dynamic_cast<Character*>(currentLine->GetAt(currentLine->GetLength() - 1));
	if (dynamic_cast<SingleByteCharacter*>(lastCharacter)->GetAlphabet()!='\n') {
		isConnected = true;
	}
	//연결되져 있는 줄이 있다면.
	if (isConnected == true) {
		Long i =index;
		bool isLineFeed = false;
		Row *row;
		Character *character;
		char alphabet;
		while (isLineFeed != true) {
			row = dynamic_cast<Row*>(text->GetAt(i));
			character = dynamic_cast<Character*>(row->GetAt(row->GetLength() - 1));
			if (dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet()=='\n') {
				isLineFeed = true;
			}
			i++;
		}
		//저장한다.
		this->lastConnectedRow=i-1;
	}
	return this->lastConnectedRow;
}
