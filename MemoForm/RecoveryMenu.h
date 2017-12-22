//RecoveryMenu.h
#ifndef _RECOVERYMENU_H
#define _RECOVERYMENU_H
#include "MenuAction.h"
class MemoForm;
class RecoveryMenu :MenuAction {
public:
	RecoveryMenu();
	virtual ~RecoveryMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _RECOVERYMENU_H
