//KeyAction.h
#ifndef _KEYACTION_H
#define _KEYACTION_H
class MemoForm;
class KeyAction {
public:
	KeyAction();
	KeyAction(const KeyAction& source);
	~KeyAction();
	virtual void Implement(MemoForm *memoForm)=0;
};
#endif // !_KEYACTION_H
