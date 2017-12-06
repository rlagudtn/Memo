//SingleByteCharacter.cpp
#include "SingleByteCharacter.h"
#include "Visitor.h"
SingleByteCharacter::SingleByteCharacter() {
	this->alphabet = ' ';
}
SingleByteCharacter::SingleByteCharacter(Long width, Long height, char alphabet)
	:Character(width, height) {
	this->alphabet = alphabet;
}

SingleByteCharacter::SingleByteCharacter(char alphabet) {
	this->alphabet = alphabet;
}

SingleByteCharacter::SingleByteCharacter(const SingleByteCharacter& source)
	: Character(source) {
	this->alphabet = source.alphabet;
}
SingleByteCharacter::~SingleByteCharacter() {}

SingleByteCharacter& SingleByteCharacter::operator=(const SingleByteCharacter& source) {
	
	this->width = source.width;
	this->height = source.height;
	this->alphabet = source.alphabet;
	return *this;
}
bool SingleByteCharacter::IsEqual(const SingleByteCharacter& other) {
	bool ret = false;
	if (Character::IsEqual(other) == true && this->alphabet == other.alphabet) {
		ret = true;
	}
	return ret;
}
bool SingleByteCharacter::IsNotEqual(const SingleByteCharacter& other) {
	bool ret = false;
	if (Character::IsNotEqual(other) == true || this->alphabet != other.alphabet) {
		ret = true;
	}
	return ret;
}
bool SingleByteCharacter::operator==(const SingleByteCharacter& other) {
	bool ret = false;
	if (Character::operator==(other) == true && this->alphabet == other.alphabet) {
		ret = true;
	}
	return ret;
}
bool SingleByteCharacter::operator!=(const SingleByteCharacter& other) {
	bool ret = false;
	if (Character::operator!=(other) == true || this->alphabet != other.alphabet) {
		ret = true;
	}
	return ret;
}

Glyph* SingleByteCharacter::Clone() {
	return new SingleByteCharacter(*this);
}
void SingleByteCharacter::Accept(Visitor *visitor) {
	visitor->Visit(this);
}