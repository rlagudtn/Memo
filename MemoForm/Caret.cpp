//Caret.cpp
#include "Caret.h"
#include "MemoForm.h"

Caret::Caret() {
	this->x = 0;
	this->y = 0;
}

Caret::Caret(const Caret& source) {
	this->x = source.x;
	this->y = source.y;
}

Caret::~Caret() {}

void Caret::Move(Long x, Long y) {

	this->x = x;
	this->y = y;
}
void Caret::MoveX(Long x) {
	this->x = x;
}
void Caret::MoveY(Long y) {
	this->y = y;
}
/*
Long Caret::Delete(Long index) {
if (this != 0) {
this->x = -1;
this->y = -1;
}
return
}*/

Caret& Caret::operator=(const Caret& source) {
	this->x = source.x;
	this->y = source.y;
	return *this;
}