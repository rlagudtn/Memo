//MoveConnectedLine.cpp
#include "MoveConnectedText.h"
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
MoveConnectedText::MoveConnectedText(){}
MoveConnectedText::MoveConnectedText(const MoveConnectedText& source) {}
MoveConnectedText::~MoveConnectedText(){}
void MoveConnectedText::ChangeLine(MemoForm *memoForm,CDC *dc, Long index) {
	//현재줄 임시 저장
	Long currentText = memoForm->text->GetCurrent();
	Long currentRow = memoForm->row->GetCurrent();
	if (currentText == index) {
		GetString currentString(0, memoForm->row->GetCurrent());
		memoForm->row->Accept(&currentString);
		CSize size = dc->GetTextExtent(CString(currentString.GetStr().c_str()));
		if (size.cx > memoForm->screenWidth) {
			currentText = memoForm->text->GetCurrent() + 1;
			currentRow = 0;
		}
	}
	

	//어디 까지 이어져있는지 구한다.
	ConnectedInfo connectedInfo;
	Long endRow=connectedInfo.GetEndOfConnected(memoForm->text, index);
	//이어진줄까지 선택한다.
	SelectedText selectedText(dc, memoForm->paper->GetX(),memoForm->paper->GetY());
	selectedText.SetTextPosition(index, 0, endRow, dynamic_cast<Row*>(memoForm->text->GetAt(endRow))->GetLength() - 1);
	memoForm->text->Accept(&selectedText);
	//지운다.
	EraseSelectedText eraseText(index, 0, endRow, dynamic_cast<Row*>(memoForm->text->GetAt(endRow))->GetLength() - 1);
	memoForm->text->Accept(&eraseText);
	
	CString writeAgain = CString(selectedText.GetBuffer().c_str());
	writeAgain.Replace("\r\n", "\r");
	CopyToMemo copyToMemo(dc, memoForm->screenWidth, (LPCTSTR)writeAgain);
	memoForm->text->Accept(&copyToMemo);
	//마지막줄에 \n추가
	Row *row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
	SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
	row->Add(lineFeed);

	//현재줄로 다시 이동
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(currentText));
	memoForm->row->Move(currentRow);
}
