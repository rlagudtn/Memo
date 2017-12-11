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
	//���������ڰ� ���๮�ڶ�� row�̵���Ų��.
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
	//���� ������ �߰� ��ġ�� ���Ѵ�.
	float mid = (previous + stringLength) / 2.0F;
	if (pointX < mid) {
		row->Move(row->GetCurrent() - 1);
	}
}