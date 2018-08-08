 ///
 /// @file    cacleManager.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-23 10:32:23
 ///
#ifndef __CC_CACLEMANAGER_H__ 
#define __CC_CACLEMANAGER_H__ 
#include "cacle.h"
#include "TimerThread.h"
#include "configuration.h"
#include "Noncopyable.h"
#include <pthread.h>
#include <string>
#include <map>
using std::string;
using std::map;
namespace cc 
{
class CacleManager
: wd::Noncopyable
{
	public:
		static CacleManager *getInstance();
		static void destory();
		void createCacle(pthread_t);
		Cacle *getCacle(pthread_t);
		void initCacle();
		void update();
		void reset();
	private:
		static CacleManager *_pInstance;
		CacleManager();
		Cacle _globalCacle;	
		map<pthread_t,Cacle> _localCacles;
		wd::TimerThread _timerThread;
};

}//end of namespace
#endif
