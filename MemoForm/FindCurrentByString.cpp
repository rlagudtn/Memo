//FindCurrentTExt.cpp
#include "FindCurrentByString.h"
FindCurrentByString::FindCurrentByString(){}
FindCurrentByString::FindCurrentByString(const FindCurrentByString& source){}
FindCurrentByString::~FindCurrentByString(){}
void FindCurrentByString::MoveToCurrent(CDC *dc,string text,Long screenWidth) {
	Long i = 0;
	this->textIndex = 0;
	this->rowIndex = -1;
	string lineText;
	string temp;
	while (i < text.length()) {
		bool isLineFeed = false;
		bool ifChangeLine = false;

		//한글일때
		if (text[i] & 0x80) {
			lineText += text.substr(i, 2);
			temp = text.substr(i,2);
			i += 2;
		}
		//영어일때
		else {
			if (text[i] != '\r'&&text[i] != '\n') {
				lineText += text[i];
				temp = text[i];
			}
			else if (text[i] == '\n') {
				isLineFeed = true;
			}
			i++;

		}
		//열 추가
		this->rowIndex++;
		//현재 줄의 길이를 구한다.
		Long stringLength = dc->GetTextExtent(CString(lineText.c_str())).cx;
		if (stringLength > screenWidth) {
			ifChangeLine = true;
		}
		//화면을 넘는다면
		if (ifChangeLine == true) {
			lineText = temp.c_str();
			this->textIndex++;
			this->rowIndex = 0;

		}
		//개행일때
		else if(isLineFeed==true){
			lineText = "";
			this->textIndex++;
			this->rowIndex = -1;

		}
	}

	
}