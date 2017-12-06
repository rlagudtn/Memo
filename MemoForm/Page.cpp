//Page.cpp
#include "Page.h"
#include "Row.h"
#include "Visitor.h"
Page::Page(Long capacity) :Composite(capacity) {}

Page::Page(const Page& source) : Composite(source) {}

Page::~Page() {}

Glyph* Page::Clone() {
	return new Page(*this);
}

void Page::Accept(Visitor *visitor) {
	visitor->Visit(this);
}