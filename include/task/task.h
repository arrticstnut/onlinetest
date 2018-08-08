///
/// @file    task.h
/// @author  lemon(haohb13@gmail.com)
/// @date    2017-07-17 16:04:50
///
#ifndef __CC_TASK_H__
#define __CC_TASK_H__
#include "TcpConnection.h"
#include "cacleManager.h"
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
using std::cout;
using std::endl;
using std::string;

namespace cc
{

	class Task
	{
		public:
			Task(wd::TcpConnectionPtr spConn,string & taskContent);
			void process();
		private:
			wd::TcpConnectionPtr _spConn;
			string _taskContent;
	};
}//namespace cc
#endif
