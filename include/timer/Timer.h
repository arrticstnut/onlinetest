 ///
 /// @file    Timer.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-10 10:00:45
 ///
 
#ifndef __WD_TIMER_H__
#define __WD_TIMER_H__
#include <iostream>
#include <functional>
using std::cout;
using std::endl;


namespace wd
{

class Timer
{
public:
	typedef std::function<void()> TimerCallback;

	Timer(const TimerCallback & cb, int initialTime, int intervalTime);

	void start();
	void stop();

	~Timer();
private:
	int createTimerfd();
	void handleRead();
	void setTimerfd(int initialTimer, int intervalTime);

private:
	int _fd;
	int _initialTime;
	int _intervalTime;

	TimerCallback _cb;
	bool _isStarted;
};

}//end of namespace wd


#endif
