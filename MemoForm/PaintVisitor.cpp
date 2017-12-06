//PaintVisitor.cpp
#include "PaintVisitor.h"
#include"Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Character.h"
#include "Text.h"
#include "Paper.h"
#include <afxwin.h>
#include <string>    
using namespace std;
PaintVisitor::PaintVisitor()
	:str("") {
	//this->start = -1;
	//this->end = -1;
}
/*PaintVisitor::PaintVisitor(Long start, Long end)
	: str("") {
	this->start = start;
	this->end = end;
}*/
PaintVisitor::PaintVisitor(CDC *pdc,Long screenHeight,Long paperPosY) : str("") {
	this->pdc = pdc;
	this->screenHeight = screenHeight;
	this->paperPosY = paperPosY;
	this->fontSize = 20;//임의적으로 설정
}

PaintVisitor::~PaintVisitor() {}

void PaintVisitor::Visit(Text *text) {
	Long i = this->paperPosY / this->fontSize;
	Long last = (this->paperPosY + this->screenHeight) / this->fontSize ;
	if (last > text->GetLength()) {
		last = text->GetLength();
	}
	
	Long y = 0;

	while (i < last) {
		text->GetAt(i)->Accept(this);
		//글자 출력
		this->pdc->TextOut(0, y , CString(this->str.c_str()));
		//입력된 글자 사이즈 받아옴
		CSize size = this->pdc->GetTextExtent(CString(this->str.c_str()));
		if (size.cy != 0) {
			this->fontSize = size.cy;
		}
		this->str = "";
		y += this->fontSize;
		i++;
	}
}
void PaintVisitor::Visit(Row *row) {
	Long j = 0;

	while (j < row->GetLength()) {
		Character *character = dynamic_cast<Character*>(row->GetAt(j));
		if (dynamic_cast<SingleByteCharacter*>(character)) {
			(dynamic_cast<SingleByteCharacter*>(character))->Accept(this);

		}
		else if (dynamic_cast<DoubleByteCharacter*>(character)) {
			(dynamic_cast<DoubleByteCharacter*>(character))->Accept(this);
		}

		j++;
	}
	

}

void PaintVisitor::Visit(SingleByteCharacter *singleByteCharacter) {
	//if (singleByteCharacter->GetAlphabet() != '\n'&&singleByteCharacter->GetAlphabet() != '\r') {
		this->str += singleByteCharacter->GetAlphabet();
	//}
}
void PaintVisitor::Visit(DoubleByteCharacter *doubleByteCharacter) {
	if (strcmp(doubleByteCharacter->GetAlphabet(), "") != 0) {
		this->str += doubleByteCharacter->GetAlphabet();
	}
}



