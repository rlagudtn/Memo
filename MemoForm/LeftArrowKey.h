//LeftArrowKey.h
#ifndef _LEFTARROWKEY_H
#define _LEFTARROWKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class LeftArrowKey :public KeyAction{
public:
	LeftArrowKey();
	LeftArrowKey(const LeftArrowKey& source);
	virtual ~LeftArrowKey();

	void Implement(MemoForm *memoForm);

};
#endif // _LEFTARROWKEY_H
