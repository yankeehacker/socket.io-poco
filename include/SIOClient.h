#ifndef SIO_Client_INCLUDED
#define SIO_Client_INCLUDED

#include <mutex>

#include "SIOClientImpl.h"

#include "Poco/JSON/Array.h"

using Poco::JSON::Array;

class SIOClient
{
private:
	~SIOClient();

	SIOClientImpl *_socket;
	
	std::string _uri;
	std::string _endpoint;

	Poco::NotificationCenter* _nCenter;

	SIOEventRegistry *_registry;
	SIONotificationHandler *_sioHandler;

	std::mutex _emit_mtx; 

public:


	SIOClient(std::string uri, std::string endpoint, SIOClientImpl *impl);

	static SIOClient* connect(std::string uri, std::map<std::string, std::string> queryArgs);
	void disconnect();
	void send(std::string s);
	void emit(std::string eventname, std::string args);
	void emit(std::string eventname, Poco::JSON::Object::Ptr json_data);
	std::string getUri();
	Poco::NotificationCenter* getNCenter();

	typedef void (SIOEventTarget::*callback)(const void*, Array::Ptr&);

	void on(const char *name, SIOEventTarget *target, callback c);

	void fireEvent(const char * name, Array::Ptr args);
};

#endif
