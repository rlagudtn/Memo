//EnterKey.cpp
#include "EnterKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "ConnectedInfo.h"
#include "LineFeed.h"
#include "SelectedText.h"
#include "EraseSelectedText.h"
#include "CutString.h"
#include "LineController.h"
#include "CopyToMemo.h"
#include "RowInfo.h"
#include <afxwin.h>
EnterKey::EnterKey() {

}
EnterKey::EnterKey(const EnterKey& source) {

}
EnterKey::~EnterKey() {

}

void EnterKey::Implement(MemoForm *memoForm) {
	//���õǾ��� �ִ� ���� �ִٸ�
	if (memoForm->selectedText != NULL) {
		//�����.
		EraseSelectedText eraseText(memoForm->selectedText->GetStartLine(), memoForm->selectedText->GetStartColumn(), memoForm->selectedText->GetEndLine(), memoForm->selectedText->GetEndColumn());
		memoForm->text->Accept(&eraseText);
		delete memoForm->selectedText;
		memoForm->selectedText = NULL;
		
	}
	//���� �ٿ� ����Ǿ��� �ִ� ���� �ִ��� Ȯ���Ѵ�.
	ConnectedInfo connectedInfo;
	Long endLine = connectedInfo.GetEndOfConnected(memoForm->text, memoForm->text->GetCurrent());
	//�ڸ���.
	CutString cutString;
	CString cuttedText = CString(cutString.CutText(memoForm, memoForm->text->GetCurrent(), memoForm->row->GetCurrent() + 1, endLine, dynamic_cast<Row*>(memoForm->text->GetAt(endLine))->GetLength() - 1).c_str());
	//���๮�� �߰�
	LineFeed lineFeed;
	lineFeed.SetLineFeed(memoForm->row);
	//���ο� �� ����
	LineController lineController;
	lineController.MakeNewLine(memoForm, memoForm->text->GetCurrent() + 1);
	//current����
	Long textCurrent = memoForm->text->GetCurrent();
	Long rowCurrent = memoForm->row->GetCurrent();
	//�����ߴ� �ؽ�Ʈ�� �ٽ� ���´�.
	CClientDC dc(memoForm);
	cuttedText.Replace("\r\n", "");
	CopyToMemo copyToMemo(&dc, memoForm->screenWidth, (LPCTSTR)cuttedText);
	memoForm->text->Accept(&copyToMemo);
	//�����߰�
	lineFeed.SetLineFeed(dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent())));
	//������ġ ����
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(textCurrent));
	memoForm->row->Move(rowCurrent);
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
}