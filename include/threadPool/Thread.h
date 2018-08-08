 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-04 16:01:16
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__
#include "Noncopyable.h"
#include <pthread.h>
#include <functional>

namespace wd
{

class Thread
: Noncopyable
{
public:
	typedef std::function<void()> ThreadCallback;

	Thread(ThreadCallback && cb);
	~Thread();

	void start();

	void join();

	pthread_t getThreadId() const
	{	return _pthId;	}

private:
	static void * threadFunc(void *);

private:
	pthread_t _pthId;
	bool _isRunning;
	ThreadCallback _cb;
};

}//end of namespace wd

#endif