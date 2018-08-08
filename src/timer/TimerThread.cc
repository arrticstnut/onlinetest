 ///
 /// @file    TimerThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-10 11:10:18
 ///

#include "TimerThread.h"
#include <iostream>

using std::cout;
using std::endl;


namespace wd
{

TimerThread::TimerThread(const TimerCallback & cb, int initialTime, int intervalTime)
: _timer(cb, initialTime, intervalTime)
, _thread(std::bind(&Timer::start, &_timer))
, _isStarted(false)
{
}

TimerThread::~TimerThread()
{
	if(_isStarted)
		stop();

}

void TimerThread::start()
{
	_isStarted = true;
	_thread.start();
}

void TimerThread::stop()
{
	if(_isStarted)
	{
		_isStarted = false;
		_timer.stop();
		_thread.join();
	}
}

}//end of namespace wd
