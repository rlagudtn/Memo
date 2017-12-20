//Menu.h
#include "Menu.h"
#include "MemoForm.h"
Menu::Menu(MemoForm *memoForm){
	this->memoForm = memoForm;
	this->main = new CMenu;
	this->main->CreateMenu();

	this->file = new CMenu;
	this->edit = new CMenu;
	this->option = new CMenu;
	this->view = new CMenu;
	this->help = new CMenu;
	
	this->file->CreatePopupMenu();
	this->edit->CreatePopupMenu();
	this->option->CreatePopupMenu();
	this->view->CreatePopupMenu();
	this->help->CreatePopupMenu();

	this->main->AppendMenuA(MF_POPUP, (UINT_PTR)this->file->m_hMenu, "파일(F)");
	this->main->AppendMenuA(MF_POPUP, (UINT_PTR)this->edit->m_hMenu, "편집(E)");
	this->main->AppendMenuA(MF_POPUP, (UINT_PTR)this->option->m_hMenu, "서식(O)");
	this->main->AppendMenuA(MF_POPUP, (UINT_PTR)this->view->m_hMenu, "보기(V)");
	this->main->AppendMenuA(MF_POPUP, (UINT_PTR)this->help->m_hMenu, "도움말(H)");
	
	this->memoForm->SetMenu(this->main);
	//파일
	this->file->AppendMenuA(MF_STRING, 201, "새로만들기(N)");
	this->file->AppendMenuA(MF_STRING, 202, "열기(O)");
	this->file->AppendMenuA(MF_STRING, 203, "저장()");
	this->file->AppendMenuA(MF_STRING, 204, "다른 이름으로 저장(O)");
	this->file->AppendMenuA(MF_STRING, 205, "페이지 설정(U)");
	this->file->AppendMenuA(MF_STRING, 206, "인쇄(P)");
	this->file->AppendMenuA(MF_STRING, 207, "인쇄미리보기(P)..");
	this->file->AppendMenuA(MF_STRING, 208, "끝내기(X)");
	//편집
	this->edit->AppendMenu(MF_STRING, 209, "복사(C)");
	this->edit->AppendMenu(MF_STRING, 210, "붙여넣기(P)");
	this->edit->AppendMenu(MF_STRING, 211, "잘라내기(T)");
	this->edit->AppendMenu(MF_STRING, 212, "되돌리기(R)");
	this->edit->AppendMenu(MF_STRING, 213, "재실행(O)");
	this->edit->AppendMenu(MF_STRING, 214, "찾기(F)");
	this->edit->AppendMenu(MF_STRING, 215, "바꾸기(H)..");
	this->edit->AppendMenu(MF_STRING, 216, "모두선택(A)");
	this->edit->AppendMenu(MF_STRING, 222, "새 페이지(N)");
	this->edit->AppendMenu(MF_STRING, 223, "다음페이지로 이동(N)");
	this->edit->AppendMenu(MF_STRING, 224, "이전페이지로 이동(P)");
	this->edit->AppendMenu(MF_STRING, 225, "페이지 삭제(D)");
	//서식
	this->option->AppendMenu(MF_STRING, 217, "자동 줄바꿈(W)");
	this->option->AppendMenu(MF_STRING, 218, "글꼴(F)");
	//보기
	this->view->AppendMenu(MF_STRING, 219, "상태표시줄(S)");
	//도움말
	this->help->AppendMenu(MF_STRING, 220, "도움말보기(H)");
	this->help->AppendMenu(MF_STRING, 221, "메모장 정보(I)");




}
Menu::~Menu(){}
void Menu::SetMenuBar(MemoForm *memoForm) {
	
}