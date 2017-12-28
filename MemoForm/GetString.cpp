//GetString.cpp
#include "GetString.h"
#include"Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Character.h"
#include "Text.h"
#include "Paper.h"
GetString::GetString() {
}
GetString::~GetString() {
}
string GetString::SubString(Row *row, Long start, Long end){
	Long i = start;
	Character *character;
	string str;
	while (i <= end) {
		character = dynamic_cast<Character*>(row->GetAt(i));
		if (dynamic_cast<SingleByteCharacter*>(character)) {
				str += dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet();
		}
		else if (dynamic_cast<DoubleByteCharacter*>(character)) {
			str += dynamic_cast<DoubleByteCharacter*>(character)->GetAlphabet();
		}
		i++;
	}
	return str;
};