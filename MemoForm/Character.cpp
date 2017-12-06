//Character.cpp
#include "Character.h"
Character::Character() {
	
	this->width = 8;
	this->height = 8;

}
Character::Character(Long width, Long  height) {
	
	this->width = width;
	this->height = height;

}


Character::Character(const Character& source) {
	
	this->width = source.width;
	this->height = source.height;

}
Character::~Character() {};
bool Character::IsEqual(const Character& other) {
	bool ret = false;
	if (this->width == other.width&& this->height == other.height) {
		ret = true;
	}
	return ret;
}
bool Character::IsNotEqual(const Character& other) {
	bool ret = false;
	if ( this->width != other.width || this->height != other.height) {
		ret = true;
	}
	return ret;
}
Character& Character::operator=(const Character& source) {
	
	this->width = source.width;
	this->height = source.height;

	return *this;
}

bool Character::operator==(const Character& other) {
	bool ret = false;
	if (this->width == other.width&& this->height == other.height) {
		ret = true;
	}
	return ret;
}

bool Character::operator!=(const Character& other) {
	bool ret = false;
	if (this->width != other.width || this->height != other.height) {
		ret = true;
	}
	return ret;
}
Glyph* Character::Clone() {
	return this;
}

void Character::Accept(Visitor *visitor) {}