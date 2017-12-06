//Text.cpp
#include "Text.h"
#include "Row.h"
#include "Visitor.h"
Text::Text(Long capacity) :Composite(capacity) {}

Text::Text(const Text& source) : Composite(source) {}

Text::~Text() {}

Glyph* Text::Clone() {
	return new Text(*this);
}

void Text::Accept(Visitor *visitor) {
	visitor->Visit(this);
}