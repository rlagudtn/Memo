//GetString.cpp
#include "GetString.h"
#include"Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Character.h"
#include "Text.h"
#include "Paper.h"
#include <afxwin.h>
#include <string>	
using namespace std;
GetString::GetString()
:str("") {
	this->start = -1;
	this->end = -1;
}
GetString::GetString(Long start, Long end)
:str(""){
	this->start = start;
	this->end = end;
}
GetString::GetString(CDC *pdc):str(""){
	this->pdc = pdc;
}

GetString::~GetString() {}

void GetString::Visit(Text *text) {

}
void GetString::Visit(Row *row) {
	Long i = this->start;

	while (i <= this->end) {
		Character *character = dynamic_cast<Character*>(row->GetAt(i));
		if (dynamic_cast<SingleByteCharacter*>(character)) {
			(dynamic_cast<SingleByteCharacter*>(character))->Accept(this);

		}
		else if (dynamic_cast<DoubleByteCharacter*>(character)) {
			(dynamic_cast<DoubleByteCharacter*>(character))->Accept(this);
		}

		i++;
	}

}

void GetString::Visit(SingleByteCharacter *singleByteCharacter) {
	//ÄÜ¼Ö:cout << singleByteCharacter->GetAlphabet() ;
	if (singleByteCharacter->GetAlphabet() != '\r'&&singleByteCharacter->GetAlphabet() != '\n') {
		this->str += singleByteCharacter->GetAlphabet();
	}
}
void GetString::Visit(DoubleByteCharacter *doubleByteCharacter) {
	if (strcmp(doubleByteCharacter->GetAlphabet(), "") !=0 ) {
		this->str += doubleByteCharacter->GetAlphabet();
	}
}



