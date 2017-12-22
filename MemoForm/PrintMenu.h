//PrintMenu.h
#ifndef _PRINTMENU_H
#define _PRINTMENU_H
#include "MenuAction.h"
class MemoForm;
class PrintMenu :MenuAction {
public:
	PrintMenu();
	virtual ~PrintMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _PRINTMENU_H
