//MoveNextPageMenu.h
#ifndef _MOVENEXTPAGEMENUNMENU_H
#define _MOVENEXTPAGEMENUMENU_H
#include "MenuAction.h"
class MemoForm;
class MoveNextPageMenu :public MenuAction {
public:
	MoveNextPageMenu();
	virtual ~MoveNextPageMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _MOVENEXTPAGEMENUMENU_H
