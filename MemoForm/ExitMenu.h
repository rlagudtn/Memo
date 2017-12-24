//ExitMenu.h
#ifndef _EXITMENU_H
#define _EXITMENU_H
#include "MenuAction.h"
class MemoForm;
class ExitMenu :public MenuAction {
public:
	ExitMenu();
	virtual ~ExitMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _EXITMENU_H
