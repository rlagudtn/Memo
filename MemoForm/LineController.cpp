//LineController.cpp
#include "LineController.h"
#include "MemoForm.h"
#include "Paper.h"
#include "Text.h"
#include "Row.h"
#include "SingleByteCharacter.h"
#include "GetString.h"
#include "ConnectedInfo.h"
#include "SelectedText.h"
#include "EraseSelectedText.h"
#include "CopyToMemo.h"
#include "MoveConnectedText.h"
LineController::LineController(){}
LineController::LineController(const LineController& source) {}
LineController::~LineController(){}

void LineController::MakeNewLine(MemoForm *memoForm, Long index) {
	Row *newRow = new Row;
	if (index < memoForm->text->GetLength() - 1) {
		memoForm->text->TakeIn(index, newRow);
	}
	else {
		memoForm->text->Add(newRow);
	}
	memoForm->row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
}

void LineController::AutomaticLineChange(MemoForm *memoForm,CDC *dc) {
	this->lineInfo = new LineInfo;
	//lineInfo�� length��ŭ �ݺ��ϳ�.
	Long i =0;
	while (i<memoForm->text->GetLength()) {
		Row* temp = dynamic_cast<Row*>(memoForm->text->GetAt(i));
		
		GetString getString;
		//������ ���̸� ���Ѵ�.
		Long stringLength = (dc->GetTextExtent(CString(getString.SubString(temp, 0, temp->GetLength() - 1).c_str()))).cx;
		//�ش����� ����Ǿ��� �ִ��� Ȯ���Ѵ�.
		ConnectedInfo connectedInfo;
		connectedInfo.GetEndOfConnected(memoForm->text, i);
		bool isConnected = connectedInfo.GetIsConnected();
		if (stringLength > memoForm->screenWidth || isConnected == true) {
			this->lineInfo->Add(i);
			ConnectedInfo connectedInfo;
			Long endLine = connectedInfo.GetEndOfConnected(memoForm->text,i);
			i = endLine + 1;
		}
		else {
			i++;
		}
	}
	//lineInfo�� �ش��ϴ� �ٸ� �ٲ��ش�.
	//i = this->lineInfo.GetLength() - 1;
	
	
}

void LineController::SetLineFeed(Row *row) {
	Long rowIndex = row->GetCurrent();
	SingleByteCharacter *carriageReturn = new SingleByteCharacter('\r');
	SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
	row->Add(carriageReturn);
	row->Add(lineFeed);
	row->Move(rowIndex);
}