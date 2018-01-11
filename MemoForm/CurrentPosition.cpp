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
	//�ڵ��ٹٲ��� �ƴҶ��� ���� ��ġ�� ���Ѵ�.
	while (i <= memoForm->text->GetCurrent()) {
		k++;
		ConnectedInfo connectedInfo;
		currentIndex = i;
		i = connectedInfo.GetEndOfConnected(memoForm->text, i)+1;
	}
	//���� �� ����
	this->textIndex = k - 1;
	//�� ã��.
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
	//�������� ���� ���ӵ� ���� ù���� ã�´�.
	while (i < this->textIndex) {
		ConnectedInfo connectedInfo;
		j = connectedInfo.GetEndOfConnected(memoForm->text, j) + 1;
		i++;
	}
	Long currentColumn;
	//���� ã�´�.
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