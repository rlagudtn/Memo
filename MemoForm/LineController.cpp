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
	
	//lineInfo에 length만큼 반복하낟.
	Long i =0;
	Long textLength = memoForm->text->GetLength();
	while (i<textLength) {
		Row* temp = dynamic_cast<Row*>(memoForm->text->GetAt(i));
		
		//해당줄이 연결되어져 있는지 확인한다.
		ConnectedInfo connectedInfo;
		Long endLine=connectedInfo.GetEndOfConnected(memoForm->text, i);
		bool isConnected = temp->GetIsConnected();
		if (isConnected == true) {
			this->lineInfo->Add(i);
		}
		i = endLine + 1;
	}
	//현재위치ㅣ 저장
	CurrentPosition currentPosition;
	currentPosition.SaveCurrent(memoForm);

	//lineInfo에 해당하는 줄만 바꿔준다.
	i = this->lineInfo->GetLength() - 1;
	while (i >= 0) {
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(this->lineInfo->GetAt(i)));
		memoForm->row->Move(-1);
		MoveConnectedText moveConnectedText;
		moveConnectedText.ChangeLine(memoForm, dc, this->lineInfo->GetAt(i));
		i--;
	}
	//현재위치구하기.
	currentPosition.MoveToCurrent(memoForm);
	//캐럿이동
	memoForm->caret->MoveToCurrent(memoForm);
}

