// Text.h
#ifndef _TEXT_H
#define _TEXT_H
#include "Composite.h"

class Visitor;
class Character;
class Text :public Composite {
public:
	Text(Long capacity = 60000);
	Text(const Text& source);
	virtual ~Text();
	Glyph* Clone();
	void Accept(Visitor *visitor);

};

#endif // _TEXT_H