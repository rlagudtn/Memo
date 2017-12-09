//ConnectedInfo.cpp
#include "ConnectedInfo.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
ConnectedInfo::ConnectedInfo(){}
ConnectedInfo::ConnectedInfo(const ConnectedInfo& source) {
	this->IsConnected = source.IsConnected;
	this->lastConnectedRow = source.lastConnectedRow;
}
ConnectedInfo::~ConnectedInfo() {}

ConnectedInfo& ConnectedInfo::operator=(const ConnectedInfo& source) {
	this->IsConnected = source.IsConnected;
	this->lastConnectedRow = source.lastConnectedRow;

	return *this;
}
ConnectedInfo& ConnectedInfo::GetConnectedInfo(Text *text) {
	this->IsConnected = false;
	Row *currentLine = dynamic_cast<Row*>(text->GetAt(text->GetCurrent()));
	this->lastConnectedRow =currentLine->GetCurrent();
	//�������� ���������ڸ� �޴´�.
	Character *lastCharacter = dynamic_cast<Character*>(currentLine->GetAt(currentLine->GetLength() - 1));
	if (dynamic_cast<SingleByteCharacter*>(lastCharacter)->GetAlphabet()!='\n') {
		this->IsConnected = true;
	}
	//������� �ִ� ���� �ִٸ�.
	if (this->IsConnected == true) {
		Long i =text->GetCurrent();
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
		//�����Ѵ�.
		this->lastConnectedRow=i-1;
	}
	return *this;
}
