 ///
 /// @file    Threadpool.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-05 17:02:11
 ///
 
#ifndef __WD_THREADPOOL_H__
#define __WD_THREADPOOL_H__

#include "TaskQueue.h"

#include <iostream>
#include <vector>
#include <memory>
#include <functional>
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;


namespace wd
{

typedef std::function<void()> Task;

class Thread;

class Threadpool
{
public:
	Threadpool(size_t threadNum, size_t queSize);
	~Threadpool();

	void start();
	void stop();
	void addTask(const Task & task);
private:
	Task getTask();

	void threadFunc();

private:
	size_t _threadNum;
	size_t _queSize;
	vector<shared_ptr<Thread>> _threads;
	TaskQueue _taskQue;
	bool _isExit;
};

}//end of namespace wd

#endif
