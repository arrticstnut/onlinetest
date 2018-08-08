 ///
 /// @file    TimerThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-10 11:08:36
 ///
 
#ifndef __WD_TIMERTHREAD_H__
#define __WD_TIMERTHREAD_H__

#include "Timer.h"
#include "Thread.h"
#include <iostream>
using std::cout;
using std::endl;


namespace wd
{

class TimerThread
{
public:
	typedef std::function<void()> TimerCallback;
	TimerThread(const TimerCallback & cb, int initialTime, int intervalTime);
	~TimerThread();

	void start();
	void stop();
private:
	Timer _timer;
	Thread _thread;
	bool _isStarted;
};

}//end of namespace wd


#endif
