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
	//1.���� ���� �ؽ�Ʈ�� �޾ƿ´�.-->ȭ�� �Ѵ��� �ȳѴ��� ���߿� Ȯ���Ϸ���.
	GetString getString;
	string currentString = getString.SubString(memoForm->row, 0, memoForm->row->GetLength() - 1);
	//2.���ڿ� ���̸�ŭ �ݺ��Ѵ�
	Long i = 0;
	string str_;
	bool ifMakeRow = false;
	char alpha[3] = { 0, };
	char alphabet;
	DoubleByteCharacter *doubleByteCharacter;
	SingleByteCharacter *singleByteCharacter;
	while (i < str.length()) {
		//���ڿ� �߶� ���� �� �ؽ�Ʈ�� ����
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
		//�ؽ�Ʈ ���� ���Ѵ�.
		CClientDC dc(memoForm);
		dc.SelectObject(memoForm->font);

		Long stringLength = dc.GetTextExtent(CString(currentString.c_str())).cx;
		if (stringLength > memoForm->screenWidth) {
			memoForm->row->Connect();
			ifMakeRow = true;
		}
		//������ ������ �ȴٸ� ����� �����.
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
		//�����͸� �����Ѵ�.
		if (str[i] & 0x80) {
			str_ = str.substr(i, 2);
			//�ڵ����� �ٹٲ��ҰͿ� ���� ���ڿ� �߰�
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