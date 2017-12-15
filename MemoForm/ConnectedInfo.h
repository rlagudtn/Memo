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
	Long GetLastConnectedLine() const;
	bool GetIsConnected() const;
private:
	Long lastConnectedLine;
	bool isConnected;
};
inline Long ConnectedInfo::GetLastConnectedLine() const {
	return this->lastConnectedLine;
}
inline bool ConnectedInfo::GetIsConnected() const {
	return this->isConnected;
}

#endif // _CONNECTEDINFO_H
