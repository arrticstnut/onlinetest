///
/// @file    task.h
/// @author  lemon(haohb13@gmail.com)
/// @date    2017-07-17 16:04:50
///
#ifndef __CC_TASK_H__
#define __CC_TASK_H__
#include "TcpConnection.h"
#include "wordQuery.h"
#include "redisPool.h"
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
			Task(wd::TcpConnectionPtr spConn,WordQuery *wordQueryPtr,RedisPool *redisPtr,string & queryStr);
			void process();
		private:
			wd::TcpConnectionPtr _spConn;
			WordQuery * _wordQueryPtr;
			RedisPool * _redisPtr;
			string _queryStr;
	};
}//namespace cc
#endif
