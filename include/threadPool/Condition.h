 ///
 /// @file    Condition.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-05 10:57:32
 ///
 
#ifndef __WD_CONDITION_H__
#define __WD_CONDITION_H__

#include "Noncopyable.h"
#include <pthread.h>


namespace wd
{

class MutexLock;

class Condition
: Noncopyable
{
public:
	Condition(MutexLock & mutex);

	~Condition();

	void wait();
	void notify();
	void notifyall();

private:
	pthread_cond_t _cond;
	MutexLock & _mutex;
};

}//end of namespace wd

#endif
