//MemoForm.h
#ifndef _MEMOFORM_H
#define _MEMOFORM_H
#include <afxwin.h>
#include < afxdlgs.h>
#include < afxext.h>
class Page;
class Text;
class Character;
class SingleByteCharacter;
class DoubleByteCharacter;
class Row;
class Text;
class Paper;
class Caret;
class LineInfo;
class PageStack;
class Menu;
//class GetString;
class SelectedText;
typedef signed long int Long;

class MemoForm : public CFrameWnd
{
public:
	MemoForm(CWnd *parent=NULL);
	
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LONG OnStartComposition(UINT wParam,LONG lParam);
	afx_msg LONG OnComposition(UINT wParam, LONG lParam);
	afx_msg void OnKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags,short zDelta,CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LONG OnFindReplace(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnMenu(UINT nID);
	DECLARE_MESSAGE_MAP()
public:

	Page *page;
	Text *text;
	Row *row;
	Paper *paper;
	LineInfo *lineInfo;
	Long screenWidth;
	Long screenHeight;
	Caret *caret;
	SelectedText *selectedText;
	//키 눌려졌을때의 현재 위치 저장
	Long keyDownTextIndex;
	Long keyDownRowIndex;
	//찾기 바꾸기
	CFindReplaceDialog *pDlg;
	Long(*scrollPositions); //페이지들의 스크롤 포지션
	CString originalPathName;
	SCROLLINFO scrollInfo;
	CPrintDialog *printDlg;
	CPageSetupDialog *pageSetUpDialog;
	CFontDialog *fontDlg;
	//되돌리기 관련
	PageStack *restoreToRearStack;
	PageStack *restoreToFrontStack;
	bool isChanged;//처음 시작한 이후 바뀐것이 있다면
	CFont *font;
	int fontSize;//글자 세로 길이
private:
	//Menu *menu;
	CStatusBar statusBar;
	bool isWritingKorean;//한글적을때 검은색 칸막이
	//CClientDC pdc;
	Long x;//첫번째 클릭된곳의 캐럿위치
	Long y;
	Long firstClickedRow;
	Long firstClickedColumn;
	Long x_;


};

#endif // _MEMOFORM_H