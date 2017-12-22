//MovePreviousPageMenu.h
#ifndef _MOVEPREVIOUSPAGEMENU_H
#define _MOVEPREVIOUSPAGEMENU_H
#include "MenuAction.h"
class MemoForm;
class MovePreviousPageMenu :public MenuAction {
public:
	MovePreviousPageMenu();
	virtual ~MovePreviousPageMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _MOVEPREVIOUSPAGEMENU_H
