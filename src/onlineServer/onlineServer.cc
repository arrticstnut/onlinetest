///
/// @file    onlineServer.cc
/// @author
/// @date    2018-07-21 14:30:44
///
//
#include "onlineServer.h"
#include "cppLog.h"

namespace cc
{
	OnlineServer::OnlineServer(Configuration & conf)
		:_conf(conf)
		 ,_redis(_conf.getConfMap()["RedisServerIp"].c_str(),stoi(_conf.getConfMap()["RedisServerPort"]))
		 ,_wordQuery(conf)
		 ,_threadPool(stoi((_conf.getConfMap())["threadNum"]),stoi((_conf.getConfMap())["queSize"]))
		 ,_tcpServer(_conf.getConfMap()["ip"].c_str(),stoi(_conf.getConfMap()["port"]))
	{
		using namespace std::placeholders;
		_threadPool.start();
		_tcpServer.setConnectionCallback(&OnlineServer::onConnection);
		_tcpServer.setMessageCallback(std::bind(&OnlineServer::onMessage,_1,&_wordQuery,&_redis,&_threadPool));
		_tcpServer.setCloseCallback(&OnlineServer::onClose);
		_tcpServer.start();
	}
	void OnlineServer::onConnection(const wd::TcpConnectionPtr & conn){
		string connInfo = conn->toString() + " [--connected--] ";
		logInfo(connInfo.c_str());
	}

	//接收客户端信息，将收到的信息交给线程池处理
	void OnlineServer::onMessage(const wd::TcpConnectionPtr & conn,WordQuery * wordQueryPtr,RedisPool *redisPtr,wd::Threadpool *pThreadPool){
		string querWord(conn->receive());
		if(!querWord.empty()){
			auto it =querWord.end()-1;
			if(*it=='\n'){
				querWord.erase(it);
			}
		}

		string messageInfo = conn->toString() + " [--query--] " + querWord;
		logInfo(messageInfo.c_str());

		(*pThreadPool).addTask(std::bind(&Task::process,Task(conn,wordQueryPtr,redisPtr,querWord)));
	}
	void OnlineServer::onClose(const wd::TcpConnectionPtr & conn){
		string closeInfo = conn->toString() + " [--closed--] ";
		logInfo(closeInfo.c_str());
	}
}//namespace cc
