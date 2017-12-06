// Page.h
#ifndef _PAGE_H
#define _PAGE_H
#include "Composite.h"

class Visitor;
class Page :public Composite {
public:
	Page(Long capacity =16);
	Page(const Page& source);
	virtual ~Page();
	Glyph* Clone();
	void Accept(Visitor *visitor);

};

#endif // _PAGE_H