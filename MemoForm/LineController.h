//LineController.h
#ifndef _LINECONTROLLER_H
#define _LINECONTROLLER_H
#include <afxwin.h>
typedef signed long int Long;
class Text;
class MemoForm;
class Row;
class LineController {
public:
	LineController();
	LineController(const LineController& source);
	~LineController();
	void SetLineInfo(MemoForm *memoForm,CDC *dc);
	void MakeNewLine(MemoForm *memoForm,Long index);
	void AutomaticLineChange(MemoForm *memoForm,CDC *dc);
	void SetLineFeed(Row *row);
};
#endif // _LINECONTROLLER_H
