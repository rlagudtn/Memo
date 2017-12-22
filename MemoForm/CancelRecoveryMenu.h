//CancelRecoveryMenu.h
#ifndef _CANCELRECOVERYMENU_H
#define _CANCELRECOVERYMENU_H
#include "MenuAction.h"
class MemoForm;
class CancelRecoveryMenu :MenuAction {
public:
	CancelRecoveryMenu();
	virtual ~CancelRecoveryMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _CANCELRECOVERYMENU_H
