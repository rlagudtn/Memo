//CStatusButton.cpp
#include "CStatusButton.h"

CStatusButton::CStatusButton(){}
CStatusButton::~CStatusButton(){}
void CStatusButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	CRect rt;
	rt = lpDrawItemStruct->rcItem;
	//상태바와 같은색으로 색칠
	//dc.FillSolidRect(rt, RGB(204, 204, 204));
	//버튼상태 가져오기
	UINT nstate = lpDrawItemStruct->itemState;
	//눌릴때
	
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
	//버튼에 있는 글자 받아온다.
	CString str;
	GetWindowText(str);
	
	dc.DrawText(str, rt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	dc.Detach();
}