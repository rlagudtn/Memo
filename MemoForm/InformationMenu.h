//InformationMenu.h
#ifndef _INFORMATIONMENU_H
#define _INFORMATIONMENU_H
#include "MenuAction.h"
class MemoForm;
class InformationMenu :MenuAction {
public:
	InformationMenu();
	virtual ~InformationMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _INFORMATIONMENU_H
