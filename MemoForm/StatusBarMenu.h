//StatusBarMenu.h
#ifndef _STATUSBARMENU_H
#define _STATUSBARMENU_H
#include "MenuAction.h"
class MemoForm;
class StatusBarMenu :MenuAction {
public:
	StatusBarMenu();
	virtual ~StatusBarMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _STATUSBARMENU_H
