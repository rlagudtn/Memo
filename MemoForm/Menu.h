//Menu.h
#ifndef _MENU_H
#define _MENU_H
class MemoForm;
class CMenu;
class Menu
{
public:
	Menu(MemoForm *memoForm);
	~Menu();
	void SetMenuBar(MemoForm *memoForm);
private:
	MemoForm *memoForm;
	CMenu *main;
	CMenu *file;
	CMenu *edit;
	CMenu *option;
	CMenu *view;
	CMenu *help;
};


#endif // _MENU_H
