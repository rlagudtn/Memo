//Row.h
#ifndef _ROW_H
#define _ROW_H
#include "Composite.h"
#include <string>
#pragma warning (disable:4996)
using namespace std;
class  Visitor;
typedef signed long int Long;
class Row :public Composite {
public:
	Row(Long capacity = 64);
	Row(const Row& source);
	virtual ~Row();
	virtual Glyph* Clone();
	void Accept(Visitor *visitor);
	void Connect();
	void DisConnect();
	bool GetIsConnected() const;
private:
	bool isConnected;
};
inline bool Row::GetIsConnected() const {
	return this->isConnected;
}
#endif // _ROW_H
