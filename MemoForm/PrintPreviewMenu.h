//PrintPreviewMenu.h
#ifndef _PRINTPREVIEWMENU_H
#define _PRINTPREVIEWMENU_H
#include "MenuAction.h"
class MemoForm;
class PrintPreviewMenu :MenuAction {
public:
	PrintPreviewMenu();
	virtual ~PrintPreviewMenu();

	void Implement(MemoForm *memoForm);

};
#endif // _PRINTPREVIEWMENU_H
