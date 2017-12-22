//CopyMenu.h
#ifndef _COPYMENU_H
#define _COPYMENU_H
#include "MenuAction.h"
class MemoForm;
class CopyMenu :public MenuAction {
public:
	CopyMenu();
	virtual ~CopyMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _COPYMENU_H
