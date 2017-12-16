//Caret.h
#ifndef _CARET_H
#define _CARET_H
#include <afxwin.h>
typedef signed long int Long;
class MemoForm;
class CDC;
class Caret {
public:
	Caret();
	Caret(const Caret& source);
	~Caret();
	void Move(Long x, Long y);
	void MoveX(Long x);
	void MoveY(Long y);
	void MoveToCurrent(MemoForm *memoForm);
	void MoveToPoint(MemoForm *memoForm, CDC *dc,CPoint point);
	Caret& operator=(const Caret& source);
	Long GetX() const;
	Long GetY() const;
private:
	Long caretX;
	Long caretY;
};

inline Long Caret::GetX() const {
return this->caretX;
}

inline Long Caret::GetY() const {
return this->caretY;
}

#endif //CARET_H