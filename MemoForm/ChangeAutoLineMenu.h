//ChangeAutoLineMenu.h
#ifndef _CHANGEAUTOLINEMENUMENU_H
#define _CHANGEAUTOLINEMENUMENU_H
#include "MenuAction.h"
class MemoForm;
class ChangeAutoLineMenu :MenuAction {
public:
	ChangeAutoLineMenu();
	virtual ~ChangeAutoLineMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _CHANGEAUTOLINEMENU_H
