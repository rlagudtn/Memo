//Visitor.h
#ifndef _VISITOR_H
#define _VISITOR_H
class SingleByteCharacter;
class DoubleByteCharacter;
class Row;
class Text;
class Page;
class Visitor {
public:
	//Visitor();
	//virtual ~Visitor()=0;
	virtual void Visit(SingleByteCharacter *singleByteCharacter);
	virtual void Visit(DoubleByteCharacter *doubleByteCharacter)=0;
	virtual void Visit(Row *row);
	virtual void Visit(Text *text);
	virtual void Visit(Page *page) ;
};


#endif // _VISITOR_H