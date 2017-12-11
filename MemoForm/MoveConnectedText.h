//MoveConnectedText.h
#ifndef _MOVECONNECTEDTEXT_H
#define _MOVECONNECTEDTEXT_H
#include <afxwin.h>
typedef signed long int Long;
class MemoForm;
class MoveConnectedText {
public :
	MoveConnectedText();
	MoveConnectedText(const MoveConnectedText& source);
	~MoveConnectedText();
	void ChangeLine(MemoForm *memoForm,CDC *dc,Long index);

};
#endif // !_MOVECONNECTEDTEXT_H
