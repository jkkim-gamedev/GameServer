#pragma once

#include "Job.h"
#include "LockQueue.h"
#include "JobTimer.h"

class JobQueue : public enable_shared_from_this<JobQueue>
{
public:
	void					Push(JobRef job, bool pushOnly = false);
	void					Execute();

protected:
	LockQueue<JobRef>		_jobs;
	Atomic<int32>			_jobCount = 0;
};
