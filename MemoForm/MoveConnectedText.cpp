//MoveConnectedLine.cpp
#include "MoveConnectedText.h"
#include "MemoForm.h"
#include "Paper.h"
#include "Text.h"
#include "Row.h"
#include "SingleByteCharacter.h"
#include "GetString.h"
#include "ConnectedInfo.h"
#include "CutString.h"
#include "CopyToMemo.h"
MoveConnectedText::MoveConnectedText(){}
MoveConnectedText::MoveConnectedText(const MoveConnectedText& source) {}
MoveConnectedText::~MoveConnectedText(){}
Long MoveConnectedText::ChangeLine(MemoForm *memoForm,CDC *dc, Long textIndex,Long rowIndex) {
	//���� ��ġ �޴´�.
	Long currentTextIndex = memoForm->text->GetCurrent();
	Long currentRowIndex = memoForm->row->GetCurrent();
	//if (currentTextIndex == textIndex) {
		GetString currentString;
		CSize size = dc->GetTextExtent(CString(currentString.SubString(memoForm->row, 0, memoForm->row->GetCurrent()).c_str()));
		if (size.cx > memoForm->screenWidth) {
			currentTextIndex = memoForm->text->GetCurrent() + 1;
			currentRowIndex = 0;
		}
	//}
	//������ �̾����ִ��� ���Ѵ�.
	ConnectedInfo connectedInfo;
	Long endRow=connectedInfo.GetEndOfConnected(memoForm->text, textIndex);
	//�̾����ٱ��� �����Ѵ�.
	CutString cutString;
	CString writeAgain = CString(cutString.CutText(memoForm->text,textIndex, rowIndex, endRow, dynamic_cast<Row*>(memoForm->text->GetAt(endRow))->GetLength() - 1).c_str());
	writeAgain.Replace("\r\n", "\r");
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(memoForm->text->GetCurrent()));
	CopyToMemo copyToMemo(dc, memoForm->screenWidth, (LPCTSTR)writeAgain);
	memoForm->text->Accept(&copyToMemo);
	//�������ٿ� \n�߰�
	Long endLine = memoForm->text->GetCurrent();
	Row *row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
	SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
	row->Add(lineFeed);

	//��ġ �̵�
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(currentTextIndex));
	memoForm->row->Move(currentRowIndex);

	return endLine;
}
