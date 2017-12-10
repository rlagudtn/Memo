//LineInfo.h
#ifndef _LINEINFO_H
#define _LINEINFO_H
#include "Array.h"
typedef signed long int Long;
class LineInfo {
public:
	LineInfo(Long capacity=60000);
	LineInfo(const LineInfo& source);
	~LineInfo();
	LineInfo& operator=(const LineInfo& source);
	bool GetAt(Long index);
	Long Add(bool isOver);
	bool operator[](Long index);
	Long GetCapapcity() const;
	Long GetLength() const;
private:
	Array<bool> isOverScreen;
	Long capacity;
	Long length;
};
inline Long LineInfo::GetCapapcity() const {
	return this->capacity;
}
inline Long LineInfo::GetLength() const {
	return this->length;
}
#endif // _LINEINFO_H
