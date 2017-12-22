//SetPageMenu.h
#ifndef _SETPAGEMENU_H
#define _SETPAGEMENU_H
#include "MenuAction.h"
class MemoForm;
class SetPageMenu :MenuAction {
public:
	SetPageMenu();
	virtual ~SetPageMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _SETPAGEMENU_H
