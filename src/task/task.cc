///
/// @file    task.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2017-07-18 12:13:11
///

#include "task.h"
#include "configuration.h"
#include "wordQuery.h"
#include <string.h>
namespace cc
{

	Task::Task(wd::TcpConnectionPtr spConn,WordQuery * wordQueryPtr,RedisPool *redisPtr,string & queryStr)
		:_spConn(spConn)
		 ,_wordQueryPtr(wordQueryPtr)
		 ,_redisPtr(redisPtr)
		 ,_queryStr(queryStr)
	{}


	void Task::process(){//处理查词任务（由子线程执行）
		string hashKey = Configuration::getInstance().getConfMap()["CacheHashKey"];//hashkey的名称
		string field = _queryStr;//键值对的key
		string result;
		bool isFound = _redisPtr->ExecuteCmdBy_3_InputArgs("HGET",hashKey,field,result);
		if(!isFound || result.empty()){//在缓存中没找到,执行查询
			auto ret = _wordQueryPtr->doQuery(_queryStr);
			_spConn->sendAndClose(ret);
			//写入缓存
			_redisPtr->ExecuteCmdBy_4_InputArgs("HSET",hashKey,field,ret,result);
		}else{//发送缓存中的数据
			_spConn->sendAndClose(result);
		}
	}


#if 0
	string resultWord = "{\"files\":[{\"title\":\"baidu\",\"url\":\"https://www.baidu.com\",\"summary\":\"百度一下，你懂得\"},{\"title\":\"google\",\"url\":\"https://www.google.com\",\"summary\":\"google一下，你更懂得\"}]}\n";
	cout<<resultWord<<endl;
	_spConn->sendAndClose(resultWord);
	//_spConn->sendInLoop(resultWord);
#endif

};//namespace cc
