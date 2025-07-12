#include "pch.h"
#include "JobTimer.h"

void JobTimer::Distribute(uint64 now)
{
	// 한 번에 1 쓰레드만 통과
	if (_distributing.exchange(true) == true)
		return;

	Vector<TimerItem> items;

	{
		WRITE_LOCK;

		while (_items.empty() == false)
		{
			const TimerItem& timerItem = _items.top();
			if (now < timerItem.executeTick)
				break;

			items.push_back(timerItem);
			_items.pop();
		}
	}

	for (TimerItem& item : items)
	{
		if (JobQueueRef owner = item.jobData->owner.lock())
			owner->Push(item.jobData->job);

		ObjectPool<JobData>::Push(item.jobData);
	}

	// 끝났으면 풀어준다
	_distributing.store(false);
}