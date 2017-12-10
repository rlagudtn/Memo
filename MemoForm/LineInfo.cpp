//LineInfo.cpp
#include "LineInfo.h"

LineInfo::LineInfo(Long capacity){
	this->capacity = capacity;
	this->length = 0;
}

LineInfo::LineInfo(const LineInfo& source) :isOverScreen(source.isOverScreen){
	this->capacity = source.capacity;
	this->length = source.length;
}
LineInfo::~LineInfo(){}
LineInfo& LineInfo::operator=(const LineInfo& source) {
	this->isOverScreen = source.isOverScreen;
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;

}
bool LineInfo::GetAt(Long index) {
	return this->isOverScreen.GetAt(index);
}
Long LineInfo::Add(bool isOver) {
	Long index;
	if (this->length < this->capacity) {
		index = this->isOverScreen.Store(this->length, isOver);
	}
	else {
		index = this->isOverScreen.AppendFromRear(isOver);
		this->capacity++;
	}
	this->length++;

	return index;
}
bool LineInfo::operator[](Long index) {
	return this->isOverScreen[index];
}
