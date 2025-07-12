#pragma once

#include "NetAddress.h"
#include <functional>

/*-------------
	Service
--------------*/

enum class ServiceType : uint8
{
	Server,
	Client
};

using SessionFactory = function<SessionRef(void)>;

class Service : public enable_shared_from_this<Service>
{
public:
	Service(ServiceType type, NetAddress address, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~Service();

	virtual bool		Start() abstract;
	bool				CanStart() { return _sessionFactory != nullptr; }

	SessionRef			CreateSession();
	void				AddSession(SessionRef session);
	void				ReleaseSession(SessionRef session);
	int32				GetMaxSessionCount() { return _maxSessionCount; }

public:
	NetAddress			GetNetAddress() { return _netAddress; }
	IocpCoreRef&		GetIocpCore() { return _iocpCore; }

protected:
	USE_LOCK;
	ServiceType			_type;
	NetAddress			_netAddress = {};
	IocpCoreRef			_iocpCore;

	Set<SessionRef>		_sessions;
	int32				_sessionCount = 0;
	int32				_maxSessionCount = 0;
	SessionFactory		_sessionFactory;
};

/*-----------------
	ServerService
------------------*/

class ServerService : public Service
{
public:
	ServerService(NetAddress targetAddress, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~ServerService() {}

	virtual bool	Start() override;

private:
	ListenerRef		_listener = nullptr;
};