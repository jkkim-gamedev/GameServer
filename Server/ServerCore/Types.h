#pragma once

#include <mutex>
#include <atomic>

using BYTE		= unsigned char;
using int8		= __int8;
using int16		= __int16;
using int32		= __int32;
using int64		= __int64;
using uint8		= unsigned __int8;
using uint16	= unsigned __int16;
using uint32	= unsigned __int32;
using uint64	= unsigned __int64;

template<typename T>
using Atomic = std::atomic<T>;
using Mutex = std::mutex;
using LockGuard = std::lock_guard<std::mutex>;

// shared_ptr
#define USING_SHARED_PTR(name)	using name##Ref = std::shared_ptr<class name>;

USING_SHARED_PTR(IocpCore);
USING_SHARED_PTR(IocpObject);
USING_SHARED_PTR(Session);
USING_SHARED_PTR(PacketSession);
USING_SHARED_PTR(Listener);
USING_SHARED_PTR(ServerService);
USING_SHARED_PTR(SendBuffer);
USING_SHARED_PTR(Job);
USING_SHARED_PTR(JobQueue);

#define _STOMP