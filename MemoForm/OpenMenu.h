//OpenMenu.h
#ifndef _OPTIONMENU_H
#define _OPTIONMENU_H
#include "MenuAction.h"
class MemoForm;
class OpenMenu :public MenuAction {
public:
	OpenMenu();
	virtual ~OpenMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _OPTIONMENU_H
