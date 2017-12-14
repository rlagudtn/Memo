//BackSpaceKey.h
#ifndef _BACKSPACEKEY_H
#define _BACKSPACEKEY_H
#include "KeyAction.h"
typedef signed long int Long;
class MemoForm;
class BackSpaceKey :public KeyAction {
public:
	BackSpaceKey();
	BackSpaceKey(const BackSpaceKey& source);
	virtual ~BackSpaceKey();

	void Implement(MemoForm *memoForm);

};
#endif // _SHIFTALLKEY_H