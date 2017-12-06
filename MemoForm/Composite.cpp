//Composite.cpp
#include "Composite.h"

Composite::Composite(Long capacity)
	:glyphs(capacity) {
	this->current = -1;
	this->capacity = capacity;
	this->length = 0;
}

Composite::Composite(const Composite& source)
	:glyphs(source.glyphs) {
	Long i = 0;
	Glyph *temp;
	this->capacity = source.capacity;
	while (i < source.length) {
		Glyph *glyph = (source.GetAt(i))->Clone();
		//임시변수에 기존것의 주소를 넘기고 힙에 있는 것을 삭제
		temp = this->glyphs.GetAt(i);
		this->glyphs.Modify(i, glyph);
		delete temp;
		i++;
	}
	this->current = source.current;
	this->length = source.length;
}

Composite::~Composite() {

}

Long Composite::Add(Glyph *glyph) {
	Long index;
	if (this->length < this->capacity) {
		index = this->glyphs.Store(this->length, glyph);
	}
	else {
		index = this->glyphs.AppendFromRear(glyph);
		this->capacity++;
	}
	this->current++;
	this->length++;
	return index;
}

Glyph* Composite::GetAt(Long index) const {
	return this->glyphs.GetAt(index);
}

Long Composite::TakeIn(Long index, Glyph *glyph) {
	index = this->glyphs.Insert(index, glyph);
	this->current=index;
	this->capacity++;
	this->length++;

	return index;
}

Long Composite::Delete(Long index) {
	this->glyphs.Delete(index);
	this->current=index-1;
	this->capacity--;
	this->length--;

	return index;
}

Glyph* Composite::Move(Long index) {
	Glyph* glyph=0;
	this->current = index;
	if(this->current>=0){
		glyph = this->glyphs.GetAt(this->current);
	}
	return glyph;
}
Long Composite::Modify(Long index, Glyph *glyph) {
	Glyph *temp = this->glyphs.GetAt(index);
	index = this->glyphs.Modify(index, glyph);
	delete temp;
	return index;
}


Composite& Composite::operator=(const Composite& source) {


	Long i = 0;

	this->glyphs = source.glyphs;
	this->capacity = source.capacity;
	while (i < source.length) {
		Glyph *glyph = (source.GetAt(i))->Clone();
		Glyph *temp = this->glyphs.GetAt(i);
		this->glyphs.Modify(i, glyph);
		delete temp;
		i++;
	}
	this->current = source.current;
	this->length = source.length;

	return *this;
}

bool Composite::IsEqual(const Composite& other) {
	bool ret = false;
	if (this->current == other.current&&this->capacity == other.capacity&&this->length == other.length) {
		ret = true;
	}
	return ret;
}

bool Composite::IsNotEqual(const Composite& other) {
	bool ret = false;
	if (this->current != other.current || this->capacity != other.capacity || this->length != other.length) {
		ret = true;
	}
	return ret;
}

bool Composite::operator==(const Composite& other) {
	bool ret = false;
	if (this->current == other.current&&this->capacity == other.capacity&&this->length == other.length) {
		ret = true;
	}
	return ret;
}

bool Composite::operator!=(const Composite& other) {
	bool ret = false;
	if (this->current != other.current || this->capacity != other.capacity || this->length != other.length) {
		ret = true;
	}
	return ret;
}

Glyph* Composite::Clone() {
	return this;
}

void Composite::Accept(Visitor *visitor) {}