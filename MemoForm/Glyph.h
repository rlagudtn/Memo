//Glyph.h
#ifndef _GLYPH_H
#define _GLYPH_H
//#include "MemoForm.h"

typedef signed long int Long;
class Visitor;
class Glyph {
public:
	Glyph();
	Glyph(const Glyph &source);
	virtual ~Glyph() = 0;
	virtual Long Add(Glyph *glyph);
	virtual Glyph* GetAt(Long index);
	virtual Glyph* Clone();
	virtual void Accept(Visitor *visitor)=0;
};
#endif // !_GLYPH_H
