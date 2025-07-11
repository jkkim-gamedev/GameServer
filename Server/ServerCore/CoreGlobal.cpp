#include "pch.h"
#include "CoreGlobal.h"
#include "DeadLockProfiler.h"
#include "SocketUtils.h"

Memory* GMemory = nullptr;

DeadLockProfiler* GDeadLockProfiler = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GMemory = new Memory();
		GDeadLockProfiler = new DeadLockProfiler();
		SocketUtils::Init();
	}

	~CoreGlobal()
	{
		delete GMemory;
		delete GDeadLockProfiler;
		SocketUtils::Clear();
	}
} GCoreGlobal;