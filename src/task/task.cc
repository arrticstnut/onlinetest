 ///
 /// @file    task.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-18 12:13:11
 ///
 
#include "task.h"
#include "configuration.h"
#include <string.h>
namespace cc
{

Task::Task(wd::TcpConnectionPtr spConn,string & taskContent)
:_spConn(spConn)
,_taskContent(taskContent)
{}


void Task::process(){//处理查词任务（由子线程执行）
	string resultWord = "{\"files\":[{\"title\":\"baidu\",\"url\":\"https://www.baidu.com\",\"summary\":\"百度一下，你懂得\"},{\"title\":\"google\",\"url\":\"https://www.google.com\",\"summary\":\"google一下，你更懂得\"}]}\n";
	cout<<resultWord<<endl;
	_spConn->sendAndClose(resultWord);
	//_spConn->sendInLoop(resultWord);
}

}//namespace cc