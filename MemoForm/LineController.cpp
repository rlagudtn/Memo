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
#include "FindCurrentByString.h"
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
	
	//lineInfo�� length��ŭ �ݺ��ϳ�.
	Long i =0;
	Long textLength = memoForm->text->GetLength();
	while (i<textLength) {
		Row* temp = dynamic_cast<Row*>(memoForm->text->GetAt(i));
		
		GetString getString;
		//������ ���̸� ���Ѵ�.
		Long stringLength = (dc->GetTextExtent(CString(getString.SubString(temp, 0, temp->GetLength() - 1).c_str()))).cx;
		//�ش����� ����Ǿ��� �ִ��� Ȯ���Ѵ�.
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
	//������ġ�� ����
	SelectedText selectedText(dc, memoForm->paper->GetX(), memoForm->paper->GetY());
	selectedText.SetTextPosition(0, 0, memoForm->text->GetCurrent(), memoForm->row->GetCurrent());
	memoForm->text->Accept(&selectedText);
	//lineInfo�� �ش��ϴ� �ٸ� �ٲ��ش�.
	i = this->lineInfo->GetLength() - 1;
	while (i >= 0) {
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(this->lineInfo->GetAt(i)));
		MoveConnectedText moveConnectedText;
		moveConnectedText.ChangeLine(memoForm, dc, this->lineInfo->GetAt(i));
		i--;
	}
	//������ġ���ϱ�.
	FindCurrentByString findCurrent;
	findCurrent.MoveToCurrent(dc, selectedText.GetBuffer(), memoForm->screenWidth);
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(findCurrent.GetTextIndex()));
	memoForm->row->Move(findCurrent.GetRowIndex());
}

void LineController::SetLineFeed(Row *row) {
	Long rowIndex = row->GetCurrent();
	SingleByteCharacter *carriageReturn = new SingleByteCharacter('\r');
	SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
	row->Add(carriageReturn);
	row->Add(lineFeed);
	row->Move(rowIndex);
}