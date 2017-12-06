//Composite.h

#ifndef _COMPOSITE_H
#define _COMPOSITE_H
#include "Glyph.h"
#include "Array.h"

typedef signed long int Long;
class Visitor;
class Composite :public Glyph {
public:
	Composite(Long capacity);
	Composite(const Composite& source);
	virtual ~Composite() = 0;
	Long Add(Glyph *glyph);
	Glyph* GetAt(Long index) const;
	Long TakeIn(Long index, Glyph *glyph);
	Long Delete(Long index);
	Long Modify(Long index, Glyph *glyph);
	Glyph* Move(Long index);
	Composite& operator=(const Composite& source);
	bool IsEqual(const Composite& other);
	bool IsNotEqual(const Composite& other);
	bool operator==(const Composite& other);
	bool operator!=(const Composite& other);
	virtual Glyph* Clone();
	Long GetCurrent() const;
	Long GetCapacity() const;
	Long GetLength() const;
	virtual void Accept(Visitor *visitor)=0;
	

	
protected:
	Array<Glyph*> glyphs;
	Long current;
	Long capacity;
	Long length;

};
inline Long Composite::GetCurrent() const {
	return this->current;
}
inline Long Composite::GetCapacity() const {
	return this->capacity;
}
inline Long Composite::GetLength() const {
	return this->length;
}

#endif // _COMPOSITE_H