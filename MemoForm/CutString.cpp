//CutSTring.cpp
#include "CutString.h"
#include "Text.h"
#include "Row.h"
#include "SelectedText.h"
#include "EraseSelectedText.h"
CutString::CutString(){}
CutString::CutString(const CutString& source) {}
CutString::~CutString(){}
string CutString::CutText(Text *text, Long startLine, Long startColumn, Long endLine, Long endColumn) {
	SelectedText selectedText;
	selectedText.SetTextPosition(startLine,startColumn, endLine, endColumn);//
	text->Accept(&selectedText);
	//���� �ؽ�Ʈ�� �����.
	EraseSelectedText eraseSelectedText(startLine, startColumn, endLine, endColumn);
	text->Accept(&eraseSelectedText);
	string buffer=selectedText.GetBuffer();
	return buffer;
}