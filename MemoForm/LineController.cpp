//LineController.cpp
#include "LineController.h"
#include "MemoForm.h"
#include "Paper.h"
#include "Text.h"
#include "Row.h"
#include "SingleByteCharacter.h"
#include "GetString.h"
#include "SelectedText.h"
#include "ConnectedInfo.h"
#include "CopyToMemo.h"
#include "MoveConnectedText.h"
#include "CutString.h"
#include "CurrentPosition.h"
#include "Caret.h"
LineController::LineController(){}
LineController::LineController(const LineController& source) {}
LineController::~LineController(){}

void LineController::MakeNewLine(MemoForm *memoForm, Long index) {
	Row *newRow = new Row;
	if (index < memoForm->text->GetLength() ) {
		memoForm->text->TakeIn(index, newRow);
	}
	else {
		memoForm->text->Add(newRow);
	}
	memoForm->row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
}

void LineController::AutomaticLineChange(MemoForm *memoForm,CDC *dc) {
	if (this->lineInfo != NULL) {
		delete this->lineInfo;
		this->lineInfo=NULL;
	}
	this->lineInfo = new LineInfo;
	
	//lineInfo�� length��ŭ �ݺ��ϳ�.
	Long i =0;
	Long textLength = memoForm->text->GetLength();
	while (i<textLength) {
		Row* temp = dynamic_cast<Row*>(memoForm->text->GetAt(i));
		
		//�ش����� ����Ǿ��� �ִ��� Ȯ���Ѵ�.
		ConnectedInfo connectedInfo;
		Long endLine=connectedInfo.GetEndOfConnected(memoForm->text, i);
		bool isConnected = temp->GetIsConnected();
		if (isConnected == true) {
			this->lineInfo->Add(i);
		}
		i = endLine + 1;
	}
	//������ġ�� ����
	CurrentPosition currentPosition;
	currentPosition.SaveCurrent(memoForm);

	//lineInfo�� �ش��ϴ� �ٸ� �ٲ��ش�.
	i = this->lineInfo->GetLength() - 1;
	while (i >= 0) {
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(this->lineInfo->GetAt(i)));
		memoForm->row->Move(-1);
		MoveConnectedText moveConnectedText;
		moveConnectedText.ChangeLine(memoForm, dc, this->lineInfo->GetAt(i));
		i--;
	}
	//������ġ���ϱ�.
	currentPosition.MoveToCurrent(memoForm);
	//ĳ���̵�
	memoForm->caret->MoveToCurrent(memoForm);
}

