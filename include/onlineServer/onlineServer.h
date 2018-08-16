///
/// @file    onlineServer.h
/// @author
/// @date    2018-07-20 18:10:38
///
#ifndef __CC_ONLINESERVER_H__
#define __CC_ONLINESERVER_H__
#include "configuration.h" 
#include "wordQuery.h"
#include "Threadpool.h"
#include "redisPool.h"
#include "TcpServer.h"
#include "task.h"
#include <functional>
namespace cc
{
	class OnlineServer
	{
		public:
			OnlineServer(Configuration & conf);
			static void onConnection(const wd::TcpConnectionPtr & conn);
			static void onMessage(const wd::TcpConnectionPtr & conn,WordQuery *wordQueryPtr,RedisPool *redisPtr,wd::Threadpool *pThreadPool);
			static void onClose(const wd::TcpConnectionPtr & conn);
		private:
			Configuration & _conf;
			cc::RedisPool _redis;
			WordQuery _wordQuery;
			wd::Threadpool _threadPool;
			wd::TcpServer _tcpServer;
	};
}//end of namespace
#endif
