//GetString.h

#ifndef _GETSTRING_H
#define _GETSTRING_H
#include "Visitor.h"
#include <string>
using namespace std;
class SingleByteCharacter;
class DoubleByteCharacter;
class Row;
class Text;
class CDC;
typedef signed long int Long;
class GetString:public Visitor{
public:
	GetString();
	GetString(CDC *pdc);
	GetString(Long start, Long end);
	~GetString();
	void Visit(Text *text);
	void Visit(Row *row);
	void Visit(SingleByteCharacter *singleByteCharacter);
	void Visit(DoubleByteCharacter *doubleByteCharacter);
	string& GetStr() const;
	Long GetStart() const;
	Long GetEnd() const;
private:
	string str;
	Long start;
	Long end;
	CDC *pdc;
};
inline string& GetString::GetStr() const {
	return const_cast<string&>(this->str);
}
inline Long GetString::GetStart() const {
	return this->start;
}
inline Long GetString::GetEnd() const {
	return this->end;
}



#endif // _PAINTVISITOR_H
