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
	Long Add(bool isOver);
public:
	Array<bool> isOverScreen;
	Long capacity;
	Long length;
};
#endif // _LINEINFO_H
