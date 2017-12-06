//Paper.cpp
#include "Paper.h"

Paper::Paper() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}
Paper::Paper(Long width, Long height) {
	this->x = 0;
	this->y = 0;
	this->width = width;
	this->height = height;
}
Paper::Paper(const Paper& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
}

Paper::~Paper(){}

void Paper::MoveToX(Long x) {
	this->x = x;
}

void Paper::MoveToY(Long y) {
	this->y = y;
}

void Paper::Move(Long x, Long y) {
	this->x = x;
	this->y = y;
}
void Paper::ModifyWidth(Long width) {
	this->width = width;
}
void Paper::ModifyHeight(Long height) {
	this->height = height;
}
void Paper::ModifyPaper(Long width, Long height) {
	this->width = width;
	this->height = height;
}