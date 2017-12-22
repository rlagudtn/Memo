//DeletePageMenu.h
#ifndef _DELETEPAGEMENU_H
#define _DELETEPAGEMENU_H
#include "MenuAction.h"
class MemoForm;
class DeletePageMenu :public MenuAction {
public:
	DeletePageMenu();
	virtual ~DeletePageMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _DELETEPAGEMENU_H
