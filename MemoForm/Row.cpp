//Row.cpp

#include "Row.h"

#include "Character.h"
#include "Visitor.h"
Row::Row(Long capacity) :Composite(capacity) {
	this->next = -1;
}

Row::Row(const Row& source) : Composite(source) {
	this->next = source.next;
}

Row::~Row() {}
void Row::ConnectRow(Long index) {
	this->next = index;
}
Glyph* Row::Clone() {
	return new Row(*this);
}

void Row::Accept(Visitor *visitor) {
	visitor->Visit(this);
}