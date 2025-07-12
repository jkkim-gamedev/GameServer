#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "DeadLockProfiler.h"
#include "SocketUtils.h"
#include "GlobalQueue.h"
#include "JobTimer.h"

ThreadManager*	GThreadManager = nullptr;
Memory*			GMemory = nullptr;
GlobalQueue*	GGlobalQueue = nullptr;
JobTimer*		GJobTimer = nullptr;

DeadLockProfiler* GDeadLockProfiler = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GThreadManager = new ThreadManager();
		GMemory = new Memory();
		GGlobalQueue = new GlobalQueue();
		GJobTimer = new JobTimer();
		GDeadLockProfiler = new DeadLockProfiler();
		SocketUtils::Init();
	}

	~CoreGlobal()
	{
		delete GThreadManager;
		delete GMemory;
		delete GGlobalQueue;
		delete GJobTimer;
		delete GDeadLockProfiler;
		SocketUtils::Clear();
	}
} GCoreGlobal;