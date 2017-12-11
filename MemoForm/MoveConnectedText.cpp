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
	//������ �ӽ� ����
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
	

	//��� ���� �̾����ִ��� ���Ѵ�.
	ConnectedInfo connectedInfo;
	Long endRow=connectedInfo.GetEndOfConnected(memoForm->text, index);
	//�̾����ٱ��� �����Ѵ�.
	SelectedText selectedText(dc, memoForm->paper->GetX(),memoForm->paper->GetY());
	selectedText.SetTextPosition(index, 0, endRow, dynamic_cast<Row*>(memoForm->text->GetAt(endRow))->GetLength() - 1);
	memoForm->text->Accept(&selectedText);
	//�����.
	EraseSelectedText eraseText(index, 0, endRow, dynamic_cast<Row*>(memoForm->text->GetAt(endRow))->GetLength() - 1);
	memoForm->text->Accept(&eraseText);
	
	CString writeAgain = CString(selectedText.GetBuffer().c_str());
	writeAgain.Replace("\r\n", "\r");
	CopyToMemo copyToMemo(dc, memoForm->screenWidth, (LPCTSTR)writeAgain);
	memoForm->text->Accept(&copyToMemo);
	//�������ٿ� \n�߰�
	Row *row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
	SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
	row->Add(lineFeed);

	//�����ٷ� �ٽ� �̵�
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(currentText));
	memoForm->row->Move(currentRow);
}
