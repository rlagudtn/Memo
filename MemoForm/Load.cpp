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
	//�ҷ�����
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
			//������ ���� �ƴ� ���� �ݺ��Ѵ�.
			//���پ� �д´�.
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
						//�ѱ��̶��
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
						//���ڿ��� ���̸� ���� ȭ���� �Ѵ��� Ȯ���Ѵ�
						Long stringLength = dc.GetTextExtent(useChechScreenOver).cx;
						if (stringLength > memoForm->screenWidth) {
							//����Ǿ��� �ִ� ���·� �����.
							memoForm->row->Connect();
							//���� �����Ѵ�.
							memoForm->row = new Row;
							memoForm->text->Add(memoForm->row);
							//ȭ�� �Ѵ��� ���ο� ���� ���ڿ��� �ʱ�ȭ �Ѵ�.
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
		//����� �ٲ۴�.
		memoForm->originalPathName = dlg.GetPathName();
	}
}