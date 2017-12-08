//Row.h
#ifndef _ROW_H
#define _ROW_H
#include "Composite.h"
#include <string>
#pragma warning (disable:4996)
using namespace std;
class  Visitor;
typedef signed long int Long;
class Row :public Composite {
public:
	Row(Long capacity = 64);
	Row(const Row& source);
	virtual ~Row();
	virtual Glyph* Clone();
	void Accept(Visitor *visitor);
};

#endif // _ROW_H
