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
	//virtual BOOL PreTranslateMessage(MSG* pMsg);
	
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
	//afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnClose();
	//afx_msg void OnButtonCliked(UINT uiID);//��ư Ŭ����

	DECLARE_MESSAGE_MAP()
public:

	Page *page;
	Text *text;
	Row *row;
	Paper *paper;
	int fontSize;//���� ���� ����
	LineInfo *lineInfo;
	Long screenWidth;
	Long screenHeight;
	Caret *caret;
	SelectedText *selectedText;
	//Ű ������������ ���� ��ġ ����
	Long keyDownTextIndex;
	Long keyDownRowIndex;
	//ã�� �ٲٱ�
	CFindReplaceDialog *pDlg;
	Long(*scrollPositions); //���������� ��ũ�� ������
	CString originalPathName;
private:
	CStatusBar statusBar;
	
	//CClientDC pdc;
	char wszComp[2];
	SCROLLINFO scrollInfo;
	//�ؽ�Ʈ ���� ����
	Long x;//ù��° Ŭ���Ȱ��� ĳ����ġ
	Long y;
	Long firstClickedRow;
	Long firstClickedColumn;
	Long x_;

	CString currentPath;
	/*CButton addPageButton;
	CButton trashPageButton;
	CButton previousButton;
	CButton nextButton;
	
	//CStatusButton (*pageButtons);
	Array<CStatusButton*> *pageButtons;*/
};

#endif // _MEMOFORM_H