//FindCurrentTExt.cpp
#include "CurrentPosition.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "ConnectedInfo.h"
CurrentPosition::CurrentPosition(){}
CurrentPosition::CurrentPosition(const CurrentPosition& source){
	this->textIndex = source.textIndex;
	this->rowIndex = source.rowIndex;
}
CurrentPosition::~CurrentPosition(){}
void CurrentPosition::SaveCurrent(MemoForm *memoForm){
	Long i = 0;
	Long k = 0;
	Long currentIndex;
	//자동줄바꿈이 아닐때의 현재 위치를 구한다.
	while (i <= memoForm->text->GetCurrent()) {
		k++;
		ConnectedInfo connectedInfo;
		currentIndex = i;
		i = connectedInfo.GetEndOfConnected(memoForm->text, i)+1;
	}
	//현재 줄 저장
	this->textIndex = k - 1;
	//열 찾기.
	i = currentIndex;
	Long rowIndex = 0;
	while (i < memoForm->text->GetCurrent()) {
		Row *row = dynamic_cast<Row*>(memoForm->text->GetAt(i));
		rowIndex += row->GetLength();
		i++;
	}
	rowIndex += memoForm->row->GetCurrent();
	this->rowIndex = rowIndex;
}
void CurrentPosition::MoveToCurrent(MemoForm *memoForm) {
	Long i = 0;
	Long j = 0;
	//현재행이 속한 연속된 줄의 첫줄을 찾는다.
	while (i < this->textIndex) {
		ConnectedInfo connectedInfo;
		j = connectedInfo.GetEndOfConnected(memoForm->text, j) + 1;
		i++;
	}
	Long currentColumn;
	//열을 찾는다.
	Long stringLength = 0;
	Long previousLength = 0;
	
	while (stringLength<= this->rowIndex) {
		Row *row = dynamic_cast<Row*>(memoForm->text->GetAt(j));
		previousLength = stringLength;
		stringLength+= row->GetLength();
		j++;
	}
	Long currentLine; 
	if (this->rowIndex != -1) {
		currentLine = j - 1;
	}
	else {
		currentLine = j;
	}
	currentColumn = this->rowIndex - previousLength;
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(currentLine));
	memoForm->row->Move(currentColumn);
}