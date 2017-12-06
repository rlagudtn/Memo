//MemoForm.cpp
#include "MemoForm.h"
#include <WinUser.h>
#include "Page.h"
#include "Text.h"  
#include "Row.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include <string.h>
#include "GetString.h"
#include <imm.h>//한글조함
#include <ctype.h>//영어 구분
#include "Paper.h"
#include "Caret.h"
#include "SelectedText.h"
#include <afxdlgs.h>//CDialog
#include "Load.h"
#include "CopyToMemo.h"
#include "PaintVisitor.h"
#include "EraseSelectedText.h"
#include "resource.h"
#include <afxcmn.h>	//cstatusbarctrl
#include < afxstatusbar.h>
//#include "CStatusButton.h"//만든 버튼
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
	ON_MESSAGE(WM_IME_STARTCOMPOSITION, OnStartComposition)
	ON_WM_VSCROLL()
	//ON_MESSAGE(WM_IME_CHAR, OnImeChar)
	ON_REGISTERED_MESSAGE(WM_FINDREPLACE,OnFindReplace)
	ON_MESSAGE(WM_IME_COMPOSITION, OnComposition)
	//ON_COMMAND_RANGE(IDI_ADDICON,200,MemoForm::OnButtonCliked)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
END_MESSAGE_MAP()
MemoForm::MemoForm() {
	this->page = NULL;
	this->text = NULL;
	this->row = NULL;
	this->caret = NULL;
	this->selectedText = NULL;
	this->y_ = 16;
	this->paper = NULL;
	this->pDlg = NULL;
	//this->pageButtons = NULL;
	


}
BOOL MemoForm::PreTranslateMessage(MSG* pMsg) {

	if (pMsg->message == WM_KEYDOWN) {
		CClientDC dc(this);
		CSize size_;
		CString str_;

		if (!GetKeyState(VK_SHIFT)&&pMsg->wParam == VK_LEFT) {
			//첫줄이 아니고 맨 왼쪽이 아닐때
			
			if (this->caret->GetX()!=0) {
				Character *character = dynamic_cast<Character*>(row->GetAt(this->row->GetCurrent()));
				if (dynamic_cast<SingleByteCharacter*>(character)) {
					str_ = dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet();
					
				}
				else if (dynamic_cast<DoubleByteCharacter*>(character)) {
					str_ = dynamic_cast<DoubleByteCharacter*>(character)->GetAlphabet();
				}
				size_ = dc.GetTextExtent(str_);
				this->caret->MoveX(this->caret->GetX() - size_.cx);
				this->row->Move(this->row->GetCurrent() - 1);
				SetCaretPos(CPoint(this->caret->GetX(), this->caret->GetY()));    //위치 설정
				ShowCaret();
			}
			//첫줄이 아니고 맨 왼쪽일때
			else if (this->caret->GetX() == 0 && this->caret->GetY() != 0) {
				this->row = dynamic_cast<Row*>(this->text->Move(this->text->GetCurrent() - 1));
				this->row->Move(this->row->GetLength() - 1);
				
				GetString getString(0, this->text->GetCurrent());
				size_ = dc.GetTextExtent(CString(getString.GetStr().c_str()));
				this->caret->Move(size_.cx, this->caret->GetY() -this->y_);
				SetCaretPos(CPoint(this->caret->GetX(), this->caret->GetY()));    //위치 설정
				ShowCaret();
			}

			//첫번째 줄의 맨 왼쪽일때
			else if(this->caret->GetX()==0&&this->caret->GetY()==0) {
				//화면 스크롤
			}

		}
		
	}
	UpdateWindow();
	return CFrameWnd::PreTranslateMessage(pMsg);
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
	
		int nLength = 0;
		this->wszComp[2] = { 0, };
		int cxBuffer;
		HIMC hImc = ImmGetContext(GetSafeHwnd());
		HDC hdc = ::GetDC(GetSafeHwnd());
		if (lParam&GCS_COMPSTR) {
			nLength = ImmGetCompositionString(hImc, GCS_COMPSTR, NULL, 0);
			if (nLength > 0) {
				//캐럿 이동;
				GetCharWidth(hdc, wParam, wParam, &cxBuffer);
				//SetCaretPos(CPoint(this->caret->GetX() + cxBuffer, this->caret->GetY()));
				//글자 적기
				ImmGetCompositionString(hImc, GCS_COMPSTR,this->wszComp, nLength);
				DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter((LPSTR)(LPCTSTR)this->wszComp);
				this->row->Modify(this->row->GetCurrent(), doubleByteCharacter);
			}
			string temp = to_string(this->row->GetLength());
			Long x = 300;
			Long y = 200;
			TextOut(hdc, x, y, temp.c_str(), 4);
			//저장되는지 확인->w저장은 됨
		}
		else if (lParam&GCS_RESULTSTR) {
			nLength = ImmGetCompositionString(hImc, GCS_RESULTSTR, NULL, 0);
			if (nLength > 0) {
				//캐럿 이동;
				GetCharWidth(hdc, wParam, wParam, &cxBuffer);
				//SetCaretPos(CPoint(this->caret->GetX() + cxBuffer, this->caret->GetY()));
				//글자 적기
				ImmGetCompositionString(hImc, GCS_RESULTSTR,this->wszComp, nLength);
				DoubleByteCharacter *doubleByteCharacter = new DoubleByteCharacter((LPSTR)(LPCTSTR)this->wszComp);
				this->row->Modify(this->row->GetCurrent(), doubleByteCharacter);
				//다음칸에 넣어질 칸을 넣는다
				DoubleByteCharacter *doubleByteCharacter_ = new DoubleByteCharacter;
				if (this->row->GetCurrent() < this->row->GetLength() - 1) {
					this->row->TakeIn(this->row->GetCurrent() + 1, doubleByteCharacter_);
				}
				//글의 현재위치가 줄의 길이보다 크거나 같으면
				else if (this->row->GetCurrent() >= this->row->GetLength() - 1) {
					this->row->Add(doubleByteCharacter_);
				}
				this->caret->MoveX(this->caret->GetX() + cxBuffer);
			}
		}
		//SendMessage(WM_CHAR);
		InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight ),false);
		UpdateWindow();

		return 0;
}
/*LONG MemoForm::OnImeChar(UINT wParam, LONG lParam) {
	Invalidate(true);
	return  0;
}*/


int MemoForm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//HIMC hImc = ImmGetContext(GetSafeHwnd());
	//ImmSetConversionStatus(hImc, IME_CMODE_HANGUL, IME_SMODE_CONVERSATION);
	//ImmReleaseContext(GetSafeHwnd(), hImc);
	this->pDlg = NULL;
	this->page = new Page;
	this->text = new Text;
	this->page->Add(this->text);
	this->caret = new Caret;
	this->selectedText = NULL;
	CRect clientRect;
	GetClientRect(&clientRect);
	this->screenWidth = clientRect.Width();
	this->screenHeight = clientRect.Height();
	this->paper = new Paper(this->screenWidth, this->screenHeight);
	this->scrollPositions = new Long[32];
	//배열 초기화
	Long k = 0;
	while (k < 32) {
		this->scrollPositions[k] = 0;
		k++;
	}
	//불러오기
	CFileDialog dlg(true, "*.txt", NULL, OFN_FILEMUSTEXIST, "text Files(*.txt)|*.txt|", NULL);
	if (dlg.DoModal() == IDOK) {
		CStdioFile file;
		CString str;
		CClientDC dc(this);
		if (file.Open(dlg.GetPathName(), CFile::modeRead)) {
			while (file.ReadString(str)) {
				if (str != '\f') {
					
					Load load(&dc,this->screenWidth,(LPCTSTR)str);
					this->text->Accept(&load);
				}
				else {
					this->text->Move(0);
					Text *text=new Text;
					this->page->Add(text);
					this->text = dynamic_cast<Text*>(this->page->GetAt(this->page->GetCurrent()));
				}
			}
			file.Close();
		}
		this->text =dynamic_cast<Text*>( this->page->Move(0));
		this->row = dynamic_cast<Row*>(this->text->Move(0));
		this->row->Move(-1);

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
	
	this->x_ = 0;
	CreateSolidCaret(1, this->y_);
	/*//상태바 생성
	this->statusBar.Create(this, WS_CLIPCHILDREN | WS_VISIBLE | CBRS_BOTTOM);
	this->statusBar.SetIndicators(ID_INDICATOR, 2);
	this->statusBar.SetPaneInfo(0, ID_INDICATOR, SBPS_NOBORDERS, this->screenWidth - 200);
	this->statusBar.SetPaneInfo(1, ID_INDICATOR, SBPS_NORMAL, 200);
	//상태표시줄 크기 변경
	//상태표시줄 생성
	CRect rect;
	rect.left = 0;
	rect.right =25;
	rect.bottom= 25;
	//페이지 생성 버튼
	HICON hIcon = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ADDICON), IMAGE_ICON, 16, 16, 0);
	this->addPageButton.Create(_T(""), WS_CHILD | WS_VISIBLE | BS_ICON | BS_PUSHBUTTON, rect, &this->statusBar, IDI_ADDICON);
	this->addPageButton.SetIcon(hIcon);
	
	//페이지 삭제 버튼
	
	rect.right = this->screenWidth - 200;
	rect.left = rect.right - 25;

	hIcon = (HICON)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_TRASHICON), IMAGE_ICON, 16, 16, 0);
	this->trashPageButton.Create(_T(""), WS_CHILD | WS_VISIBLE | BS_ICON | BS_PUSHBUTTON, rect, &this->statusBar, IDI_TRASHICON);
	this->trashPageButton.SetIcon(hIcon);
	//왼쪽으로 이동버튼

	//페이지 버튼
	CStatusButton *pageButton = new CStatusButton;
	pageButton->Create(_T("page"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, CRect(75  , 0, 75 +100, 25), &this->statusBar, 105 );
	this->pageButtons = new Array<CStatusButton*>(16);
	this->pageButtons->Store(0, pageButton);*/
	//캐럿
	//SetCaretPos(CPoint(this->caret->GetX(), this->caret->GetY()));
	//ShowCaret();
	
	//((CStatusBarCtrl&)this->statusBar.GetStatusBarCtrl()).SetIcon(2, hIcon);

	return 0;
}
void MemoForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	
	if (GetKeyState(VK_CONTROL)<0) {
		switch (nChar) {
			//CTRL+V
		case 0x56: {
			if (IsClipboardFormatAvailable(CF_TEXT)) {
				OpenClipboard();
				HANDLE hClipboardData = GetClipboardData(CF_TEXT);
				CString *str=(CString*)GlobalLock(hClipboardData);
				GlobalUnlock(hClipboardData);
				//붙여넣기 하기 전의 선택된줄 뒤의 텍스트들을 복사한다
				
				SelectedText selectedText;
				selectedText.SetTextPosition(this->text->GetCurrent(), this->row->GetCurrent() + 1, this->text->GetCurrent(), this->row->GetLength()-1 );//-2인 이유는 뒤의 \n을 인위적으로 빼줌..여기서만
				this->text->Accept(&selectedText);
				//뒤의 텍스트를 지운다.
				EraseSelectedText eraseSelectedText(this->text->GetCurrent(), this->row->GetCurrent() + 1, this->text->GetCurrent(), this->row->GetLength() - 1);
				this->text->Accept(&eraseSelectedText);
				CClientDC dc(this);
				CopyToMemo copyToMemo(&dc,this->screenWidth,(LPCTSTR)str);
				this->text->Accept(&copyToMemo);
				this->row = dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent()));
				//현 위치 임시저장
				Long textCurrent = this->text->GetCurrent();
				Long rowCurrent = this->row->GetCurrent();
				//임시저장한 텍스트를 다시 적는다.
				CString remainText = CString(selectedText.GetBuffer().c_str());
				remainText.Replace("\r\n", "\r");
				CopyToMemo copyAgain(&dc, this->screenWidth, (LPCTSTR)remainText);
				this->text->Accept(&copyAgain);
				//마지막에 \n 추가
				SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
				dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent()))->Add(lineFeed);
				//현재 위치를 원 상태로 돌린다
				this->row = dynamic_cast<Row*>(this->text->Move(textCurrent));
				this->row->Move(rowCurrent);
			}
		}break;
			//CTRL+C
		case 0x43: {
			CString copiedStr = "";
			if (this->selectedText != NULL) { 
			copiedStr = CString(this->selectedText->GetBuffer().c_str());
			}
			HGLOBAL hGloBal = GlobalAlloc(GHND | GMEM_SHARE,(lstrlen(copiedStr) + 1) * sizeof(TCHAR));

			PSTR pStr = (PSTR)GlobalLock(hGloBal);
			if (pStr != NULL) {
				lstrcpy(pStr, TEXT(copiedStr));

				// 락 해제
				GlobalUnlock(pStr);

				// 클립보드 오픈
				OpenClipboard();

				// 클립보드 초기화
				EmptyClipboard();

				// 클립보드에 복사
				SetClipboardData(CF_TEXT,pStr);

				// 클립보드 클로즈
				CloseClipboard();

				
			}
		}break;
			//CTRL+X
		case 0x58: {
			CString copiedStr = "";
			if (this->selectedText != NULL) {
				copiedStr = CString(this->selectedText->GetBuffer().c_str());

				HGLOBAL hGloBal = GlobalAlloc(GHND | GMEM_SHARE, (lstrlen(copiedStr) + 1) * sizeof(TCHAR));

				PSTR pStr = (PSTR)GlobalLock(hGloBal);
				if (pStr != NULL) {
					lstrcpy(pStr, TEXT(copiedStr));

					// 락 해제
					GlobalUnlock(pStr);

					// 클립보드 오픈
					OpenClipboard();

					// 클립보드 초기화
					EmptyClipboard();

					// 클립보드에 복사
					SetClipboardData(CF_TEXT, pStr);

					// 클립보드 클로즈
					CloseClipboard();
				}
				
				//선택된 곳부터 만 삭제
				EraseSelectedText eraseSelectedText(this->selectedText->GetStartRow(), this->selectedText->GetStartColumn(), this->selectedText->GetEndRow(), this->selectedText->GetEndColumn());
				this->text->Accept(&eraseSelectedText);
				
				//현재 위치를 원 상태로 돌린다.
				this->row = dynamic_cast<Row*>(this->text->Move(this->text->GetCurrent()));
				if (this->selectedText != NULL) {
					delete this->selectedText;
					this->selectedText = NULL;
				}

				InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), true);
				UpdateWindow();
			}
		}break;
			//CTRL+F
		case 0x46: {
			if (this->pDlg==	NULL )
			{
				this->pDlg = new CFindReplaceDialog;  // Must be created on the heap

				pDlg->Create(TRUE, _T(""), _T(""), FR_HIDEUPDOWN | FR_HIDEWHOLEWORD, this);
				HideCaret();
				pDlg->CreateSolidCaret(1,this->y_);
				pDlg->ShowCaret();
				pDlg->SetFocus();
			}
		}break;
			//CTRL+H
		case 0x48: {
			if (this->pDlg == NULL)
			{
				HideCaret();
				pDlg = new CFindReplaceDialog;  // Must be created on the heap
			
				pDlg->Create(FALSE, _T(""), _T(""), FR_HIDEUPDOWN | FR_HIDEWHOLEWORD, this);
				
			}
		}break;
		default:break;
		}

	}
	else if (GetKeyState(VK_SHIFT) < 0) {
		switch (nChar)	
		{
			//페이지 생성 A키
		case VK_TAB: {
			/*//기존 페이지에 '\f'추가
			Row *row_ = dynamic_cast<Row*>(this->text->GetAt(this->text->GetLength() - 1));
			SingleByteCharacter *formFeed = new SingleByteCharacter('\f');
			row_->Add(formFeed);
			*/
			Text *text = new Text;
			if(this->page->GetCurrent()<this->page->GetLength()-1){
				this->page->TakeIn(this->page->GetCurrent() + 1, text);
			}
			else {
				this->page->Add(text);
			}
			this->text = dynamic_cast<Text*>(this->page->GetAt(this->page->GetCurrent()));
			Row *row = new Row;
			SingleByteCharacter *carriageReturn = new SingleByteCharacter('\r');
			SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
			row->Add(carriageReturn);
			row->Add(lineFeed);
			row->Move(-1);
			this->text->Add(row);
			this->row = dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent()));
			this->paper->ModifyPaper(this->screenWidth, this->screenHeight);
			this->paper->MoveToY(0);
		}break;
			//페이지 삭제 s키
		case  VK_SPACE : {
			this->page->Delete(this->page->GetCurrent());
			if (this->page->GetCurrent() < this->page->GetLength() - 1) {
				this->page->Move(this->page->GetCurrent() + 1);
			}
			//페이지가 아예 없으면 새로 생성
			if (this->page->GetLength() == 0) {
				Text *text = new Text;
				this->page->Add(text);
				this->text = dynamic_cast<Text*>(this->page->GetAt(this->page->GetCurrent()));
				Row *row = new Row;
				SingleByteCharacter *carriageReturn = new SingleByteCharacter('\r');
				SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
				row->Add(carriageReturn);
				row->Add(lineFeed);
				row->Move(-1);
				this->text->Add(row);
				this->row = dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent()));
				
			}
			
		}break;
			//페이지 이전으로 이동
		case VK_LEFT: {
			if (this->page->GetCurrent() > 0) {
				this->text=dynamic_cast<Text*>(this->page->Move(this->page->GetCurrent() - 1));
				this->row = dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent()));
				//스크롤 위치 변경
				this->paper->MoveToY(this->scrollPositions[this->page->GetCurrent()]);
				this->scrollInfo.nPos = this->scrollPositions[this->page->GetCurrent()];
				SetScrollPos(SB_VERT, this->scrollInfo.nPos);
			}
		}break;
			//페이지 다음 이동
		case VK_RIGHT: {
			if (this->page->GetCurrent()  <this->page->GetLength()-1) {
				this->text = dynamic_cast<Text*>(this->page->Move(this->page->GetCurrent() + 1));
				this->row = dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent()));
				//스크롤 위치 변경
				this->paper->MoveToY(this->scrollPositions[this->page->GetCurrent()]);
				this->scrollInfo.nPos = this->scrollPositions[this->page->GetCurrent()];
				SetScrollPos(SB_VERT, this->scrollInfo.nPos);
			}
		}break;
		default:
			break;
		}
		Invalidate(true);
	}
	
}
void MemoForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	

	if (nChar == VK_RETURN) {
		//캐럿을 숨긴다
		HideCaret();
		//현재 위치 이후의 텍스트를 옮긴다.
		SelectedText selectedText;
		selectedText.SetTextPosition(this->text->GetCurrent(), this->row->GetCurrent() + 1, this->text->GetCurrent(), this->row->GetLength()-1 );
		this->text->Accept(&selectedText);

		//옮긴텍스트를 기존 종이에서 삭제한다.
		EraseSelectedText eraseSelectedText(this->text->GetCurrent(), this->row->GetCurrent() + 1, this->text->GetCurrent(), this->row->GetLength() - 1);
		this->text->Accept(&eraseSelectedText);
		//\r,\n추가
		SingleByteCharacter *singleByteCharacter = new SingleByteCharacter('\r');
		this->row->Add(singleByteCharacter);
		SingleByteCharacter *singleByteCharacter_ = new SingleByteCharacter('\n');
		this->row->Add(singleByteCharacter_);

		//새로운 줄 생성
		this->row = new Row;
		//text에 저장
		if (this->text->GetCurrent() < this->text->GetLength() - 1) {
			this->text->TakeIn(this->text->GetCurrent() + 1, this->row);
		}
		else if (this->text->GetCurrent() >= this->text->GetLength() - 1) {
			this->text->Add(this->row);
		}
		//current저장
		Long textCurrent = this->text->GetCurrent();
		Long rowCurrent = this->row->GetCurrent();
		//삭제했던 텍스트를 다시 적는다.
		CClientDC dc(this);
		CString tempString = CString(selectedText.GetBuffer().c_str());
		tempString.Replace("\r\n", "\r");
		CopyToMemo copyToMemo(&dc, this->screenWidth, (LPCTSTR)tempString);
		this->text->Accept(&copyToMemo);
		//현재위치 변경
		this->row = dynamic_cast<Row*>(this->text->Move(textCurrent));
		SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
		this->row->Add(lineFeed);
		this->row->Move(rowCurrent);
		//캐럿 위치  여기서만 변경
		this->caret->Move(0, this->caret->GetY() + this->y_);
		InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), true);
		//UpdateWindow();
	}
	else if (nChar == VK_BACK) {
		if (this->text->GetCurrent() != 0 ||this->row->GetCurrent() != -1) {
			Long currentText;
			Long currentRow;
			if (this->row->GetCurrent() >= 0) {
				this->row->Delete(this->row->GetCurrent());
				//현재줄 먼저 저장.
				currentText = this->text->GetCurrent();
				currentRow = this->row->GetCurrent();
			}
			//행의 맨 처음일때
			else {
				//이전줄의 \r\n을 지운다.
				Row *previousRow = dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent() - 1));
				previousRow->Delete(previousRow->GetLength() - 1);
				previousRow->Delete(previousRow->GetLength() - 1);
				currentText = this->text->GetCurrent() - 1;
				currentRow = previousRow->GetLength() - 1;
			}
			//연결되어져있는줄이 있는지 확인한다.
			bool isConnected = false;
			Row *currentTemp = dynamic_cast<Row*>(this->text->GetAt(currentText));
			Character *character = dynamic_cast<Character*>(currentTemp->GetAt(currentTemp->GetLength() - 1));
			if (dynamic_cast<SingleByteCharacter*>(character)) {
				if (dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet() != '\n') {
					isConnected = true;
				}
			}
			if (isConnected == true) {
				CClientDC dc(this);

				bool isLineFeed = false;
				Long k = this->text->GetCurrent();
				Row *row;
				Character *character;
				char alphabet;
				while (isLineFeed != true) {
					row = dynamic_cast<Row*>(this->text->GetAt(k));
					character = dynamic_cast<Character*>(row->GetAt(row->GetLength() - 1));
					if (dynamic_cast<SingleByteCharacter*>(character)) {
						alphabet = dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet();
						if (alphabet == '\n') {
							isLineFeed = true;
						}
					}
					k++;
				}
				Long endRow = k - 1;
				//이어진줄까지 선택한다.
				SelectedText selectedText(&dc, this->paper->GetX(), this->paper->GetY());
				selectedText.SetTextPosition(currentText, currentRow, endRow, dynamic_cast<Row*>(this->text->GetAt(endRow))->GetLength() - 1);
				this->text->Accept(&selectedText);
				//지운다.
				EraseSelectedText eraseText(currentText, currentRow, endRow, dynamic_cast<Row*>(this->text->GetAt(endRow))->GetLength() - 1);
				this->text->Accept(&eraseText);
				//다시 쓴다.
				CString writeAgain = CString(selectedText.GetBuffer().c_str());
				writeAgain.Replace("\r\n", "\r");
				CopyToMemo copyToMemo(&dc, this->screenWidth, (LPCTSTR)writeAgain);
				this->text->Accept(&copyToMemo);
				//마지막줄에 \n추가
				row = dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent()));
				SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
				row->Add(lineFeed);
				//현재줄로 다시 이동
				this->row = dynamic_cast<Row*>(this->text->Move(currentText));
				this->row->Move(currentRow);

			}
			InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), true);
		}
	}
	else if(GetAsyncKeyState(VK_SHIFT)==0&& GetAsyncKeyState(VK_CONTROL)==0){
		Long index = 0;
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
		GetString getString(0, this->row->GetLength() - 1);
		this->row->Accept(&getString);
		CClientDC dc(this);
		CSize size = dc.GetTextExtent(CString(getString.GetStr().c_str()));
		//넘는다면
		if (size.cx > this->screenWidth) {
			//현재줄 저장
			Long currentText = this->text->GetCurrent();;
			Long currentRow = this->row->GetCurrent();;
			GetString currentString(0, this->row->GetCurrent());
			this->row->Accept(&currentString);
			size = dc.GetTextExtent(CString(currentString.GetStr().c_str()));
			if (size.cx > this->screenWidth) {
				currentText = this->text->GetCurrent() + 1;
				currentRow = 0;
			}
			//else {
				//currentText = this->text->GetCurrent() + 1;
				//currentRow = 0;
			//}

			//연결되어져 있는 줄까지.
			bool isLineFeed = false;
			Long k = this->text->GetCurrent();
			Row *row;
			Character *character;
			char alphabet;
			while (isLineFeed != true) {
				row = dynamic_cast<Row*>(this->text->GetAt(k));
				character = dynamic_cast<Character*>(row->GetAt(row->GetLength() - 1));
				if (dynamic_cast<SingleByteCharacter*>(character)) {
					alphabet = dynamic_cast<SingleByteCharacter*>(character)->GetAlphabet();
					if (alphabet == '\n') {
						isLineFeed = true;
					}
				}
				k++;
			}
			Long endRow = k - 1;
			//이어진줄까지 선택한다.
			SelectedText selectedText(&dc, this->paper->GetX(), this->paper->GetY());
			selectedText.SetTextPosition(this->text->GetCurrent(), this->row->GetCurrent(), endRow, dynamic_cast<Row*>(this->text->GetAt(endRow))->GetLength() - 1);
			this->text->Accept(&selectedText);
			//지운다.
			EraseSelectedText eraseText(this->text->GetCurrent(), this->row->GetCurrent(), endRow, dynamic_cast<Row*>(this->text->GetAt(endRow))->GetLength() - 1);
			this->text->Accept(&eraseText);
			//새줄을 추가한다.
			/*Row *newRow = new Row;
			if (text->GetCurrent() < text->GetLength() - 1) {
				text->TakeIn(text->GetCurrent() + 1, newRow);
			}
			else if (text->GetCurrent() >= text->GetLength() - 1) {
				text->Add(newRow);
			}*/			//다시 쓴다.
			CString writeAgain = CString(selectedText.GetBuffer().c_str());
			writeAgain.Replace("\r\n", "\r");
			CopyToMemo copyToMemo(&dc, this->screenWidth, (LPCTSTR)writeAgain);
			this->text->Accept(&copyToMemo);
			//마지막줄에 \n추가
			row = dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent()));
			SingleByteCharacter *lineFeed = new SingleByteCharacter('\n');
			row->Add(lineFeed);

			//현재줄로 다시 이동
			this->row = dynamic_cast<Row*>(this->text->Move(currentText));
			this->row->Move(currentRow);
		}
	}
	//스크롤 관련
	//마지막줄에서 한줄 내리기
	if (this->caret->GetY()  >= this->screenHeight / this->y_*this->y_) {
		this->paper->MoveToY(this->paper->GetY()+ this->y_);
		this->scrollInfo.nPos =this->paper->GetY();
		SetScrollPos(SB_VERT, this->scrollInfo.nPos);
	}
	//캐럿의 위치가 화면 밖일때
	if (this->caret->GetY() < 0 || this->caret->GetY() > this->screenHeight / this->y_*this->y_) {
		this->paper->MoveToY(this->y_*this->text->GetCurrent());
		if (this->paper->GetY() + this->screenHeight > this->paper->GetHeight()) {
			this->paper->MoveToY(this->paper->GetHeight() - this->screenHeight);
			this->scrollInfo.nPos = this->paper->GetY();
			SetScrollPos(SB_VERT, this->scrollInfo.nPos);
		}
	}
	
	
}


void MemoForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
	Long yInc=0;//스크롤 thumb의 이동거리
	Long i = -1;
	switch (LOWORD(nSBCode))
	{
	case SB_LINEUP: {
		yInc = i*this->y_;
		this->paper->MoveToY(this->paper->GetY() +yInc);
		this->caret->MoveY(this->caret->GetY() - yInc);

	}break;
	case SB_LINEDOWN: {
		yInc = this->y_;
		this->paper->MoveToY(this->paper->GetY() + yInc);
		this->caret->MoveY(this->caret->GetY() -yInc);
	}break;
	case SB_PAGEUP:
	{	
		yInc = i*(this->scrollInfo.nPage/this->y_*this->y_);
		this->paper->MoveToY(this->paper->GetY() +yInc );
		this->caret->MoveY(this->caret->GetY() - yInc);

	}break;
	case SB_PAGEDOWN:
	{
		yInc = this->scrollInfo.nPage / this->y_*this->y_;
		this->paper->MoveToY(this->paper->GetY() +yInc );
		this->caret->MoveY(this->caret->GetY() - yInc);
	}break;
	case SB_THUMBTRACK:
	{	
		GetScrollInfo(SB_VERT, &this->scrollInfo);
		yInc = (this->scrollInfo.nTrackPos - this->scrollInfo.nPos) / this->y_*this->y_;
		this->paper->MoveToY(this->paper->GetY() + yInc );
		this->caret->MoveY(this->caret->GetY() - yInc);
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
		yInc = (this->scrollInfo.nMax - this->scrollInfo.nPos-this->scrollInfo.nPage) / this->y_*this->y_;
		this->paper->MoveToY(this->paper->GetHeight()-this->screenHeight / this->y_*this->y_);
		Long distance = previous - this->paper->GetY();
		if (LOWORD(nSBCode) != SB_THUMBTRACK) {
			this->caret->MoveY(this->caret->GetY()+distance);
		}
	}
	
 	//새로운 위치 설정
	this->scrollInfo.nPos = this->scrollInfo.nPos + yInc;
	//ScrollWindow(0, -yInc, 0, 0);
	//UpdateWindow();
	InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), true);
	SetScrollPos(SB_VERT, this->scrollInfo.nPos);
	SetCaretPos(CPoint(this->caret->GetX(), this->caret->GetY()));
	
}
void MemoForm::OnPaint()
{
	
	CString str;
	CPaintDC dc(this);
	
	//화면에 적는다.
	PaintVisitor paintVisitor(&dc,this->screenHeight,this->paper->GetY());
	this->text->Accept(&paintVisitor);
	this->y_ = paintVisitor.GetFontSize();
	
	//캐럿을 설정한다.
	CSize size_;
	Character *character;
	if (this->text->GetLength() > 0) {

		GetString getString(0, this->row->GetCurrent());
		this->row->Accept(&getString);
		size_ = dc.GetTextExtent(CString(getString.GetStr().c_str()));
		this->caret->Move(size_.cx, (this->text->GetCurrent())*(this->y_) - this->paper->GetY());

	}
	//출력영역 안이라면
	if (this->caret->GetY() < this->screenHeight / this->y_*this->y_) {
		CreateSolidCaret(1, this->y_);
		SetCaretPos(CPoint(this->caret->GetX(), this->caret->GetY()));
		ShowCaret();
		
	}
	//출력영역 밖이라면
	else {
		HideCaret();
	}
	//스크롤 갱신/
	if (this->text->GetLength()*this->y_ > this->screenHeight) {
		this->paper->ModifyHeight(this->text->GetLength()*this->y_);
		
	}
	else {
		this->paper->ModifyPaper(this->screenWidth, this->screenHeight);
	}
	this->scrollInfo.nMax = this->paper->GetHeight()+this->y_;
	SetScrollInfo(SB_VERT, &this->scrollInfo);
	//스크롤 위치 저장
	this->scrollPositions[this->page->GetCurrent()] = this->scrollInfo.nPos;
	//선택하기있으면 출력
	if (this->selectedText!=NULL){
		if (this->selectedText->GetStartRow()!=this->selectedText->GetEndRow()||this->selectedText->GetStartColumn()!=this->selectedText->GetEndColumn()) {
			this->selectedText->SetPaperPosition(this->paper->GetX(), this->paper->GetY());
			this->selectedText->Visit(this->text);
		}

	}
}

//마우스 클릭 캐럿 이동
void MemoForm::OnLButtonDown(UINT nFlags, CPoint point) {
	HideCaret();
	InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight ), false);
	if (this->selectedText != NULL) {
		delete this->selectedText;
		this->selectedText = NULL;
	}
	
	CClientDC dc(this);
	//this->selectedText = new SelectedText(&dc);
	CSize size_;
	CString str_;
	//클릭된 곳 좌표 받음
	Long x = point.x;
	Long y = point.y;
	Long y_;//글자의 세로 길이
	Character *character;
	Long height;
	//캐럿과 마우스 클릭된 곳의 y좌표 거리
	height = this->caret->GetY() - y;
	
	//캐럿보다 위에 있을때
	if (height >= 0) {
		while (height > 0) {
			this->row = dynamic_cast<Row*>(this->text->Move(this->text->GetCurrent() - 1));//this->text->current--;
			this->caret->MoveY(this->caret->GetY() - this->y_);
			height = this->caret->GetY() - y;
		}
	}

	//캐럿보다 아래에 있을때
	else if (height < 0) {
		height = -height;
		while (height > this->y_&&this->text->GetCurrent() < this->text->GetLength() - 1)
		{
			this->row = dynamic_cast<Row*>(this->text->Move(this->text->GetCurrent() + 1));
			this->caret->MoveY(this->caret->GetY() + this->y_);
			height = y - this->caret->GetY();
		}
		Long test = this->paper->GetHeight() - this->paper->GetY();
		if (y > this->screenHeight / this->y_*this->y_&&test>y) {
			this->paper->MoveToY(this->paper->GetY() + this->y_);
			InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight), true);
		}

	}
	
	//x축시작
	//text 가 있으면
	Long tempX = 0;
	Long previousX = 0;
	
	this->row->Move(-1);
	while (tempX < x&&this->row->GetCurrent() < this->row->GetLength()-3) {//-3인 이유는 \r\n때문

		GetString getString(0, this->row->GetCurrent()+1);
		this->row->Accept(&getString);
		size_ = dc.GetTextExtent(CString(getString.GetStr().c_str()));
		previousX = tempX;
		tempX = size_.cx;

		this->row->Move(this->row->GetCurrent() + 1);
	}
	float mid = (tempX + previousX) / 2.0F;
	if (x < mid) {
		this->row->Move(this->row->GetCurrent() - 1);
		this->caret->MoveX( previousX);
	}
	else if (x >= mid&&mid != 0) {
		this->caret->MoveX(tempX);
	}
	else {
		this->caret->MoveX(0);
	}
	SetCaretPos(CPoint(this->caret->GetX(), this->caret->GetY()));
	ShowCaret();
	this->x = this->caret->GetX();
	this->y = this->caret->GetY();

	this->firstClickedRow= this->text->GetCurrent();
	this->firstClickedColumn = this->row->GetCurrent();
	
	
}

void MemoForm::OnMouseMove(UINT nFlags, CPoint point) {
	
	Long x = point.x;
	Long y = point.y;
	CClientDC dc(this);
	CSize size_;
	
	this->selectedText = new SelectedText(&dc, this->paper->GetX(), this->paper->GetY());
	if (nFlags == MK_LBUTTON) {
		

		//**************************캐럿이동************************
		Long height;
		//캐럿과 마우스 클릭된 곳의 y좌표 거리
		height = this->caret->GetY() - y;

		//캐럿보다 위에 있을때
		if (height >= 0) {
			while (height > 0) {
				this->row = dynamic_cast<Row*>(this->text->Move(this->text->GetCurrent() - 1));//this->text->current--;
				this->caret->MoveY(this->caret->GetY() - this->y_);
				height = this->caret->GetY() - y;
			}
		}

		//캐럿보다 아래에 있을때
		else if (height < 0) {
			height = -height;
			while (height > this->y_&&this->text->GetCurrent() < this->text->GetLength() - 1)
			{
				this->row = dynamic_cast<Row*>(this->text->Move(this->text->GetCurrent() + 1));
				this->caret->MoveY(this->caret->GetY() + this->y_);
				height = y - this->caret->GetY();
			}
		}

		//x축시작
		//text 가 있으면
		Long tempX = 0;
		Long previousX = 0;

		this->row->Move(-1);
		while (tempX < x  &&this->row->GetCurrent() < this->row->GetLength() - 3) {

			GetString getString(0, this->row->GetCurrent() + 1);
			this->row->Accept(&getString);
			size_ = dc.GetTextExtent(CString(getString.GetStr().c_str()));
			previousX = tempX;
			tempX = size_.cx;

			this->row->Move(this->row->GetCurrent() + 1);
		}
		float mid = (tempX + previousX) / 2.0F;
		if (x < mid) {
			this->row->Move(this->row->GetCurrent() - 1);
		}
		
		//****************************캐럿이동끝**************************************
		//텍스트 선택시작.************************************************
		//현재 위치 저장
		Long startRow;
		Long startColumn;
		
		Long endRow;
		Long endColumn;
		
		//
		//마우스가 더블클릭된곳보다 상단에 있을때
		if (this->text->GetCurrent() < this->firstClickedRow) {

			startRow = this->text->GetCurrent();
			endRow = this->firstClickedRow;
			startColumn = this->row->GetCurrent()+1;
			endColumn = this->firstClickedColumn;

		}
		else if (this->text->GetCurrent() > this->firstClickedRow) {
			startRow = this->firstClickedRow;
			endRow = this->text->GetCurrent();
			startColumn = this->firstClickedColumn+1;
			endColumn = this->row->GetCurrent();
		}
		//같은줄 이라면
		else if (this->text->GetCurrent() == this->firstClickedRow) {
			startRow = this->firstClickedRow;
			endRow = this->text->GetCurrent();
			//현재 위치가 처음보다 왼쪽이라면
			if (this->row->GetCurrent() < this->firstClickedColumn) {
				startColumn = this->row->GetCurrent()+1;
				endColumn = this->firstClickedColumn;
			}
			else if (this->row->GetCurrent() >= this->firstClickedColumn) {
				startColumn = this->firstClickedColumn+1;
				endColumn = this->row->GetCurrent();
			}
		}
		//선택될곳 셋팅
		this->selectedText->SetTextPosition(startRow, startColumn, endRow, endColumn);
		//선택하기
		InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight ), false);
		UpdateWindow();
		
		//this->selectedText->Visit(this->text);
	
	}
	
}

//찾기 
LONG MemoForm::OnFindReplace(WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(wParam);
	HideCaret();
	
	CFindReplaceDialog *dlg = CFindReplaceDialog::GetNotifier(lParam);

	if (dlg != NULL) {
		//아래로 검색일때
		
		//찾기 창에 적힌 글자를 받아와서 keys에 저장한다
		CString findString = dlg->GetFindString();
		CString replaceString = "";
		Long i = 0;
		Long findStringLength = 0;
		CString alphabet;
		Row *keys = new Row(findString.GetLength());
		while (i < findString.GetLength()) {
			if (IsDBCSLeadByte(findString.GetAt(i))) {
				i += 2;
			}
			else {
				i++;
			}
			findStringLength++;
		}

		CClientDC dc(this);
		CSize size_;
		Long startRow;
		Long endRow;
		Long startColumn;
		Long endColumn;
		Long startX;
		Long endX;
		Long startY;
		Long endY;
		//찾기 방향 아래로
		//찾기랑 바꾸기
		if (dlg->ReplaceAll() == 0 && !dlg->IsTerminating()) {
			//현재 위치 이후 텍스트를 버퍼에 담는다.
			/*SelectedText selectedText;
			selectedText.SetTextPosition(this->text->GetCurrent(), this->row->GetCurrent() + 1, this->text->GetLength() - 1, dynamic_cast<Row*>(this->text->GetAt(this->text->GetLength() - 1))->GetLength() - 1);
			this->text->Accept(&selectedText);
			CString text = CString(selectedText.GetBuffer().c_str());*/
			//자동으로 줄바꾸기 때문에 전체 다 해줘야 될듯
			CString buffer;
			Row *row;
			CString text;
			Long startColumn;
			Long endColumn;
			Long afterTextRow=this->text->GetCurrent();
			while (afterTextRow < this->text->GetLength()) {
				row = dynamic_cast<Row*>(this->text->GetAt(afterTextRow));
				if (afterTextRow!=this->text->GetCurrent()) {
					startColumn = 0;
				}
				else {
					startColumn = row->GetCurrent() + 1;
				}
				endColumn = row->GetLength() - 1;
				GetString getString(startColumn, endColumn);
				row->Accept(&getString);
				text += CString(getString.GetStr().c_str());
				text += "\r\n";
				afterTextRow++;
			}
			//i로 돌리면서 같은것이 있는지 확인한다
			bool isEqual = false;
			Long i = 0;
			//모두 바꾸기 시작
			i = 0;
			Long j;
			Long k;

			//마크할것에 관한 데이터
			Long startRow;
			Long endRow;
			Long startX;
			Long endX;
			Long startY;
			Long endY;
			//CString 을 돌면서 텍스트 상의 위치 표시
			Long currentText = this->text->GetCurrent();
			Long currentRow = this->row->GetCurrent();
			CString comparedString;//비교되는 문자
			while (i < text.GetLength() - findString.GetLength()  && isEqual == false) {
				k = 0;
				j = i;

				comparedString = "";
				//비교될 문자 합치기
				while (k < findStringLength) {
					//한글
					if (IsDBCSLeadByte(text.GetAt(j))) {
						comparedString += text.Mid(j, 2);
						//i바꿔줘야되므로
						j += 2;
					}
					else {
						//영어
						comparedString += text.Mid(j, 1);
						//i바꿔줘야되므로
						j++;
					}
					k++;
				}
				//\r을 만난다면
				if (text.GetAt(i) != '\r'&&text.GetAt(i) != '\n') {
					currentRow++;
				}
				//찾는 문자열과 같다면
				if (comparedString == findString) {
					if (this->selectedText != NULL) {
						delete this->selectedText;
						this->selectedText = NULL;
					}

					//isEqual
					isEqual = true;
					startRow = currentText;
					endRow = currentText;
					startColumn = currentRow;
					endColumn = currentRow + findStringLength - 1;
					//현재위치를 옮긴다.
					this->row = dynamic_cast<Row*>(this->text->Move(currentText));
					this->row->Move(currentRow + findStringLength - 1);

					//스크롤 관련
					Long paperLocation = this->y_*(this->text->GetCurrent() + 2) - this->screenHeight;
					if (paperLocation > this->paper->GetHeight() - this->screenHeight) {
						paperLocation = this->paper->GetHeight() - this->screenHeight/this->y_*this->y_;
					}
					if (paperLocation < 0) {
						paperLocation = 0;
					}
					this->paper->MoveToY(paperLocation);

					this->scrollInfo.nPos = paperLocation;
					SetScrollPos(SB_VERT, this->scrollInfo.nPos);
					//Invalidate();
					//마크

					//마크할 위치 

					GetString getStart(0, startColumn - 1);
					dynamic_cast<Row*>(this->text->GetAt(currentText))->Accept(&getStart);
					size_ = dc.GetTextExtent(CString(getStart.GetStr().c_str()));
					startX = size_.cx;
					startY = currentText*this->y_ - paperLocation;
					GetString getEnd(0, endColumn);
					dynamic_cast<Row*>(this->text->GetAt(currentText))->Accept(&getEnd);
					size_ = dc.GetTextExtent(CString(getEnd.GetStr().c_str()));
					endX = size_.cx;
					endY = currentText*this->y_ - paperLocation;
					//마크한다.
					this->selectedText = new SelectedText(&dc, this->paper->GetX(), this->paper->GetY());
					this->selectedText->SetTextPosition(currentText, currentRow, currentText, currentRow + findStringLength - 1);

					InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight ), true);
					UpdateWindow();
					this->selectedText->Visit(this->text);
					//SetCaretPos(CPoint(this->caret->GetX(), this->caret->GetY()));
					//ShowCaret();
				}

				//\n을 만난다면.
				if (text.GetAt(i) == '\n') {
					currentText++;
					currentRow = -1;//??????????????????
				}
				//더블바이트이면
				if (IsDBCSLeadByte(text.GetAt(i))) {
					i += 2;
				}
				//싱글바이트라면
				else {
					i++;
				}
			}
			if (isEqual == false) {
				Invalidate(true);
				CString temp = "'이 존재하지 않습니다.";
				CString print = "'" + findString + temp;
				MessageBox((LPCTSTR)print, "메모장", MB_OK);
				delete this->selectedText;
				this->selectedText = NULL;
			}
			CString replaceString = "";
			replaceString = dlg->GetReplaceString();

			if (dlg->ReplaceCurrent() != 0) {
				//선택된 부분이후를 선택하여 임시 저장한다
				if (this->selectedText != NULL) {
					SelectedText selectedText;
					selectedText.SetTextPosition(this->selectedText->GetEndRow(), this->selectedText->GetEndColumn() + 1, this->text->GetLength() - 1, dynamic_cast<Row*>(this->text->GetAt(this->text->GetLength() - 1))->GetLength() - 1);
					this->text->Accept(&selectedText);
					//선택된 곳부터 끝까지 다 삭제
					EraseSelectedText eraseSelectedText(this->selectedText->GetStartRow(), this->selectedText->GetStartColumn(), this->text->GetLength() - 1, dynamic_cast<Row*>(this->text->GetAt(this->text->GetLength() - 1))->GetLength() - 1);
					this->text->Accept(&eraseSelectedText);
					this->row = dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent()));

					//바꿀 문자열을 받아온다.
					CopyToMemo copyToMemo(&dc, this->screenWidth, (LPCTSTR)replaceString);
					this->text->Accept(&copyToMemo);
					this->row = dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent()));

					//임시저장한 뒷부분을 옮겨 적는다.
					Long textCurrent = this->text->GetCurrent();
					Long rowCurrent = this->row->GetCurrent();
					//임시저장한 텍스트를 다시 적는다.
					CopyToMemo copyAgain(&dc, this->screenWidth, selectedText.GetBuffer());
					this->text->Accept(&copyAgain);
					//현재 위치를 원 상태로 돌린다
					this->row = dynamic_cast<Row*>(this->text->Move(textCurrent));
					this->row->Move(rowCurrent);
				}
			}


		}
		//모두 바꾸기
		else if (dlg->ReplaceAll() != 0 && !dlg->IsTerminating()) {
			bool isChanged = false;
			//전체 복사
			SelectedText selectedText;
			selectedText.SetTextPosition(0, 0, this->text->GetLength() - 1, dynamic_cast<Row*>(this->text->GetAt(this->text->GetLength() - 1))->GetLength() - 1);
			this->text->Accept(&selectedText);
			//전체 삭제
			EraseSelectedText eraseSelectedText(0, 0, this->text->GetLength() - 1, dynamic_cast<Row*>(this->text->GetAt(this->text->GetLength() - 1))->GetLength() - 1);
			this->text->Accept(&eraseSelectedText);
			//복사한 스트링을 받는다
			CString text = CString(selectedText.GetBuffer().c_str());
			CString buffer;
			CString changeText;

			//찾을 텍스트,바꿀 텍스트를 받아온다.
			CString findString = dlg->GetFindString();
			//찾을 텍스트의 길이를 받아온다.
			Long findStringLength = 0;
			Long i = 0;
			while (i < findString.GetLength()) {
				if (IsDBCSLeadByte(findString.GetAt(i))) {
					i += 2;
				}
				else {
					i++;
				}
				findStringLength++;
			}
			CString replaceString = dlg->GetReplaceString();
			//모두 바꾸기 시작
			i = 0;
			Long j;
			Long k;
			Long start = 0;
			Long end;
			CString comparedString;//비교되는 문자
			while (i < text.GetLength() - findString.GetLength() - 1) {
				k = 0;
				j = i;
				comparedString = "";
				//비교될 문자 합치기
				while (k < findStringLength) {
					//한글
					if (IsDBCSLeadByte(text.GetAt(j))) {
						comparedString += text.Mid(j, 2);
						j += 2;
					}
					else {
						//영어
						comparedString += text.Mid(j, 1);
						j++;
					}
					k++;
				}
				//찾는 문자열과 같다면
				if (comparedString == findString) {
					end = i - 1;
					buffer = text.Mid(start, end - start + 1);
					changeText += buffer;
					changeText += replaceString;
					start = i + findString.GetLength();
					//isChanged 바꿔줌
					isChanged = true;
				}
				//더블바이트이면
				if (IsDBCSLeadByte(text.GetAt(j))) {
					i += 2;
				}
				else {
					//영어
					i++;
				}
			}
			end = text.GetLength() - 1;
			buffer = text.Mid(start, end - start + 1);
			changeText += buffer;

			CopyToMemo copyToMemo(&dc, this->screenWidth, (LPCTSTR)changeText);
			this->text->Accept(&copyToMemo);
			//맨앞으로 이동
			this->row = dynamic_cast<Row*>(this->text->GetAt(0));
			this->row->Move(0);
			this->paper->MoveToY(0);
			this->caret->Move(0, 0);
			this->scrollInfo.nPos = 0;
			SetScrollInfo(SB_VERT, &this->scrollInfo);
			InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight ), true);
			if (isChanged == false) {
				CString temp = "'이 존재하지 않습니다.";
				CString print = "'" + findString + temp;
				MessageBox((LPCTSTR)print, "메모장", MB_OK);
			}


		}
		/*CreateSolidCaret(1, this->y_);
		*/
		//끌때
		if (dlg->IsTerminating()) {
			//동적할당한거 해제시켜줘야함*************************아직 못해줌
			this->pDlg = NULL;

			//Long i;
		}

	}
	
	return 0;
}
//버튼/
/*void MemoForm::OnButtonCliked(UINT uiID) {
	switch (uiID)
	{
	case IDI_ADDICON :{
		//기존 페이지에 '\f'추가
		Row *row_ = dynamic_cast<Row*>(this->text->GetAt(this->text->GetLength() - 1));
		SingleByteCharacter *formFeed = new SingleByteCharacter('\f');
		row_->Add(formFeed);
		//새로운 페이지 추가
		Row *row = new Row;
		Text *text = new Text;
		text->Add(row);
		this->page->Add(text);
		this->text = dynamic_cast<Text*>(this->page->GetAt(this->page->GetCurrent()));
		this->row = dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent()));
		//\r\n추가
		SingleByteCharacter *singleByteCharacter = new SingleByteCharacter('\r');
		SingleByteCharacter *singleBytecharacter_ = new SingleByteCharacter('\n');
		this->row->Add(singleByteCharacter);
		this->row->Add(singleBytecharacter_);
		this->row->Move(-1);
		this->caret->Move(0, 0);
		this->paper->MoveToY(0);
		InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight ), true);
		SetCaretPos(CPoint(this->caret->GetX(), this->caret->GetY()));
		ShowCaret();
		
		//페이지 버튼 생성
		Long i = this->page->GetCurrent();
		CStatusButton *pageButton= new CStatusButton;
		pageButton->Create(_T("page"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, CRect(75+i*100, 0, 75+(i+1)*100, 25), &this->statusBar, 123+i);
		if (this->pageButtons->GetLength() < this->pageButtons->GetCapacity()) {
			this->pageButtons->Store(i, pageButton);
		}
		else {
			this->pageButtons->Insert(i,pageButton);
		}
		
		//UpdateWindow();
	}break;
	case IDI_TRASHICON: {
		//메세지 박스.
		int ret=0;//페이지에 아무거도 없을때
		if (this->text->GetLength() > 1 || this->row->GetLength() > 2) {
			ret=MessageBox(_T("현재 페이지가 메모장에서 영구적으로 삭제됩니다.계속 하시겠습니까?"), _T("메모장"), MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON1);
		}//페이지가 1보다 클때 페이지 삭제
		if (ret==0||ret==IDYES) {
			Long current = this->page->GetCurrent();
			this->page->Delete(current);
			if (this->page->GetCurrent() < this->page->GetLength() - 1) {
				this->page->Move(this->page->GetCurrent() + 1);
			}
			this->pageButtons->Delete(current);
			
		}
		//페이지 없을때
		if (this->page->GetLength() == 0) {
			//int ret_ = MessageBox(_T("현재 페이지가 하나밖에 없습니다. 지우시겠습니까?"), _T("메모장"), MB_YESNO | MB_DEFBUTTON1);
			//if (ret_ == IDYES) {
				Text *text = new Text;
				Row *row = new Row;
				SingleByteCharacter *singleByteCharacter = new SingleByteCharacter('\r');
				SingleByteCharacter *singleByteCharacter_ = new SingleByteCharacter('\n');
				row->Add(singleByteCharacter);
				row->Add(singleByteCharacter_);
				row->Move(-1);
				text->Add(row);
				this->page->Add(text);
			//}
		}
		this->text = dynamic_cast<Text*>(this->page->GetAt(this->page->GetCurrent()));
		this->row = dynamic_cast<Row*>(this->text->GetAt(this->text->GetCurrent()));
		InvalidateRect(CRect(0, 0, this->screenWidth, this->screenHeight ), true);
	}
	case 105: {
		HDC hdc = ::GetDC(GetSafeHwnd());
		TextOut(hdc, 100, 100, _T("그"),3);
	}
	default:
		break;
	}
	//RepositionBars(ID_INDICATOR, 0xFFFF, AFX_IDW_PANE_FIRST, reposDefault, NULL, NULL, TRUE);
	SetFocus();
}*/
void MemoForm::OnSize(UINT nType, int cx, int cy) {

	this->screenWidth = cx;
	this->screenHeight = cy;
	this->scrollInfo.cbSize = sizeof(this->scrollInfo);
	this->scrollInfo.fMask = SIF_ALL;
	this->scrollInfo.nMin = 0;
	this->scrollInfo.nMax = this->paper->GetHeight();
	this->scrollInfo.nPage = cy;
	SetScrollInfo(SB_VERT, &this->scrollInfo);
	/*//상태표시줄 생성
	this->statusBar.SetIndicators(ID_INDICATOR, 2);
	this->statusBar.SetPaneInfo(0, ID_INDICATOR, SBPS_NOBORDERS, cx - 200);
	this->statusBar.SetPaneInfo(1, ID_INDICATOR, SBPS_NORMAL, 200);
	RepositionBars(ID_INDICATOR, 0xFFFF, AFX_IDW_PANE_FIRST, reposDefault, NULL, NULL, TRUE);
	CRect rect;
	this->statusBar.GetItemRect(0, rect);*/
	
	
}
void MemoForm::OnSysCommand(UINT nID, LPARAM lParam) {
	if (nID == SC_CLOSE) {
		if (this->page != NULL) {
			//저장하기
			//메세지박스 출력
			int ret = MessageBox(_T("변경내용을 제목없음에 저장하시겠습니까?"), _T("메모장"), MB_YESNOCANCEL);
			if (ret == IDYES) {
				CFileDialog dlg(FALSE, "*.txt", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, "text Files(*.txt)|*.txt|");
				if (dlg.DoModal() == IDOK) {
					CStdioFile file;
					CString str;
					//TCHAR pathName[128];//파일경로
					//GetModuleFileName(NULL, pathName, 128);

					if (file.Open(dlg.GetPathName(), CFile::modeCreate|CFile::modeWrite | CFile::typeText)) {
						Long i = 0;
						Text *text;
						Row *row;
						CString str;
						while (i < this->page->GetLength()) {
							text = dynamic_cast<Text*>(this->page->GetAt(i));
							Long j = 0;
							while (j <text->GetLength()) {
								row = dynamic_cast<Row*>(text->GetAt(j));
								GetString getString(0, row->GetLength() -1);
								row->Accept(&getString);
								str = CString(getString.GetStr().c_str());
								file.WriteString(str+"\n");
								j++;
							}
							if (i <this->page->GetLength()-1) {
								file.WriteString("\f\n");
							}
							i++;

						}
						file.Close();
					}


				}
				CFrameWnd::OnClose();

			}
			else if (ret == IDNO) {
				if (this->page != NULL) {
					delete this->page;
				}
				CFrameWnd::OnClose();
			}
		}
	

	}
	else {
		
		CFrameWnd::OnSysCommand(nID, lParam);
		
	}
}
void MemoForm::OnClose() {
	
}

