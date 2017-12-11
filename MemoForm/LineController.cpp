//LineController.cpp
#include "LineController.h"
#include "MemoForm.h"
#include "LineInfo.h"
#include "Paper.h"
#include "Text.h"
#include "Row.h"
#include "SingleByteCharacter.h"
#include "GetString.h"
#include "ConnectedInfo.h"
#include "SelectedText.h"
#include "EraseSelectedText.h"
#include "CopyToMemo.h"
LineController::LineController(){}
LineController::LineController(const LineController& source) {}
LineController::~LineController(){}
/*void LineController::SetLineInfo(MemoForm *memoForm,CDC *dc) {
	//�����ִ� ���ڵ��� �������� �����Ѵ�.
	Long i = 0;
	while (i < memoForm->text->GetLength()) {
		Row* temp = dynamic_cast<Row*>(memoForm->text->GetAt(i));
		GetString getString(0, temp->GetLength() - 1);
		temp->Accept(&getString);
		Long stringLength = (dc->GetTextExtent(CString(getString.GetStr().c_str()))).cx;
		//ȭ�� ���� �ȳ�����
		bool isOver = false;
		//������
		if (stringLength > memoForm->screenWidth) {
			isOver = true;
		}
		memoForm->lineInfo->Add(isOver);
		i++;
	}
}*/
void LineController::MakeNewLine(MemoForm *memoForm, Long index) {
	Row *newRow = new Row;
	SingleByteCharacter *carriageReturn = new SingleByteCharacter('\r');
	SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
	newRow->Add(carriageReturn);
	newRow->Add(lineFeed);
	newRow->Move(-1);
	if (index < memoForm->text->GetLength() - 1) {
		memoForm->text->TakeIn(index, newRow);
	}
	else {
		memoForm->text->Add(newRow);
	}
	memoForm->row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
}

/*void LineController::AutomaticLineChange(MemoForm *memoForm,CDC *dc) {
	//lineInfo�� length��ŭ �ݺ��ϳ�.
	Long i = memoForm->lineInfo->GetLength()-1;
	while (i >= 0) {
		//ȭ�� ������ �Ѵ´ٸ�
		if (memoForm->lineInfo->GetAt(i) == true) {
			//�ش� �ٰ� ���� �Ǿ��� �ִ� �ٱ��� �����Ѵ�.
			ConnectedInfo connectedInfo;
			Long endOfConnected = connectedInfo.GetEndOfConnected(memoForm->text,i);
			//�����ٺ��� ������ ����.
			SelectedText selectedText(dc, memoForm->paper->GetX(), memoForm->paper->GetY());
			selectedText.SetTextPosition(i, 0, endOfConnected, dynamic_cast<Row*>(memoForm->text->GetAt(endOfConnected))->GetLength() - 1);
			memoForm->text->Accept(&selectedText);
			//���õȺκ������
			EraseSelectedText eraseSelectedText(i, 0, endOfConnected, dynamic_cast<Row*>(memoForm->text->GetAt(endOfConnected))->GetLength() - 1);
			memoForm->text->Accept(&eraseSelectedText);
			//�ٽ�����.
			CString copyText = CString(selectedText.GetBuffer().c_str());
			copyText.Replace("\r\n", "\r");
			CopyToMemo writeAgain(dc,memoForm->screenWidth,(LPCTSTR)copyText);
			memoForm->text->Accept(&writeAgain);
			//���๮�� �߰�
			SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
			dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()))->Add(lineFeed);
			//���� ��ġ ....******************
		}
		i++;
	}
}
*/
/*void LineController::SetLineFeed(Row *row) {
	SingleByteCharacter *carriageReturn = new SingleByteCharacter('\r');
	SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
	row->Add(carriageReturn);
	row->Add(lineFeed);
}*/