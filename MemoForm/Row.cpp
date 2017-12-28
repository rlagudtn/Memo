//Row.cpp

#include "Row.h"

#include "Character.h"
#include "Visitor.h"
Row::Row(Long capacity) :Composite(capacity) {
	this->isConnected = false;
}

Row::Row(const Row& source) : Composite(source) {
	this->isConnected = source.isConnected;
}

Row::~Row() {}

Glyph* Row::Clone() {
	return new Row(*this);
}

void Row::Accept(Visitor *visitor) {
	visitor->Visit(this);
}
void Row::Connect() {
	this->isConnected = true;
}
void Row::DisConnect() {
	this->isConnected = false;
}