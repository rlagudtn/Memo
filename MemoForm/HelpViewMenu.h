//HelpViewMenu.h
#ifndef _HELPVIEWMENU_H
#define _HELPVIEWMENU_H
#include "MenuAction.h"
class MemoForm;
class HelpViewMenu :MenuAction {
public:
	HelpViewMenu();
	virtual ~HelpViewMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _HELPVIEWMENU_H
