//Menu.h
#ifndef _MENU_H
#define _MENU_H
#include <afxwin.h>
class MemoForm;
class CMenu;
class MenuAction;
class Menu
{
public:
	Menu(MemoForm *memoForm);
	~Menu();
	void SetMenuAction(UINT nID);
	void DoAction();
private:
	MemoForm *memoForm;
	MenuAction *menuAction;
	CMenu *main;
	CMenu *file;
	CMenu *edit;
	CMenu *option;
	CMenu *view;
	CMenu *help;

};


#endif // _MENU_H
