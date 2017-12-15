//FindReplace.cpp
#include "FindReplace.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "Paper.h"
#include "Caret.h"
#include "CutString.h"
#include "SelectedText.h"
#include "GetString.h"
#include "CopyToMemo.h"
FindReplace::FindReplace(){

}
FindReplace::~FindReplace() {

}
void FindReplace::FindString(MemoForm *memoForm) {

	//ã�� â�� ���� ���ڸ� �޾ƿͼ� keys�� �����Ѵ�
	CString findString = memoForm->pDlg->GetFindString();
	Long i = 0;
	Long findStringLength = 0;
	while (i < findString.GetLength()) {
		if (IsDBCSLeadByte(findString.GetAt(i))) {
			i += 2;
		}
		else {
			i++;
		}
		findStringLength++;
	}

	CClientDC dc(memoForm);
	CSize size_;
	//ã�� ���� �Ʒ���
	//ã��� �ٲٱ�
	CString buffer;
	Row *row;
	CString text;
	Long startColumn;
	Long endColumn;
	Long afterTextRow = memoForm->text->GetCurrent();
	while (afterTextRow < memoForm->text->GetLength()) {
		row = dynamic_cast<Row*>(memoForm->text->GetAt(afterTextRow));
		if (afterTextRow != memoForm->text->GetCurrent()) {
			startColumn = 0;
		}
		else {
			startColumn = row->GetCurrent() + 1;
		}
		endColumn = row->GetLength() - 1;
		GetString getString;
		text += CString(getString.SubString(row, startColumn, endColumn).c_str());
		text += "\r\n";
		afterTextRow++;
	}
	//i�� �����鼭 �������� �ִ��� Ȯ���Ѵ�
	bool isEqual = false;
	i = 0;
	Long j;
	Long k;

	//��ũ�ҰͿ� ���� ������
	Long startRow;
	Long endRow;
	//CString �� ���鼭 �ؽ�Ʈ ���� ��ġ ǥ��
	Long currentText = memoForm->text->GetCurrent();
	Long currentRow = memoForm->row->GetCurrent();
	CString comparedString;//�񱳵Ǵ� ����
	while (i < text.GetLength() - findString.GetLength() && isEqual == false) {
		k = 0;
		j = i;

		comparedString = "";
		//�񱳵� ���� ��ġ��
		while (k < findStringLength) {
			//�ѱ�
			if (IsDBCSLeadByte(text.GetAt(j))) {
				comparedString += text.Mid(j, 2);
				j += 2;
			}
			else {
				//����
				comparedString += text.Mid(j, 1);
				j++;
			}
			k++;
		}
		//\r�� �����ٸ�
		if (text.GetAt(i) != '\r'&&text.GetAt(i) != '\n') {
			currentRow++;
		}
		//ã�� ���ڿ��� ���ٸ�
		if (comparedString == findString) {
			isEqual = true;
		}

		//\n�� �����ٸ�.
		if (text.GetAt(i) == '\n') {
			currentText++;
			currentRow = -1;//??????????????????
		}
		//�������Ʈ�̸�
		if (IsDBCSLeadByte(text.GetAt(i))) {
			i += 2;
		}
		//�̱۹���Ʈ���
		else {
			i++;
		}
	}
	if (isEqual == true) {
		if (memoForm->selectedText != NULL) {
			delete memoForm->selectedText;
			memoForm->selectedText = NULL;
		}
		startRow = currentText;
		endRow = currentText;
		startColumn = currentRow;
		endColumn = currentRow + findStringLength - 1;
		//������ġ�� �ű��.
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(currentText));
		memoForm->row->Move(currentRow + findStringLength - 1);

		//��ũ�� ����
		Long paperLocation = memoForm->fontSize*(memoForm->text->GetCurrent() + 2) - memoForm->screenHeight / memoForm->fontSize*memoForm->fontSize;
		if (paperLocation > memoForm->paper->GetHeight() - memoForm->screenHeight) {
			paperLocation = memoForm->paper->GetHeight() - memoForm->screenHeight / memoForm->fontSize*memoForm->fontSize;
		}
		if (paperLocation < 0) {
			paperLocation = 0;
		}
		memoForm->paper->MoveToY(paperLocation);

		//��ũ�Ѵ�.
		memoForm->selectedText = new SelectedText;
		memoForm->selectedText->Select(memoForm, currentText, currentRow, currentText, currentRow + findStringLength - 1);

		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}

	if (isEqual == false) {
		CString temp = "'�� �������� �ʽ��ϴ�.";
		CString print = "'" + findString + temp;
		memoForm->MessageBox((LPCTSTR)print, "�޸���", MB_OK);
		delete memoForm->selectedText;
		memoForm->selectedText = NULL;
	}
	
}
void FindReplace::ReplaceString(MemoForm *memoForm) {
	CString replaceString =  memoForm->pDlg->GetReplaceString();
	//���õ� �κ����ĸ� �����Ͽ� �ӽ� �����Ѵ�
	if (memoForm->selectedText != NULL) {
		CutString cutString;
		CString buffer =CString(cutString.CutText(memoForm, memoForm->selectedText->GetEndLine(), memoForm->selectedText->GetEndColumn() + 1, memoForm->text->GetLength() - 1, dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetLength() - 1))->GetLength() - 1).c_str());
		//���õ� ������ ������ �� ����
		memoForm->selectedText->EraseSelectedText(memoForm);
		delete memoForm->selectedText;
		memoForm->selectedText = NULL;
		
		//�ٲ� ���ڿ��� �޾ƿ´�.
		CClientDC dc(memoForm);
		CopyToMemo copyToMemo(&dc, memoForm->screenWidth, (LPCTSTR)replaceString);
		memoForm->text->Accept(&copyToMemo);

		//�ӽ������� �޺κ��� �Ű� ���´�.
		Long textCurrent = memoForm->text->GetCurrent();
		Long rowCurrent = memoForm->row->GetCurrent();
		//�ӽ������� �ؽ�Ʈ�� �ٽ� ���´�.
		CopyToMemo copyAgain(&dc, memoForm->screenWidth, (LPCTSTR)buffer);
		memoForm->text->Accept(&copyAgain);
		//���� ��ġ�� �� ���·� ������
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(textCurrent));
		memoForm->row->Move(rowCurrent);
	}
}

void FindReplace::ReplaceAll(MemoForm *memoForm) {
	bool isChanged = false;
	//��ü ����
	CutString cutAll;
	CString text = CString(cutAll.CutText(memoForm, 0, 0, memoForm->text->GetLength() - 1, dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetLength() - 1))->GetLength() - 1).c_str());
	
	//������ ��Ʈ���� �޴´�
	CString buffer;
	CString changeText="";

	//ã�� �ؽ�Ʈ,�ٲ� �ؽ�Ʈ�� �޾ƿ´�.
	CString findString = memoForm->pDlg->GetFindString();
	//ã�� �ؽ�Ʈ�� ���̸� �޾ƿ´�.
	Long findStringLength = 0;
	Long i = 0;
	while (i < findString.GetLength()) {
		if (IsDBCSLeadByte(findString.GetAt(i))) {
			i += 2;
		}
		else {
			i++;
		}
		findStringLength++;
	}
	CString replaceString = memoForm->pDlg->GetReplaceString();
	//��� �ٲٱ� ����
	i = 0;
	Long j;
	Long k;
	Long start = 0;
	Long end;
	CString comparedString;//�񱳵Ǵ� ����
	while (i < text.GetLength() - findString.GetLength() - 1) {
		k = 0;
		j = i;
		comparedString = "";
		//�񱳵� ���� ��ġ��
		while (k < findStringLength) {
			//�ѱ�
			if (IsDBCSLeadByte(text.GetAt(j))) {
				comparedString += text.Mid(j, 2);
				j += 2;
			}
			else {
				//����
				comparedString += text.Mid(j, 1);
				j++;
			}
			k++;
		}
		//ã�� ���ڿ��� ���ٸ�
		if (comparedString == findString) {
			end = i - 1;
			buffer = text.Mid(start, end - start + 1);
			changeText += buffer;
			changeText += replaceString;
			start = i + findString.GetLength();
			//isChanged �ٲ���
			isChanged = true;
		}
		//�������Ʈ�̸�
		if (IsDBCSLeadByte(text.GetAt(j))) {
			i += 2;
		}
		else {
			//����
			i++;
		}
	}
	end = text.GetLength() - 1;
	buffer = text.Mid(start, end - start + 1);
	changeText += buffer;
	CClientDC dc(memoForm);
	CopyToMemo copyToMemo(&dc, memoForm->screenWidth, (LPCTSTR)changeText);
	memoForm->text->Accept(&copyToMemo);
	//�Ǿ����� �̵�
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(0));
	memoForm->row->Move(-1);
	memoForm->paper->MoveToY(0);
	memoForm->caret->Move(0, 0);
	//��ũ��
	/*memoForm->scrollInfo.nPos = 0;
	SetScrollInfo(SB_VERT, &memoForm->scrollInfo);*/
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	if (isChanged == false) {
		CString temp = "'�� �������� �ʽ��ϴ�.";
		CString print = "'" + findString + temp;
		memoForm->MessageBox((LPCTSTR)print, "�޸���", MB_OK);
	}


}
