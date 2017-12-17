//WriteKorean.h
#ifndef _WRITEKOREAN_H
#define _WRITEKOREAN_H
#include <afxwin.h>
class MemoForm;
class WriteKorean {
public:
	WriteKorean();
	~WriteKorean();
	void Write(MemoForm *memoForm,UINT wParam, LONG lParam);
};
#endif // _WRITEKOREAN_H
