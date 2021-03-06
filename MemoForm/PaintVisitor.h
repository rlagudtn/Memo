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
class MemoForm;
class CDC;
typedef signed long int Long;
class PaintVisitor :public Visitor {
public:
	PaintVisitor();
	PaintVisitor(MemoForm *memoForm,CDC *dc);
	//PaintVisitor(Long start, Long end);
	~PaintVisitor();
	void Visit(Text *text);
	void Visit(Row *row);
	void Visit(SingleByteCharacter *singleByteCharacter);
	void Visit(DoubleByteCharacter *doubleByteCharacter);
	string& GetStr() const;
private:
	string str;
	//Long start;
	//Long end;
	MemoForm *memoForm;
	CDC *dc;
};
inline string& PaintVisitor::GetStr() const {
	return const_cast<string&>(this->str);
}



#endif // _PAINTVISITOR_H
