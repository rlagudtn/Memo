//MoveColumnByStringLength.h
#ifndef _MOVECOLUMNBYSTRINGLENGTH_H
#define _MOVECOLUMNBYSTRINGLENGTH_H
class Row;
class CDC;
typedef signed long int Long;
class MoveColumnByStringLength {
public:
	MoveColumnByStringLength();
	MoveColumnByStringLength(const MoveColumnByStringLength& source);
	~MoveColumnByStringLength();
	void MoveColumn(Row *row,CDC *pdc, Long pointX);
};
#endif // _MOVECOLUMNBYSTRINGLENGTH_H
