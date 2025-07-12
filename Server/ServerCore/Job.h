#pragma once

#include <functional>

using CallbackType = std::function<void()>;

class Job
{
public:
	void Execute()
	{
		_callback();
	}

private:
	CallbackType _callback;
};

