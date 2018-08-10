 ///
 /// @file    onlineServer.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-20 18:10:38
 ///
#ifndef __CC_ONLINESERVER_H__
#define __CC_ONLINESERVER_H__
#include "configuration.h" 
#include "wordQuery.h"
#include "Threadpool.h"
#include "TcpServer.h"
#include "task.h"
#include "cacleManager.h"
#include <functional>
namespace cc
{
class OnlineServer
{
	public:
		OnlineServer(Configuration & conf);
		static void onConnection(const wd::TcpConnectionPtr & conn);
		static void onMessage(const wd::TcpConnectionPtr & conn,WordQuery *wordQueryPtr,wd::Threadpool *pThreadPool);
		static void onClose(const wd::TcpConnectionPtr & conn);
	private:
		Configuration & _conf;
		WordQuery _wordQuery;
		wd::Threadpool _threadPool;
		wd::TcpServer _tcpServer;
};
}//namespace cc
#endif
