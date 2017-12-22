//MakeNewPageMenu.h
#ifndef _MAKENEWPAGEMENU_H
#define _MAKENEWPAGEMENU_H
#include "MenuAction.h"
class MemoForm;
class MakeNewPageMenu :public MenuAction {
public:
	MakeNewPageMenu();
	virtual ~MakeNewPageMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _MAKENEWPAGEMENU_H
