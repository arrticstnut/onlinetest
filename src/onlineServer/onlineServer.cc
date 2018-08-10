///
/// @file    onlineServer.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2017-07-21 14:30:44
///
#include "onlineServer.h"

namespace cc
{
	OnlineServer::OnlineServer(Configuration & conf)
		:_conf(conf)
		 ,_wordQuery(conf)
		 ,_threadPool(stoi((_conf.getConfMap())["threadNum"]),stoi((_conf.getConfMap())["queSize"]))
		 ,_tcpServer(_conf.getConfMap()["ip"].c_str(),stoi(_conf.getConfMap()["port"]))
	{
		using namespace std::placeholders;
		_threadPool.start();
		_tcpServer.setConnectionCallback(&OnlineServer::onConnection);
		_tcpServer.setMessageCallback(std::bind(&OnlineServer::onMessage,_1,&_wordQuery,&_threadPool));
		_tcpServer.setCloseCallback(&OnlineServer::onClose);
		_tcpServer.start();
	}
	void OnlineServer::onConnection(const wd::TcpConnectionPtr & conn){
		printf("\n> %s has connected!\n", conn->toString().c_str());
		//conn->send("hello, welcome to Chat Server.\n");
	}

	//接收客户端信息，将收到的信息交给线程池处理
	void OnlineServer::onMessage(const wd::TcpConnectionPtr & conn,WordQuery * wordQueryPtr,wd::Threadpool *pThreadPool){
		string querWord(conn->receive());
		if(!querWord.empty()){
			auto it =querWord.end()-1;
			if(*it=='\n'){
				querWord.erase(it);
			}
		}
		(*pThreadPool).addTask(std::bind(&Task::process,Task(conn,wordQueryPtr,querWord)));
	}
	void OnlineServer::onClose(const wd::TcpConnectionPtr & conn){
		printf("> %s has closed. \n", conn->toString().c_str());
	}
}//namespace cc
