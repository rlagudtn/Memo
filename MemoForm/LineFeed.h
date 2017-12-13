//LineFeed.h
#ifndef _LINEFEED_H
#define _LINEFEED_H
class Row;
class LineFeed {
public:
	LineFeed();
	LineFeed(const LineFeed& source);
	~LineFeed();
	void SetLineFeed(Row *row);
	bool IsLineFeed(Row *row);
};
#endif // _LINEFEED_H