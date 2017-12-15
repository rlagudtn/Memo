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

	//찾기 창에 적힌 글자를 받아와서 keys에 저장한다
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
	//찾기 방향 아래로
	//찾기랑 바꾸기
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
	//i로 돌리면서 같은것이 있는지 확인한다
	bool isEqual = false;
	i = 0;
	Long j;
	Long k;

	//마크할것에 관한 데이터
	Long startRow;
	Long endRow;
	//CString 을 돌면서 텍스트 상의 위치 표시
	Long currentText = memoForm->text->GetCurrent();
	Long currentRow = memoForm->row->GetCurrent();
	CString comparedString;//비교되는 문자
	while (i < text.GetLength() - findString.GetLength() && isEqual == false) {
		k = 0;
		j = i;

		comparedString = "";
		//비교될 문자 합치기
		while (k < findStringLength) {
			//한글
			if (IsDBCSLeadByte(text.GetAt(j))) {
				comparedString += text.Mid(j, 2);
				j += 2;
			}
			else {
				//영어
				comparedString += text.Mid(j, 1);
				j++;
			}
			k++;
		}
		//\r을 만난다면
		if (text.GetAt(i) != '\r'&&text.GetAt(i) != '\n') {
			currentRow++;
		}
		//찾는 문자열과 같다면
		if (comparedString == findString) {
			isEqual = true;
		}

		//\n을 만난다면.
		if (text.GetAt(i) == '\n') {
			currentText++;
			currentRow = -1;//??????????????????
		}
		//더블바이트이면
		if (IsDBCSLeadByte(text.GetAt(i))) {
			i += 2;
		}
		//싱글바이트라면
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
		//현재위치를 옮긴다.
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(currentText));
		memoForm->row->Move(currentRow + findStringLength - 1);

		//스크롤 관련
		Long paperLocation = memoForm->fontSize*(memoForm->text->GetCurrent() + 2) - memoForm->screenHeight / memoForm->fontSize*memoForm->fontSize;
		if (paperLocation > memoForm->paper->GetHeight() - memoForm->screenHeight) {
			paperLocation = memoForm->paper->GetHeight() - memoForm->screenHeight / memoForm->fontSize*memoForm->fontSize;
		}
		if (paperLocation < 0) {
			paperLocation = 0;
		}
		memoForm->paper->MoveToY(paperLocation);

		//마크한다.
		memoForm->selectedText = new SelectedText;
		memoForm->selectedText->Select(memoForm, currentText, currentRow, currentText, currentRow + findStringLength - 1);

		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	}

	if (isEqual == false) {
		CString temp = "'이 존재하지 않습니다.";
		CString print = "'" + findString + temp;
		memoForm->MessageBox((LPCTSTR)print, "메모장", MB_OK);
		delete memoForm->selectedText;
		memoForm->selectedText = NULL;
	}
	
}
void FindReplace::ReplaceString(MemoForm *memoForm) {
	CString replaceString =  memoForm->pDlg->GetReplaceString();
	//선택된 부분이후를 선택하여 임시 저장한다
	if (memoForm->selectedText != NULL) {
		CutString cutString;
		CString buffer =CString(cutString.CutText(memoForm, memoForm->selectedText->GetEndLine(), memoForm->selectedText->GetEndColumn() + 1, memoForm->text->GetLength() - 1, dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetLength() - 1))->GetLength() - 1).c_str());
		//선택된 곳부터 끝까지 다 삭제
		memoForm->selectedText->EraseSelectedText(memoForm);
		delete memoForm->selectedText;
		memoForm->selectedText = NULL;
		
		//바꿀 문자열을 받아온다.
		CClientDC dc(memoForm);
		CopyToMemo copyToMemo(&dc, memoForm->screenWidth, (LPCTSTR)replaceString);
		memoForm->text->Accept(&copyToMemo);

		//임시저장한 뒷부분을 옮겨 적는다.
		Long textCurrent = memoForm->text->GetCurrent();
		Long rowCurrent = memoForm->row->GetCurrent();
		//임시저장한 텍스트를 다시 적는다.
		CopyToMemo copyAgain(&dc, memoForm->screenWidth, (LPCTSTR)buffer);
		memoForm->text->Accept(&copyAgain);
		//현재 위치를 원 상태로 돌린다
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(textCurrent));
		memoForm->row->Move(rowCurrent);
	}
}

void FindReplace::ReplaceAll(MemoForm *memoForm) {
	bool isChanged = false;
	//전체 복사
	CutString cutAll;
	CString text = CString(cutAll.CutText(memoForm, 0, 0, memoForm->text->GetLength() - 1, dynamic_cast<Row*>(memoForm->text->GetAt(memoForm->text->GetLength() - 1))->GetLength() - 1).c_str());
	
	//복사한 스트링을 받는다
	CString buffer;
	CString changeText="";

	//찾을 텍스트,바꿀 텍스트를 받아온다.
	CString findString = memoForm->pDlg->GetFindString();
	//찾을 텍스트의 길이를 받아온다.
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
	//모두 바꾸기 시작
	i = 0;
	Long j;
	Long k;
	Long start = 0;
	Long end;
	CString comparedString;//비교되는 문자
	while (i < text.GetLength() - findString.GetLength() - 1) {
		k = 0;
		j = i;
		comparedString = "";
		//비교될 문자 합치기
		while (k < findStringLength) {
			//한글
			if (IsDBCSLeadByte(text.GetAt(j))) {
				comparedString += text.Mid(j, 2);
				j += 2;
			}
			else {
				//영어
				comparedString += text.Mid(j, 1);
				j++;
			}
			k++;
		}
		//찾는 문자열과 같다면
		if (comparedString == findString) {
			end = i - 1;
			buffer = text.Mid(start, end - start + 1);
			changeText += buffer;
			changeText += replaceString;
			start = i + findString.GetLength();
			//isChanged 바꿔줌
			isChanged = true;
		}
		//더블바이트이면
		if (IsDBCSLeadByte(text.GetAt(j))) {
			i += 2;
		}
		else {
			//영어
			i++;
		}
	}
	end = text.GetLength() - 1;
	buffer = text.Mid(start, end - start + 1);
	changeText += buffer;
	CClientDC dc(memoForm);
	CopyToMemo copyToMemo(&dc, memoForm->screenWidth, (LPCTSTR)changeText);
	memoForm->text->Accept(&copyToMemo);
	//맨앞으로 이동
	memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(0));
	memoForm->row->Move(-1);
	memoForm->paper->MoveToY(0);
	memoForm->caret->Move(0, 0);
	//스크롤
	/*memoForm->scrollInfo.nPos = 0;
	SetScrollInfo(SB_VERT, &memoForm->scrollInfo);*/
	memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
	if (isChanged == false) {
		CString temp = "'이 존재하지 않습니다.";
		CString print = "'" + findString + temp;
		memoForm->MessageBox((LPCTSTR)print, "메모장", MB_OK);
	}


}
