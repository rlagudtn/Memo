//GetString.h

#ifndef _GETSTRING_H
#define _GETSTRING_H
#include <afxwin.h>
#include <string>
#pragma warning(disable:4996)
using namespace std;
class SingleByteCharacter;
class DoubleByteCharacter;
class Row;
class Text;
class CDC;
typedef signed long int Long;
class GetString{
public:
	GetString();
	~GetString();
	string SubString(Row *row,Long start, Long end);
};
#endif // _PAINTVISITOR_H
