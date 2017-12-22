//FindMenu.h
#ifndef _FINDMENU_H
#define _FINDMENU_H
#include "MenuAction.h"
class MemoForm;
class FindMenu :public MenuAction {
public:
	FindMenu();
	virtual ~FindMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _FINDMENU_H
