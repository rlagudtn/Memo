//Row.h
#ifndef _ROW_H
#define _ROW_H
#include "Composite.h"

class  Visitor;
typedef signed long int Long;
class Row :public Composite {
public:
	Row(Long capacity = 64);
	Row(const Row& source);
	virtual ~Row();
	virtual Glyph* Clone();
	void Accept(Visitor *visitor);
	Long GetNext() const;
	void ConnectRow(Long index);
private:
	Long next;
};
inline Long Row::GetNext() const {
	return this->next;
}
#endif // _ROW_H
