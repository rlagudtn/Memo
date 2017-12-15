//CtrlVKey.cpp
#include "CtrlVKey.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "Paper.h"
#include "SelectedText.h"
#include "CutString.h"
#include "LineFeed.h"
#include "ConnectedInfo.h"
#include "CopyToMemo.h"
#include "RowInfo.h"
#include <afxwin.h>
CtrlVKey::CtrlVKey() {

}
CtrlVKey::CtrlVKey(const CtrlVKey& source) {

}
CtrlVKey::~CtrlVKey() {

}

void CtrlVKey::Implement(MemoForm *memoForm) {
	if (memoForm->selectedText != NULL) {
		memoForm->selectedText->EraseSelectedText(memoForm);
		delete memoForm->selectedText;
		memoForm->selectedText = NULL;
	}
	if (IsClipboardFormatAvailable(CF_TEXT)) {
		memoForm->OpenClipboard();
		HANDLE hClipboardData = GetClipboardData(CF_TEXT);
		CString *str = (CString*)GlobalLock(hClipboardData);
		GlobalUnlock(hClipboardData);
		//�ٿ��ֱ� �ϱ� ���� ���õ��� ���� �ؽ�Ʈ���� �����Ѵ�
		ConnectedInfo connectedInfo;
		Long endLine = connectedInfo.GetEndOfConnected(memoForm->text, memoForm->text->GetCurrent());
		//�ڸ���.
		CutString cutString;
		CString cuttedText = CString(cutString.CutText(memoForm, memoForm->text->GetCurrent(), memoForm->row->GetCurrent() + 1, endLine, dynamic_cast<Row*>(memoForm->text->GetAt(endLine))->GetLength() - 1).c_str());
		CClientDC dc(memoForm);
		CopyToMemo copyToMemo(&dc, memoForm->screenWidth, (LPCTSTR)str);
		memoForm->text->Accept(&copyToMemo);
		memoForm->row = dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetCurrent()));
		//�� ��ġ �ӽ�����
		Long textCurrent = memoForm->text->GetCurrent();
		Long rowCurrent = memoForm->row->GetCurrent();
		//�ӽ������� �ؽ�Ʈ�� �ٽ� ���´�.
		cuttedText.Replace("\r\n", "");
		CopyToMemo copyAgain(&dc, memoForm->screenWidth, (LPCTSTR)cuttedText);
		memoForm->text->Accept(&copyAgain);
		//�������� \n �߰�
		LineFeed lineFeed;
		lineFeed.SetLineFeed(memoForm->row);
		//���� ��ġ�� �� ���·� ������
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(textCurrent));
		memoForm->row->Move(rowCurrent);

	}
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);

}