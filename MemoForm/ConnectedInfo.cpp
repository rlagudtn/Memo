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
	Row *currentLine = dynamic_cast<Row*>(text->GetAt(index));
	this->isConnected = currentLine->GetIsConnected();
	Long i = index+1;
	while (i<text->GetLength()&&this->isConnected == true) {
		Row *row= dynamic_cast<Row*>(text->GetAt(i));
		this->isConnected = row->GetIsConnected();
		i++;
	}
	this->lastConnectedLine = i - 1;
	
	return this->lastConnectedLine;
}
