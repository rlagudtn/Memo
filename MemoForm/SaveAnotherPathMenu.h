//SaveAnotherPathMenu.h
#ifndef _INFORMATIONMENU_H
#define _INFORMATIONMENU_H
#include "MenuAction.h"
class MemoForm;
class SaveAnotherPathMenu :MenuAction {
public:
	SaveAnotherPathMenu();
	virtual ~SaveAnotherPathMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _INFORMATIONMENU_H
