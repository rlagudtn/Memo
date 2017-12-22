//SaveMenu.h
#ifndef _SAVEMENU_H
#define _SAVEMENU_H
#include "MenuAction.h"
class MemoForm;
class SaveMenu :MenuAction {
public:
	SaveMenu();
	virtual ~SaveMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _SAVEMENU_H
