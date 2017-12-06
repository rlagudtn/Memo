//DoubleByteCharacter.cpp
#include "DoubleByteCharacter.h"
#include "Visitor.h"
#include <string>
#pragma warning(disable:4996)

DoubleByteCharacter::DoubleByteCharacter() {
	strcpy(this->alphabet,"");
}
DoubleByteCharacter::DoubleByteCharacter(Long width, Long height, char *alphabet)
	:Character(width, height) {
	strcpy(this->alphabet, alphabet);
}
DoubleByteCharacter::DoubleByteCharacter(char *alphabet) {
	strcpy(this->alphabet, alphabet);
}
DoubleByteCharacter::DoubleByteCharacter(const DoubleByteCharacter& source)
	: Character(source) {
	strcpy(this->alphabet, source.alphabet);
}
DoubleByteCharacter::~DoubleByteCharacter() {}

DoubleByteCharacter& DoubleByteCharacter::operator=(const DoubleByteCharacter& source) {
	
	this->width = source.width;
	this->height = source.height;
	strcpy(this->alphabet, source.alphabet);
	return *this;
}
bool DoubleByteCharacter::IsEqual(const DoubleByteCharacter& other) {
	bool ret = false;
	if (Character::IsEqual(other) == true && this->alphabet == other.alphabet) {
		ret = true;
	}
	return ret;
}
bool DoubleByteCharacter::IsNotEqual(const DoubleByteCharacter& other) {
	bool ret = false;
	if (Character::IsNotEqual(other) == true || this->alphabet != other.alphabet) {
		ret = true;
	}
	return ret;
}
bool DoubleByteCharacter::operator==(const DoubleByteCharacter& other) {
	bool ret = false;
	//if (this->x == other.x&&this->y == other.y&&this->width == other.width&&this->height == other.height&& this->alphabet == other.alphabet) {
	//   ret = true;
	//}
	if (Character::operator==(other) == true && this->alphabet == other.alphabet) {
		ret = true;
	}
	return ret;
}
bool DoubleByteCharacter::operator!=(const DoubleByteCharacter& other) {
	bool ret = false;
	if (Character::operator!=(other) == true || this->alphabet != other.alphabet) {
		ret = true;
	}
	return ret;
}

Glyph* DoubleByteCharacter::Clone() {
	return new DoubleByteCharacter(*this);
}

void DoubleByteCharacter::Accept(Visitor *visitor) {
	visitor->Visit(this);
}