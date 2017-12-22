//ChangeTextMenu.h
#ifndef _CHANGETEXTMENU_H
#define _CHANGETEXTMENU_H
#include "MenuAction.h"
class MemoForm;
class ChangeTextMenu :public MenuAction {
public:
	ChangeTextMenu();
	virtual ~ChangeTextMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _CHANGETEXTMENU_H
