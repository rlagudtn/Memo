//RowInfo.cpp
#include "RowInfo.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "LineFeed.h"
RowInfo::RowInfo(){}
RowInfo::RowInfo(const RowInfo& source) {
	this->lastIndex = source.lastIndex;
	this->lastAlphabet = source.lastAlphabet;
	this->isLastIndex = false;
}
RowInfo::~RowInfo(){}
void RowInfo::GetRowInfo(Row *row) {
	LineFeed lineFeed;
	bool isLineFeed = lineFeed.IsLineFeed(row);
	if (isLineFeed == true) {
		this->lastIndex = row->GetLength() - 3;
	}
	else {
		this->lastIndex = row->GetLength() - 1;
	}
	if (this->lastIndex >= 0) {
		this->lastAlphabet = dynamic_cast<Character*>(row->GetAt(this->lastIndex));
	}
	if (row->GetCurrent() == this->lastIndex) {
		this->isLastIndex = true;
	}
}