//CopyToMemo.cpp
#include "CopyToMemo.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"	
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "GetString.h"
CopyToMemo::CopyToMemo(){}
CopyToMemo::~CopyToMemo(){}
void CopyToMemo::WriteToMemo(MemoForm *memoForm, string str) {
	//1.현재 줄의 텍스트를 받아온다.-->화면 넘는지 안넘는지 나중에 확인하려고.
	GetString getString;
	string currentString = getString.SubString(memoForm->row, 0, memoForm->row->GetLength() - 1);
	//2.문자열 길이만큼 반복한다
	Long i = 0;
	string str_;
	bool ifMakeRow = false;
	char alpha[3] = { 0, };
	char alphabet;
	DoubleByteCharacter *doubleByteCharacter;
	SingleByteCharacter *singleByteCharacter;
	while (i < str.length()) {
		//문자열 잘라서 현재 줄 텍스트에 연결
		if (str[i] & 0x80) {
			str_= str.substr(i, 2);
			currentString += str_;
		}
		else {
			str_= str.substr(i, 1);
			alphabet = *str_.c_str();
			if (alphabet != '\r'&&alphabet != '\r') {
				currentString += alphabet;
			}
			if (alphabet == '\n') {
				ifMakeRow = true;
			}
		}
		//텍스트 길이 구한다.
		CClientDC dc(memoForm);
		dc.SelectObject(memoForm->font);

		Long stringLength = dc.GetTextExtent(CString(currentString.c_str())).cx;
		if (stringLength > memoForm->screenWidth) {
			memoForm->row->Connect();
			ifMakeRow = true;
		}
		//새줄을 만들어야 된다면 만들고 끼운다.
		if (ifMakeRow == true) {
			memoForm->row = new Row;
			if (memoForm->text->GetCurrent() < memoForm->text->GetLength() - 1) {
				memoForm->text->TakeIn(memoForm->text->GetCurrent() + 1, memoForm->row);
			}
			else {
				memoForm->text->Add(memoForm->row);
			}
			currentString = str_;
			ifMakeRow = false;
		}
		//데이터를 저장한다.
		if (str[i] & 0x80) {
			str_ = str.substr(i, 2);
			//자동으로 줄바꿈할것에 관한 문자열 추가
			strcpy(alpha, str_.c_str());
			doubleByteCharacter = new DoubleByteCharacter(alpha);
			memoForm->row->Add(doubleByteCharacter);
			i += 2;
		}
		else {
			str_ = str.substr(i, 1);
			alphabet = *str_.c_str();
			if (alphabet != '\r'&&alphabet != '\n') {
				singleByteCharacter = new SingleByteCharacter(alphabet);
				memoForm->row->Add(singleByteCharacter);
			}
			i++;
		}
	}




}