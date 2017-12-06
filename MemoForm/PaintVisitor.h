//PaintVisitor.h

#ifndef _PAINTVISITOR_H
#define _PAINTVISITOR_H
#include "Visitor.h"
#include <string>
using namespace std;
class SingleByteCharacter;
class DoubleByteCharacter;
class Row;
class Text;
class CDC;
typedef signed long int Long;
class PaintVisitor :public Visitor {
public:
	PaintVisitor();
	PaintVisitor(CDC *pdc,Long screenHeight,Long paperPosY);
	//PaintVisitor(Long start, Long end);
	~PaintVisitor();
	void Visit(Text *text);
	void Visit(Row *row);
	void Visit(SingleByteCharacter *singleByteCharacter);
	void Visit(DoubleByteCharacter *doubleByteCharacter);
	string& GetStr() const;
	Long GetFontSize() const;
private:
	string str;
	//Long start;
	//Long end;
	CDC *pdc;
	Long screenHeight;
	Long paperPosY;
	Long fontSize;
};
inline string& PaintVisitor::GetStr() const {
	return const_cast<string&>(this->str);
}
inline Long PaintVisitor::GetFontSize() const {
	return this->fontSize;
}



#endif // _PAINTVISITOR_H
