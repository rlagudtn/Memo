//ConnectedInfo.h
#ifndef _CONNECTEDINFO_H
#define _CONNECTEDINFO_H

class Text;
typedef signed long int Long;
class ConnectedInfo {
public:
	ConnectedInfo();
	ConnectedInfo(const ConnectedInfo& source);
	~ConnectedInfo();
	ConnectedInfo& operator=(const ConnectedInfo& source);
	Long GetEndOfConnected(Text *text,Long index);
	Long GetLastConnectedRow() const;
private:
	Long lastConnectedRow;
};
inline Long ConnectedInfo::GetLastConnectedRow() const {
	return this->lastConnectedRow;
}

#endif // _CONNECTEDINFO_H
