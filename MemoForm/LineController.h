//LineController.h
#ifndef _LINECONTROLLER_H
#define _LINECONTROLLER_H
#include <afxwin.h>
#include "LineInfo.h"
typedef signed long int Long;
class Text;
class MemoForm;
class Row;
class LineController {
public:
	LineController();
	LineController(const LineController& source);
	~LineController();
	void MakeNewLine(MemoForm *memoForm,Long index);
	void AutomaticLineChange(MemoForm *memoForm,CDC *dc);
	
private:
	LineInfo *lineInfo;
};
#endif // _LINECONTROLLER_H
