//SelectAllMenu.h
#ifndef _SELECTALLMENU_H
#define _SELECTALLMENU_H
#include "MenuAction.h"
class MemoForm;
class SelectAllMenu :public MenuAction {
public:
	SelectAllMenu();
	virtual ~SelectAllMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _SELECTALLMENU_H
