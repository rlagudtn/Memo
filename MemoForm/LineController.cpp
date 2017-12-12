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
#include "CutString.h"
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
	if (this->lineInfo != NULL) {
		delete this->lineInfo;
		this->lineInfo=NULL;
	}
	this->lineInfo = new LineInfo;
	
	//lineInfo에 length만큼 반복하낟.
	Long i =0;
	while (i<memoForm->text->GetLength()) {
		Row* temp = dynamic_cast<Row*>(memoForm->text->GetAt(i));
		
		GetString getString;
		//라인의 길이를 구한다.
		Long stringLength = (dc->GetTextExtent(CString(getString.SubString(temp, 0, temp->GetLength() - 1).c_str()))).cx;
		//해당줄이 연결되어져 있는지 확인한다.
		ConnectedInfo connectedInfo;
		Long endLine=connectedInfo.GetEndOfConnected(memoForm->text, i);
		bool isConnected = connectedInfo.GetIsConnected();
		if (stringLength > memoForm->screenWidth || isConnected == true) {
			this->lineInfo->Add(i);
			
			i = endLine + 1;
		}
		else {
			i++;
		}
	}
	
	
	//lineInfo에 해당하는 줄만 바꿔준다.
	//i = thi->lineInfo.GetLength() - 1;
	
	
}

void LineController::SetLineFeed(Row *row) {
	Long rowIndex = row->GetCurrent();
	SingleByteCharacter *carriageReturn = new SingleByteCharacter('\r');
	SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
	row->Add(carriageReturn);
	row->Add(lineFeed);
	row->Move(rowIndex);
}