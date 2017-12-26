//FontMenu.h
#ifndef _FONTMENU_H
#define _FONTMENU_H
#include "MenuAction.h"
class MemoForm;
class FontMenu :public MenuAction {
public:
	FontMenu();
	virtual ~FontMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _FONTMENU_H
