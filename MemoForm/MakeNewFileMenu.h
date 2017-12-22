//MakeNewFileMenu.h
#ifndef _MAKENEWFILEMENU_H
#define _MAKENEWFILEMENU_H
#include "MenuAction.h"
class MemoForm;
class MakeNewFileMenu :public MenuAction {
public:
	MakeNewFileMenu();
	virtual ~MakeNewFileMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _MAKENEWFILEMENU_H
