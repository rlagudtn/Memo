//HomeKey.h
#ifndef _HOMEKEY_H
#define _HOMEKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class HomeKey :public KeyAction {
public:
	HomeKey();
	HomeKey(const HomeKey& source);
	virtual ~HomeKey();

	void Implement(MemoForm *memoForm);

};
#endif // _HOMEARROWKEY_H