//PageStack.h
#ifndef _PAGESTACK_H
#define _PAGESTACK_H
#include "Array.h"
typedef signed long int Long;
class Page;
class PageStack {
public:
	PageStack(Long capacity=1024);
	PageStack(const PageStack& source);
	~PageStack();
	PageStack& operator=(const PageStack& source);
	void Push(Page *page);
	Page* Pop();
	bool IsEmpty();
	Long GetCapacity() const;
	Long GetTop() const;
private:
	Array<Page*> stack;
	Long capacity;
	Long top;
};
inline Long PageStack::GetCapacity() const {
	return this->capacity;
}
inline Long PageStack::GetTop() const {
	return this->top;
}
#endif // _PAGESTACK_H
