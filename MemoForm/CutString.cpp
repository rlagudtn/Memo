//CutSTring.cpp
#include "CutString.h"
#include "MemoForm.h"
#include "Text.h"
#include "Row.h"
#include "SelectedText.h"
#include "EraseSelectedText.h"
CutString::CutString(){}
CutString::CutString(const CutString& source) {}
CutString::~CutString(){}
string CutString::CutText(MemoForm *memoForm, Long startLine, Long startColumn, Long endLine, Long endColumn) {
	SelectedText selectedText;
	selectedText.Select(memoForm,startLine,startColumn, endLine, endColumn);//
	//뒤의 텍스트를 지운다.
	EraseSelectedText eraseSelectedText(startLine, startColumn, endLine, endColumn);
	memoForm->text->Accept(&eraseSelectedText);
	string buffer=selectedText.GetBuffer();
	return buffer;
}