//Row.cpp

#include "Row.h"

#include "Character.h"
#include "Visitor.h"
Row::Row(Long capacity) :Composite(capacity) {
}

Row::Row(const Row& source) : Composite(source) {
}

Row::~Row() {}

Glyph* Row::Clone() {
	return new Row(*this);
}

void Row::Accept(Visitor *visitor) {
	visitor->Visit(this);
}