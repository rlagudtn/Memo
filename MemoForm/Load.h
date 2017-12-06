//Load.h
#ifndef _LOAD_H
#define _LOAD_H	
#include "Visitor.h"
#include <string>
using namespace std;
class SingleByteCharacter;
class DoubleByteCharacter;
class Row;
class Text;
class Page;
class CDC;
typedef signed long int Long;
class Load :public Visitor {
public:
	Load();
	Load(CDC *pdc,Long screenWidth,string str);
	~Load();
	void Visit(Page *page);
	void Visit(Text *text);
	void Visit(Row *row);
	void Visit(SingleByteCharacter *singleByteCharacter);
	void Visit(DoubleByteCharacter *doubleByteCharacter);
	string& GetStr() const;
private:
	CDC *pdc;
	Long screenWidth;
	
	string str;
	string temp;//문자열이 스크린 넘는지
	string deleteChar;
	Long i;
	bool ifChangeLine;
};
inline string& Load::GetStr() const {
	return const_cast<string&>(this->str);
}

#endif // !_LOAD_H
