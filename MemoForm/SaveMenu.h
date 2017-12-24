//SaveMenu.h
#ifndef _SAVEMENU_H
#define _SAVEMENU_H
#include "MenuAction.h"
class MemoForm;
class SaveMenu :public MenuAction {
public:
	SaveMenu();
	virtual ~SaveMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _SAVEMENU_H
