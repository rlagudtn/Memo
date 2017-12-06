//CStatusButton.cpp
#include "CStatusButton.h"

CStatusButton::CStatusButton(){}
CStatusButton::~CStatusButton(){}
void CStatusButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	CRect rt;
	rt = lpDrawItemStruct->rcItem;
	//���¹ٿ� ���������� ��ĥ
	//dc.FillSolidRect(rt, RGB(204, 204, 204));
	//��ư���� ��������
	UINT nstate = lpDrawItemStruct->itemState;
	//������
	
	if (nstate&ODS_SELECTED) {
		dc.DrawEdge(rt, EDGE_SUNKEN, BF_SOFT);
		dc.FillSolidRect(rt, RGB(255, 255, 255));
		dc.SetTextColor(RGB(0, 0, 255));
		//dc.SetBkMode(OPAQUE);
		EnableWindow(FALSE);
	}
	else {
		dc.DrawEdge(rt, EDGE_RAISED, BF_LEFT | BF_RIGHT);
	}
	//��ư�� �ִ� ���� �޾ƿ´�.
	CString str;
	GetWindowText(str);
	
	dc.DrawText(str, rt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.Detach();
}