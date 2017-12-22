//CutMenu.h
#ifndef _CUTMENU_H
#define _CUTMENU_H
#include "MenuAction.h"
class MemoForm;
class CutMenu :MenuAction {
public:
	CutMenu();
	virtual ~CutMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _CUTMENU_H
