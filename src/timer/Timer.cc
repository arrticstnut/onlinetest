 ///
 /// @file    Timer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-10 10:05:54
 ///
 
#include "Timer.h"

#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/timerfd.h>
#include <iostream>

using std::cout;
using std::endl;


namespace wd
{

Timer::Timer(const TimerCallback & cb, int initialTime, int intervalTime)
: _fd(createTimerfd())
, _initialTime(initialTime)
, _intervalTime(intervalTime)
, _cb(cb)
, _isStarted(false)
{

}

Timer::~Timer()
{
	if(_isStarted)
		stop();
}

void Timer::start()
{
	_isStarted = true;
	setTimerfd(_initialTime, _intervalTime);

	struct pollfd pfd;
	pfd.fd = _fd;
	pfd.events = POLLIN;

	while(_isStarted)
	{
		int nready = ::poll(&pfd, 1, -1);
		if(nready == -1 && errno == EINTR)
			continue;
		else if(nready == -1)
		{
			perror("poll error");
			return ;
		}
		else if(nready == 0)
			printf("> poll timeout\n");
		else
		{// 有文件描述符就绪
			if(pfd.fd == _fd && (pfd.revents & POLLIN) )
			{
				handleRead();//该操作必须要有,不可少
				if(_cb)
					_cb();//执行任务
			}
		}
	}
}


void Timer::stop()
{
	if(_isStarted)
	{
		setTimerfd(0, 0);
		_isStarted = false;
	}
}

int Timer::createTimerfd()
{
	int fd = ::timerfd_create(CLOCK_REALTIME, 0);
	if(-1 == fd)
	{
		perror("timerfd_create error");	
	}
	return fd;
}

void Timer::setTimerfd(int initialTime, int intervalTime)
{
	struct itimerspec value;
	value.it_value.tv_sec = initialTime;
	value.it_value.tv_nsec = 0;
	value.it_interval.tv_sec = intervalTime;
	value.it_interval.tv_nsec = 0;

	int ret = timerfd_settime(_fd, 0, &value, NULL);
	if(ret == -1)
	{
		perror("timerfd_settime error");
	}
}

void Timer::handleRead()
{
	uint64_t  howmany = 0;
	int ret = ::read(_fd, &howmany, sizeof(howmany));
	if(ret != sizeof(howmany))
	{
		perror("read error");
	}
}

}//end of namespace wd
