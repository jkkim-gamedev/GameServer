﻿#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "GameSession.h"

enum
{
	WORKER_TICK = 64
};

void DoWorkerJob(ServerServiceRef& service)
{
	while (true)
	{
		LEndTickCount = ::GetTickCount64() + WORKER_TICK;

		// 네트워크 입출력 처리 -> 인게임 로직까지 (패킷 핸들러에 의해)
		service->GetIocpCore()->Dispatch(10);

		// 예약된 일감 처리
		ThreadManager::DistributeReservedJobs();

		// 글로벌 큐
		ThreadManager::DoGlobalQueueWork();
	}
}

int main()
{
	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>, // TODO : SessionManager 등
		10);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 3; i++)
	{
		GThreadManager->Launch([&service]()
		{
			DoWorkerJob(service);
		});
	}

	// Main Thread
	DoWorkerJob(service);

	GThreadManager->Join();
}
