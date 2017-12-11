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
	Long ChangeLine(MemoForm *memoForm,CDC *dc,Long textIndex,Long rowIndex=0);

};
#endif // _CUTSTRING_H
