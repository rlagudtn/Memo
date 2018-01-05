//MoveColumnByStringLength.h
#ifndef _MOVECOLUMNBYSTRINGLENGTH_H
#define _MOVECOLUMNBYSTRINGLENGTH_H
class Row;
class MemoForm;
typedef signed long int Long;
class MoveColumnByStringLength {
public:
	MoveColumnByStringLength();
	MoveColumnByStringLength(const MoveColumnByStringLength& source);
	~MoveColumnByStringLength();
	void MoveColumn(MemoForm *memoForm,Row *row, Long pointX);
};
#endif // _MOVECOLUMNBYSTRINGLENGTH_H
