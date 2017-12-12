//LineInfo.cpp
#include "LineInfo.h"

LineInfo::LineInfo(Long capacity):booleans(capacity){
	this->capacity = capacity;
	this->length = 0;
}

LineInfo::LineInfo(const LineInfo& source) :booleans(source.booleans){
	this->capacity = source.capacity;
	this->length = source.length;
}
LineInfo::~LineInfo(){}
LineInfo& LineInfo::operator=(const LineInfo& source) {
	this->booleans = source.booleans;
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;

}
Long LineInfo::GetAt(Long index) {
	return this->booleans.GetAt(index);
}
Long LineInfo::Add(Long isOver) {
	Long index;
	if (this->length < this->capacity) {
		index = this->booleans.Store(this->length, isOver);
	}
	else {
		index = this->booleans.AppendFromRear(isOver);
		this->capacity++;
	}
	this->length++;

	return index;
}
Long LineInfo::operator[](Long index) {
	return this->booleans[index];
}
