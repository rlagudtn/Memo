//KeyBoard.h
#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include<afxwin.h>
#include "KeyAction.h"
class MemoForm;
class KeyBoard {
public:
	KeyBoard();
	KeyBoard(const KeyBoard& source);
	~KeyBoard();

	void SetKeyAction(UINT nChar, UINT nRepCnt, UINT nFlags);
	void DoAction(MemoForm *memoForm);
	KeyAction* GetKeyAction() const;
private:
	KeyAction *keyAction;
};
inline KeyAction* KeyBoard::GetKeyAction() const {
	return const_cast<KeyAction*>(this->keyAction);
}
#endif // _KEYBOARD_H
