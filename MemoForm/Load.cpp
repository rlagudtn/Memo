#include "Load.h"
#include "MemoForm.h"
#include "Page.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
Load::Load() {}
Load::~Load() {}
void Load::WriteToMemo(MemoForm *memoForm) {
	//불러오기
	CFileDialog dlg(true, "*.txt", NULL, OFN_FILEMUSTEXIST, "text Files(*.txt)|*.txt|", NULL);
	if (dlg.DoModal() == IDOK) {
		if (memoForm->page != NULL) {
			delete memoForm->page;
		}
		memoForm->page = new Page;
		memoForm->text = new Text;
		memoForm->page->Add(memoForm->text);
	
		CStdioFile file;
		CString line;
		CClientDC dc(memoForm);
		dc.SelectObject(memoForm->font);
		if (file.Open(dlg.GetPathName(), CFile::modeRead)) {
			//파일의 끝이 아닌 동안 반복한다.
			//한줄씩 읽는다.
			while (file.ReadString(line)) {
				if (line != '\f') {
					memoForm->row = new Row;
					memoForm->text->Add(memoForm->row);
					Long i = 0;
					CString useChechScreenOver="";
					CString temp;
					Character *character;
					char alpha[3] = { 0, };
					char alphabet;
					while (i < line.GetLength()) {
						//한글이라면
						if (IsDBCSLeadByte(line.GetAt(i))) {
							temp = line.Mid(i, 2);
							strcpy(alpha, (LPCTSTR)temp);
							character=new DoubleByteCharacter(alpha);
							i += 2;
						}
						else {
							temp = line.Mid(i, 1);
							alphabet = *temp;
							character = new SingleByteCharacter(alphabet);
							i++;
						}
						useChechScreenOver += temp;
						//문자열의 길이를 구해 화면을 넘는지 확인한다
						Long stringLength = dc.GetTextExtent(useChechScreenOver).cx;
						if (stringLength > memoForm->screenWidth) {
							//연결되어져 있는 상태로 만든다.
							memoForm->row->Connect();
							//줄을 생성한다.
							memoForm->row = new Row;
							memoForm->text->Add(memoForm->row);
							//화면 넘는지 여부에 관한 문자열을 초기화 한다.
							useChechScreenOver = "";
						}
						memoForm->row->Add(character);

					}
				}
				else {
					memoForm->text = new Text;
					memoForm->page->Add(memoForm->text);
					
				}
			}
			file.Close();
		}
		memoForm->text = dynamic_cast<Text*>(memoForm->page->Move(0));
		memoForm->row = dynamic_cast<Row*>(memoForm->text->Move(0));
		memoForm->row->Move(-1);
		memoForm->InvalidateRect(CRect(0, 0, memoForm->screenWidth, memoForm->screenHeight), true);
		//경오를 바꾼다.
		memoForm->originalPathName = dlg.GetPathName();
	}
}