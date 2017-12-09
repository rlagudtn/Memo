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
	ConnectedInfo& GetConnectedInfo(Text *text);
	bool GetIsConnected() const;
	Long GetLastConnectedRow() const;
private:
	bool IsConnected;
	Long lastConnectedRow;
};
inline bool ConnectedInfo::GetIsConnected() const {
	return this->IsConnected;
}
inline Long ConnectedInfo::GetLastConnectedRow() const {
	return this->lastConnectedRow;
}

#endif // _CONNECTEDINFO_H
