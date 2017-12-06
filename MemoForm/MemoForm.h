//MemoForm.h
#ifndef _MEMOFORM_H
#define _MEMOFORM_H
#include <afxwin.h>
#include < afxdlgs.h>
#include < afxext.h>
#include "CStatusButton.h"
#include "Array.h"
class Page;
class Text;
class Character;
class SingleByteCharacter;
class DoubleByteCharacter;
class Row;
class Text;
class Paper;
class Caret;
//class GetString;
class SelectedText;
typedef signed long int Long;
class CControlApp : public CWinApp
{
public:
	//CControlApp();
	BOOL InitInstance();


};
class MemoForm : public CFrameWnd
{
public:
	MemoForm();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LONG OnStartComposition(UINT wParam,LONG lParam);
	afx_msg LONG OnComposition(UINT wParam, LONG lParam);
	afx_msg void OnKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags);
	//afx_msg LONG OnImeChar(UINT wParam, LONG lParam);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LONG OnFindReplace(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnClose();
	//afx_msg void OnButtonCliked(UINT uiID);//버튼 클릭시

	DECLARE_MESSAGE_MAP()
private:
	CFindReplaceDialog *pDlg;
	CStatusBar statusBar;
	Page *page;
	Text *text;
	Row *row;
	Caret *caret;
	Paper *paper;
	//CClientDC pdc;
	SelectedText *selectedText;
	char wszComp[2];
	int y_;//글자 세로 길이
	Long screenHeight;
	Long screenWidth;
	SCROLLINFO scrollInfo;
	Long(*scrollPositions); //페이지들의 스크롤 포지션
	//텍스트 선택 관련
	Long x;//첫번째 클릭된곳의 캐럿위치
	Long y;
	Long firstClickedRow;
	Long firstClickedColumn;
	Long x_;

	CString currentPath;
private:
	/*CButton addPageButton;
	CButton trashPageButton;
	CButton previousButton;
	CButton nextButton;
	
	//CStatusButton (*pageButtons);
	Array<CStatusButton*> *pageButtons;*/
};

#endif // _MEMOFORM_H