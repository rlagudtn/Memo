//Glyph.cpp
#include "Glyph.h"


Glyph::Glyph() {};

Glyph::Glyph(const Glyph& source) {}

Glyph::~Glyph() {}

Long Glyph::Add(Glyph *glyph) {
	return -1;
}

Glyph* Glyph::GetAt(Long index) {
	return nullptr;
}
Glyph* Glyph::Clone() {
	return this;
}

void Glyph::Accept(Visitor *visitor) {
}