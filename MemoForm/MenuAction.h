//MenuAction.h
#ifndef _MENUACTION_H
#define _MENUACTION_H
class MemoForm;
class MenuAction {
public:
	MenuAction();
	MenuAction(const MenuAction& source);
	~MenuAction();
	virtual void Implement(MemoForm *memoForm) = 0;
};
#endif // _MENUACTION_H
