//EnterKey.h
#ifndef _ENTERKEY_H
#define _ENTERKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class EnterKey :public KeyAction {
public:
	EnterKey();
	EnterKey(const EnterKey& source);
	virtual ~EnterKey();

	void Implement(MemoForm *memoForm);

};
#endif // _SHIFTALLKEY_H