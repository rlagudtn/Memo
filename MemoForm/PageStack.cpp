//PageStack.cpp
#include "PageStack.h"
#include "Page.h"

PageStack::PageStack(Long capacity) :stack(capacity){
	this->capacity = capacity;
	this->top = -1;
}
PageStack::PageStack(const PageStack& source) : stack(source.stack) {
	this->capacity = source.capacity;
	//안의 내용 복사해줘야됨
	Long i = 0;
	while (i <= source.top) {
		Page *page = new Page(*source.stack.GetAt(i));
		this->stack.Modify(i, page);
		i++;
	}
	this->top = source.top;

}
PageStack::~PageStack(){}
PageStack& PageStack::operator=(const PageStack& source) {
	this->stack = source.stack;
	this->capacity = source.capacity;
	//안의 내용 복사해줘야됨
	Long i = 0;
	while (i <= source.top) {
		Page *page = new Page(*source.stack.GetAt(i));
		this->stack.Modify(i, page);
		i++;
	}
	this->top = source.top;

	return *this;
}
void PageStack::Push(Page *page) {
	Page *previousPage = new Page(*page);
	if (this->top <this->capacity -1) {
		this->stack.Store(this->top + 1, previousPage);
	}
	else {
		this->stack.AppendFromRear(previousPage);
		this->capacity++;
	}
	this->top++;
}
Page* PageStack::Pop(){
	Page *ret = 0;
	if (this->top >= 0) {
		ret = new Page(*this->stack.GetAt(this->top));
		this->stack.Delete(this->top);
		this->capacity--;
		this->top--;
	}
	return ret;
}
bool PageStack::IsEmpty() {
	bool ret = false;
	if (this->top <= -1) {
		ret=true;
	}
	return ret;
}
