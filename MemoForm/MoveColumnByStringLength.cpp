//MoveColumnByStringLength.cpp
#include "MoveColumnByStringLength.h"
#include "Row.h"	
#include "Character.h"
#include "SingleByteCharacter.h"
#include "GetString.h"
#include <afxwin.h>
MoveColumnByStringLength::MoveColumnByStringLength(){}
MoveColumnByStringLength::MoveColumnByStringLength(const MoveColumnByStringLength& source){}
MoveColumnByStringLength::~MoveColumnByStringLength(){}
void MoveColumnByStringLength::MoveColumn(Row *row,CDC *pdc, Long pointX) {
	Long i = 0;
	Long previous=0;
	CSize size;
	Long stringLength = 0;
	row->Move(-1);
	while (i < row->GetLength()&&stringLength<pointX) {
		row->Move(i);
		GetString getString;
		size = pdc->GetTextExtent(CString(getString.SubString(row, 0, i).c_str()));
		previous = stringLength;
		stringLength = size.cx;
		i++;
	}
	//마지막문자가 개행문자라면 row이동시킨다.
	Character *character = dynamic_cast<Character*>(row->GetAt(row->GetCurrent()));
	bool isLineFeed = false;
	if (dynamic_cast<SingleByteCharacter*>(character)) {
		if (dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet() == '\n') {
			isLineFeed = true;
		}
	}
	if (isLineFeed == true) {
		row->Move(row->GetLength() - 3);
	}
	//현재 글자의 중간 위치를 구한다.
	float mid = (previous + stringLength) / 2.0F;
	if (pointX < mid) {
		row->Move(row->GetCurrent() - 1);
	}
}