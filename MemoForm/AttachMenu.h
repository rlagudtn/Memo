//AttachMenu.h
#ifndef _ATTACHMENU_H
#define _ATTACHMENU_H
#include "MenuAction.h"
class MemoForm;
class AttachMenu :MenuAction {
public:
	AttachMenu();
	virtual ~AttachMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _ATTACHMENU_H
