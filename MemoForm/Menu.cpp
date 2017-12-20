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

	this->main->AppendMenuA(MF_POPUP, (UINT_PTR)this->file->m_hMenu, "����(F)");
	this->main->AppendMenuA(MF_POPUP, (UINT_PTR)this->edit->m_hMenu, "����(E)");
	this->main->AppendMenuA(MF_POPUP, (UINT_PTR)this->option->m_hMenu, "����(O)");
	this->main->AppendMenuA(MF_POPUP, (UINT_PTR)this->view->m_hMenu, "����(V)");
	this->main->AppendMenuA(MF_POPUP, (UINT_PTR)this->help->m_hMenu, "����(H)");
	
	this->memoForm->SetMenu(this->main);
	//����
	this->file->AppendMenuA(MF_STRING, 201, "���θ����(N)");
	this->file->AppendMenuA(MF_STRING, 202, "����(O)");
	this->file->AppendMenuA(MF_STRING, 203, "����()");
	this->file->AppendMenuA(MF_STRING, 204, "�ٸ� �̸����� ����(O)");
	this->file->AppendMenuA(MF_STRING, 205, "������ ����(U)");
	this->file->AppendMenuA(MF_STRING, 206, "�μ�(P)");
	this->file->AppendMenuA(MF_STRING, 207, "�μ�̸�����(P)..");
	this->file->AppendMenuA(MF_STRING, 208, "������(X)");
	//����
	this->edit->AppendMenu(MF_STRING, 209, "����(C)");
	this->edit->AppendMenu(MF_STRING, 210, "�ٿ��ֱ�(P)");
	this->edit->AppendMenu(MF_STRING, 211, "�߶󳻱�(T)");
	this->edit->AppendMenu(MF_STRING, 212, "�ǵ�����(R)");
	this->edit->AppendMenu(MF_STRING, 213, "�����(O)");
	this->edit->AppendMenu(MF_STRING, 214, "ã��(F)");
	this->edit->AppendMenu(MF_STRING, 215, "�ٲٱ�(H)..");
	this->edit->AppendMenu(MF_STRING, 216, "��μ���(A)");
	this->edit->AppendMenu(MF_STRING, 222, "�� ������(N)");
	this->edit->AppendMenu(MF_STRING, 223, "������������ �̵�(N)");
	this->edit->AppendMenu(MF_STRING, 224, "������������ �̵�(P)");
	this->edit->AppendMenu(MF_STRING, 225, "������ ����(D)");
	//����
	this->option->AppendMenu(MF_STRING, 217, "�ڵ� �ٹٲ�(W)");
	this->option->AppendMenu(MF_STRING, 218, "�۲�(F)");
	//����
	this->view->AppendMenu(MF_STRING, 219, "����ǥ����(S)");
	//����
	this->help->AppendMenu(MF_STRING, 220, "���򸻺���(H)");
	this->help->AppendMenu(MF_STRING, 221, "�޸��� ����(I)");




}
Menu::~Menu(){}
void Menu::SetMenuBar(MemoForm *memoForm) {
	
}