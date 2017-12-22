//MemoForm.cpp
#include "MemoForm.h"
#include <WinUser.h>
#include "Menu.h"
#include "Page.h"
#include "Text.h"  
#include "Row.h"
#include "LineInfo.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include <string.h>
#include "GetString.h"
#include <imm.h>//한글조함
#include "WriteKorean.h"//한글
#include <ctype.h>//영어 구분
#include "Paper.h"
#include "Caret.h"
#include "SelectedText.h"
#include <afxdlgs.h>//CDialog
#include "Load.h"
#include "CopyToMemo.h"
#include "PaintVisitor.h"
#include "MoveConnectedText.h"
#include "ConnectedInfo.h"
#include "CutString.h"
#include "LineController.h"
#include "LineFeed.h"
#include "KeyBoard.h"
#include "FindReplace.h"
#include "Save.h"
#include "Menu.h"
#include "resource.h"
#include <afxcmn.h>	//cstatusbarctrl
#include < afxstatusbar.h>
#pragma warning(disable:4996)
//#define ID_INDICATOR 0
CControlApp the;
static UINT WM_FINDREPLACE = ::RegisterWindowMessage(FINDMSGSTRING);
//static UINT BASED_CODE indicators[] {ID_INDICATOR};
BOOL CControlApp::InitInstance()
{
	MemoForm *memoForm = new MemoForm;
	CRect rect(300, 300,1000, 816);
	this->m_pMainWnd = memoForm;
	memoForm->Create(NULL, "메모장", WS_OVERLAPPEDWINDOW| WS_VSCROLL, rect);
	this->m_pMainWnd->ShowWindow(SW_SHOW);
	this->m_pMainWnd->UpdateWindow();

	return TRUE;
	
}
BEGIN_MESSAGE_MAP(MemoForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	ON_MESSAGE(WM_IME_STARTCOMPOSITION, OnStartComposition)
	ON_WM_VSCROLL()
	//ON_MESSAGE(WM_IME_CHAR, OnImeChar)
	ON_REGISTERED_MESSAGE(WM_FINDREPLACE,OnFindReplace)
	ON_MESSAGE(WM_IME_COMPOSITION, OnComposition)
	ON_COMMAND_RANGE(201,300,OnMenu)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()
MemoForm::MemoForm() {
	this->page = NULL;
	this->text = NULL;
	this->row = NULL;
	this->caret = NULL;
	this->selectedText = NULL;
	this->fontSize = 16;
	this->paper = NULL;
	this->pDlg = NULL;
	this->lineInfo = NULL;


}
LONG MemoForm::OnStartComposition(UINT wParam,LONG lParam){
	DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter;
	if (this->row->GetCurrent() < this->row->GetLength() - 1) {
		this->row->TakeIn(this->row->GetCurrent() + 1, doubleByteCharacter);
	}
	else if (this->row->GetCurrent() >= this->row->GetLength() - 1) {
		this->row->Add(doubleByteCharacter);
	}
	
	return 0;
}
LONG MemoForm::OnComposition(UINT wParam, LONG lParam) {
	//선택되어져있는게 있으면 지운다.
	if (this->selectedText != NULL) {
		this->selectedText->EraseSelectedText(this);
		this->selectedText = NULL;
	}
	WriteKorean writeKorean;
	writeKorean.Write(this, wParam, lParam);
	//한글 입력중 다른 이벤트 발생으로 입력이 끝날때
	Character *character = dynamic_cast<Character*>(this->row->GetAt(this->row->GetCurrent()));
	if (dynamic_cast<DoubleByteCharacter*>(character)) {
		if (dynamic_cast<DoubleByteCharacter*>(character)->GetAlphabet() == "") {
			this->row->Delete(this->row->GetCurrent());
		}
	}
	//화면 넘는지
	GetString getString;
	CClientDC dc(this);
	CSize size = dc.GetTextExtent(CString(getString.SubString(this->row, 0, this->row->GetLength() - 1).c_str()));
	//넘는다면 자동줄바꿈 시켜준다.
	if (size.cx > this->screenWidth) {
		MoveConnectedText moveConnectedText;
		moveConnectedText.ChangeLine(this, &dc, this->text->GetCurrent());
		//캐럿
		this->caret->MoveToCurrent(this);

	}

	InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), true);
	UpdateWindow();
	return 0;
}


int MemoForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	this->pDlg = NULL;
	this->page = new Page;
	this->text = new Text;
	this->page->Add(this->text);
	this->caret = new Caret;
	this->lineInfo = new LineInfo;
	this->selectedText = NULL;
	CRect clientRect;
	GetClientRect(&clientRect);
	this->screenWidth = clientRect.Width();
	this->screenHeight = clientRect.Height();
	this->paper = new Paper(this->screenWidth, this->screenHeight);
	this->scrollPositions = new Long[32];
	this->keyDownTextIndex = 0;
	this->keyDownTextIndex = -1;
	//배열 초기화
	Long k = 0;
	while (k < 32) {
		this->scrollPositions[k] = 0;
		k++;
	}
	
	if (this->text->GetLength() == 0) {
		this->row = new Row;
		SingleByteCharacter *singleByteCharacter = new SingleByteCharacter('\r');
		SingleByteCharacter *singleBytecharacter_ = new SingleByteCharacter('\n');
		this->row->Add(singleByteCharacter);
		this->row->Add(singleBytecharacter_);
		this->row->Move(-1);
		this->text->Add(this->row);
	}
	//스크롤 포지션 초기화
	
	CreateSolidCaret(1, this->fontSize);
	this->caret->MoveToCurrent(this);
	Menu menu(this);
	
	return 0;
}
void MemoForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {

	
	KeyBoard keyBoardAction;
	keyBoardAction.SetKeyAction(nChar, nRepCnt, nFlags);
	if (keyBoardAction.GetKeyAction() != NULL) {
		keyBoardAction.DoAction(this);
	}
	
}
void MemoForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	
	if(GetKeyState(VK_SHIFT)>=0 && GetKeyState(VK_CONTROL)>=0&&nChar!=VK_BACK&&nChar!=VK_RETURN){
		CClientDC dc(this);
		if (this->selectedText != NULL) {
			this->selectedText->EraseSelectedText(this);
			this->selectedText = NULL;
			MoveConnectedText moveConnectedText;
			moveConnectedText.ChangeLine(this, &dc, this->text->GetCurrent());
		}
		CString str;
		str.Format(_T("%c"), nChar);
		//영어

		SingleByteCharacter *singleByteCharacter = new SingleByteCharacter(*(LPCTSTR)str);
		//글의 현재위치가 줄의 길이보다 작으면
			if (this->row->GetCurrent() < this->row->GetLength() - 1) {
				this->row->TakeIn(this->row->GetCurrent() + 1, singleByteCharacter);
			}
			//글의 현재위치가 줄의 길이보다 크거나 같으면
			else if (this->row->GetCurrent() >= this->row->GetLength() - 1) {
				this->row->Add(singleByteCharacter);
			}
		
		InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), true);
		//화면 넘는지.
		GetString getString;
		
		CSize size = dc.GetTextExtent(CString(getString.SubString(this->row, 0, this->row->GetLength() - 1).c_str()));
		//넘는다면 자동줄바꿈 시켜준다.
		if (size.cx > this->screenWidth) {
			MoveConnectedText moveConnectedText;
			moveConnectedText.ChangeLine(this, &dc, this->text->GetCurrent());
			
		}
		
	}
	//캐럿
	this->caret->MoveToCurrent(this);
	//출력글자 보다 밑에 있다면 종이를 올린다.
	if (this->caret->GetY() >= this->screenHeight / this->fontSize*this->fontSize) {
		this->paper->MoveToY((this->text->GetCurrent()+1)*this->fontSize-this->screenHeight/this->fontSize*this->fontSize);
		this->scrollInfo.nPos = this->paper->GetY();
		//다시 캐럿 이동
		this->caret->MoveToCurrent(this);
	}
	//캐럿이 화면 위에 있다면
	else if (this->caret->GetY() < 0) {
		this->paper->MoveToY(this->text->GetCurrent()*this->fontSize );
		this->scrollInfo.nPos = this->paper->GetY();
		//다시 캐럿 이동
		this->caret->MoveToCurrent(this);
	}
	
}
void MemoForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	Long yInc=0;//스크롤 thumb의 이동거리
	Long i = -1;
	switch (LOWORD(nSBCode))
	{
	case SB_LINEUP: {
		yInc = i*this->fontSize;
		this->paper->MoveToY(this->paper->GetY() +yInc);
		//this->caret->MoveY(this->caret->GetY() - yInc);

	}break;
	case SB_LINEDOWN: {
		yInc = this->fontSize;
		this->paper->MoveToY(this->paper->GetY() + yInc);
		//this->caret->MoveY(this->caret->GetY() -yInc);
	}break;
	case SB_PAGEUP:
	{	
		yInc = i*(this->scrollInfo.nPage/this->fontSize*this->fontSize);
		this->paper->MoveToY(this->paper->GetY() +yInc );
		//this->caret->MoveY(this->caret->GetY() - yInc);

	}break;
	case SB_PAGEDOWN:
	{
		yInc = this->scrollInfo.nPage / this->fontSize*this->fontSize;
		this->paper->MoveToY(this->paper->GetY() +yInc );
		//this->caret->MoveY(this->caret->GetY() - yInc);
	}break;
	case SB_THUMBTRACK:
	{	
		GetScrollInfo(SB_VERT, &this->scrollInfo);
		yInc = (this->scrollInfo.nTrackPos - this->scrollInfo.nPos) / this->fontSize*this->fontSize;
		this->paper->MoveToY(this->paper->GetY() + yInc );
		//this->caret->MoveY(this->caret->GetY() - yInc);
	}break;
	default:
		break;
	}
	//위치가 스크롤 범위 넘어섰을때
	if (this->scrollInfo.nPos + yInc<0||this->paper->GetY()<0) {
		this->caret->MoveY(this->caret->GetY() + yInc);
		yInc = -this->scrollInfo.nPos;
		this->paper->MoveToY(0);
	}
	if (this->scrollInfo.nPos + yInc > this->scrollInfo.nMax||this->paper->GetY()+this->screenHeight>this->paper->GetHeight()) {
		Long previous = this->paper->GetY();
		yInc = (this->scrollInfo.nMax - this->scrollInfo.nPos-this->scrollInfo.nPage) / this->fontSize*this->fontSize;
		this->paper->MoveToY(this->paper->GetHeight()-this->screenHeight / this->fontSize*this->fontSize);
		Long distance = previous - this->paper->GetY();
		if (LOWORD(nSBCode) != SB_THUMBTRACK) {
			//this->caret->MoveY(this->caret->GetY()+distance);
		}
	}
 	//새로운 위치 설정
	this->scrollInfo.nPos = this->scrollInfo.nPos + yInc;
	//캐럿 설정
	this->caret->MoveToCurrent(this);
	//SetScrollPos(SB_VERT, this->scrollInfo.nPos);
	SetCaretPos(CPoint(this->caret->GetX(), this->caret->GetY()));
	InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), true);

}
void MemoForm::OnPaint()
{
	
	CString str;
	CPaintDC dc(this);
	
	
	//화면에 적는다.
	PaintVisitor paintVisitor(&dc,this->screenHeight,this->paper->GetY());
	this->text->Accept(&paintVisitor);
	this->fontSize = paintVisitor.GetFontSize();
	
	
	
	
	if (this->text->GetLength()*this->fontSize > (this->screenHeight/this->fontSize)*this->fontSize) {
		this->paper->ModifyHeight(this->text->GetLength()*this->fontSize);

	}
	else {
		this->paper->ModifyPaper(this->screenWidth,this->screenHeight / this->fontSize *this->fontSize);
	}
	this->scrollInfo.nMax = this->paper->GetHeight()+this->screenHeight%this->fontSize;
	SetScrollInfo(SB_VERT, &this->scrollInfo);
	SetScrollPos(SB_VERT, this->scrollInfo.nPos);
	
	//스크롤 위치 저장
	this->scrollPositions[this->page->GetCurrent()] = this->scrollInfo.nPos;
	//선택하기있으면 출력
	if (this->selectedText != NULL) {
		this->selectedText->DrawUnderLine(this);
	}
}

//마우스 클릭 캐럿 이동
void MemoForm::OnLButtonDown(UINT nFlags, CPoint point) {
	HideCaret();
	if (this->selectedText != NULL) {
		delete this->selectedText;
		this->selectedText = NULL;
	}
	
	CClientDC dc(this);
	this->caret->MoveToPoint(this, &dc, point);
	this->firstClickedRow= this->text->GetCurrent();
	this->firstClickedColumn = this->row->GetCurrent();
	
	
	//출력글자 보다 밑에 있다면 종이를 올린다.
	if (this->caret->GetY() >= this->screenHeight / this->fontSize*this->fontSize) {
		this->paper->MoveToY(this->paper->GetY() + this->fontSize);
		this->scrollInfo.nPos = this->paper->GetY();
		this->caret->MoveToCurrent(this);
	}
	InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), true);
}

void MemoForm::OnMouseMove(UINT nFlags, CPoint point){
	
	Long x = point.x;
	Long y = point.y;
	CClientDC dc(this);
	CSize size_;

	if (nFlags == MK_LBUTTON) {
		HideCaret();
		this->selectedText = new SelectedText;

		//캐럿 이동
		CClientDC dc(this);
		this->caret->MoveToPoint(this, &dc, point);
		//출력글자 보다 밑에 있다면 종이를 올린다.
		if (this->caret->GetY() >= this->screenHeight / this->fontSize*this->fontSize) {
			this->paper->MoveToY(this->paper->GetY() + this->fontSize);
			this->scrollInfo.nPos = this->paper->GetY();
			this->caret->MoveToCurrent(this);
			InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), true);

		}
		//텍스트 선택시작.************************************************
		//현재 위치 저장
		Long startRow;
		Long startColumn;
		Long endRow;
		Long endColumn;
		//마우스가 더블클릭된곳보다 상단에 있을때
		if (this->text->GetCurrent() < this->firstClickedRow) {
			startRow = this->text->GetCurrent();
			endRow = this->firstClickedRow;
			startColumn = this->row->GetCurrent() + 1;
			endColumn = this->firstClickedColumn;
		}
		else if (this->text->GetCurrent() > this->firstClickedRow) {
			startRow = this->firstClickedRow;
			endRow = this->text->GetCurrent();
			startColumn = this->firstClickedColumn + 1;
			endColumn = this->row->GetCurrent();
		}
		//같은줄 이라면
		else if (this->text->GetCurrent() == this->firstClickedRow) {
			startRow = this->firstClickedRow;
			endRow = this->text->GetCurrent();
			//현재 위치가 처음보다 왼쪽이라면
			if (this->row->GetCurrent() < this->firstClickedColumn) {
				startColumn = this->row->GetCurrent() + 1;
				endColumn = this->firstClickedColumn;
			}
			else if (this->row->GetCurrent() >= this->firstClickedColumn) {
				startColumn = this->firstClickedColumn + 1;
				endColumn = this->row->GetCurrent();
			}
		}
		//선택될곳 셋팅
		this->selectedText->Select(this, startRow, startColumn, endRow, endColumn);
		if (startRow >= endRow&&startColumn > endColumn) {
			delete this->selectedText;
			this->selectedText = NULL;
		}
		InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), false);
		UpdateWindow();
	}
}
	
BOOL MemoForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	if (zDelta < 0) {
		this->paper->MoveToY(this->paper->GetY() + this->fontSize * 3);
	}
	else if (zDelta > 0) {
		this->paper->MoveToY(this->paper->GetY() - this->fontSize * 3);
	}
	if (this->paper->GetY() < 0) {
		this->paper->MoveToY(0);
	}
	if (this->paper->GetY() > this->paper->GetHeight()-this->screenHeight/this->fontSize*this->fontSize) {
		this->paper->MoveToY(this->paper->GetHeight() - this->screenHeight / this->fontSize*this->fontSize);
	}
	this->scrollInfo.nPos= this->paper->GetY();
	InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), true);
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

//찾기 
LONG MemoForm::OnFindReplace(WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(wParam);
	HideCaret();

	this->pDlg = CFindReplaceDialog::GetNotifier(lParam);

	if (this->pDlg != NULL&&this->pDlg->IsTerminating()==0) {
		FindReplace findReplace;
		findReplace.FindString(this);
		if (this->pDlg->ReplaceCurrent() != 0) {
			findReplace.ReplaceString(this);
		}
		//모두 바꾸기
		else if (this->pDlg->ReplaceAll() != 0 && !this->pDlg->IsTerminating()) {
			if (this->selectedText != NULL) {
				delete this->selectedText;
				this->selectedText = NULL;
			}
			findReplace.ReplaceAll(this);
		}
	}
	if (this->pDlg->IsTerminating()!=0) {
		//동적할당한거 해제시켜줘야함*************************아직 못해줌
		this->pDlg = NULL;
	}
	return 0;
}

void MemoForm::OnSize(UINT nType, int cx, int cy) {
	Long temp = this->screenWidth;
	this->screenWidth = cx;
	this->screenHeight = cy;
	this->scrollInfo.cbSize = sizeof(this->scrollInfo);
	this->scrollInfo.fMask = SIF_ALL;
	this->scrollInfo.nMin = 0;
	this->scrollInfo.nMax = this->paper->GetHeight()+this->screenHeight%this->fontSize;
	this->scrollInfo.nPage = cy;
	SetScrollInfo(SB_VERT, &this->scrollInfo);
	//자동 줄바꿈
	if (temp != this->screenWidth) {
		LineController lineController;
		CDC *dc = GetDC();
		lineController.AutomaticLineChange(this, dc);
		InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), true);
		UpdateWindow();
	}
	
}
void MemoForm::OnMenu(UINT nID) {
	Menu menu(this);
	menu.SetMenuAction(nID);
	menu.DoAction();
	//캐럿
	this->caret->MoveToCurrent(this);
	//출력글자 보다 밑에 있다면 종이를 올린다.
	if (this->caret->GetY() >= this->screenHeight / this->fontSize*this->fontSize) {
		this->paper->MoveToY((this->text->GetCurrent() + 1)*this->fontSize - this->screenHeight / this->fontSize*this->fontSize);
		this->scrollInfo.nPos = this->paper->GetY();
		//다시 캐럿 이동
		this->caret->MoveToCurrent(this);
	}
	//캐럿이 화면 위에 있다면
	else if (this->caret->GetY() < 0) {
		this->paper->MoveToY(this->text->GetCurrent()*this->fontSize);
		this->scrollInfo.nPos = this->paper->GetY();
		//다시 캐럿 이동
		this->caret->MoveToCurrent(this);
	}
}
void MemoForm::OnClose() {
	CWnd::EnableWindow(false);
	if (this->page != NULL) {
		//저장하기
		//메세지박스 출력
		int ret = MessageBox(_T("변경내용을 제목없음에 저장하시겠습니까?"), _T("메모장"), MB_YESNOCANCEL);
		if (ret == IDYES) {
			CString savePath = this->originalPathName;
			if (this->originalPathName == "") {
				CFileDialog dlg(FALSE, "*.txt", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "text Files(*.txt)|*.txt|");
				if (dlg.DoModal() == IDOK) {
					savePath = dlg.GetPathName();
				}
			}
			Save save;
			save.SaveMemo(this, (LPCTSTR)savePath);
			CFrameWnd::OnClose();
		}
		else if (ret == IDNO) {
			if (this->page != NULL) {
				delete this->page;
			}
			CFrameWnd::OnClose();
		}
	}
	CWnd::EnableWindow(true);
}



