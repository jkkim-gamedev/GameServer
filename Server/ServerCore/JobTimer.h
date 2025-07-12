#pragma once

struct JobData
{
	JobData(weak_ptr<JobQueue> owner, JobRef job) : owner(owner), job(job)
	{

	}

	weak_ptr<JobQueue>	owner;
	JobRef				job;
};

struct TimerItem
{
	bool operator<(const TimerItem& other) const
	{
		return executeTick > other.executeTick;
	}

	uint64 executeTick = 0;
	JobData* jobData = nullptr;
};

/*--------------
	JobTimer
---------------*/

class JobTimer
{
public:
	void			Distribute(uint64 now);

private:
	USE_LOCK;
	PriorityQueue<TimerItem>	_items;
	Atomic<bool>				_distributing = false;
};

