//LineInfo.h
#ifndef _LINEINFO_H
#define _LINEINFO_H
#include "Array.h"
typedef signed long int Long;
class LineInfo {
public:
	LineInfo(Long capacity=3000);
	LineInfo(const LineInfo& source);
	~LineInfo();
	LineInfo& operator=(const LineInfo& source);
	Long GetAt(Long index);
	Long Add(Long isOver);
	Long operator[](Long index);
	Long GetCapapcity() const;
	Long GetLength() const;
private:
	Array<Long> booleans;
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
