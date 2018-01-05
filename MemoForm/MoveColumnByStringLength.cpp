//MoveColumnByStringLength.cpp
#include "MoveColumnByStringLength.h"
#include "Row.h"	
#include "Character.h"
#include "SingleByteCharacter.h"
#include "GetString.h"
#include "MemoForm.h"
MoveColumnByStringLength::MoveColumnByStringLength(){}
MoveColumnByStringLength::MoveColumnByStringLength(const MoveColumnByStringLength& source){}
MoveColumnByStringLength::~MoveColumnByStringLength(){}
void MoveColumnByStringLength::MoveColumn(MemoForm *memoForm,Row *row, Long pointX) {
	Long i = 0;
	Long previous=0;
	CSize size;
	Long stringLength = 0;
	row->Move(-1);
	CClientDC dc(memoForm);
	dc.SelectObject(memoForm->font);
	Long lastIndex = row->GetLength() - 1;
	while (i <=lastIndex&&stringLength<pointX) {
		row->Move(i);
		GetString getString;
		size = dc.GetTextExtent(CString(getString.SubString(row, 0, i).c_str()));
		previous = stringLength;
		stringLength = size.cx;
		i++;
	}
	
	//현재 글자의 중간 위치를 구한다.
	float mid = (previous + stringLength) / 2.0F;
	if (pointX < mid) {
		row->Move(row->GetCurrent() - 1);
	}
}