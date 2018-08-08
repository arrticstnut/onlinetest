 ///
 /// @file    cacleManager.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-23 11:06:34
 ///

#include "cacleManager.h"

namespace cc
{
CacleManager *CacleManager::_pInstance=new CacleManager;

CacleManager *CacleManager::getInstance(){
	if(!_pInstance){
		_pInstance=new CacleManager;	
	}
	return _pInstance;
}

void CacleManager::destory(){
	if(_pInstance){
		delete _pInstance;
		_pInstance=nullptr;
	}
}

CacleManager::CacleManager()
:_timerThread(std::bind(&CacleManager::update,this),600,600)//每10分钟自动更新缓存
{
	initCacle();
	_timerThread.start();
}

void CacleManager::createCacle(pthread_t pid){
	Cacle pthCacle;
	pthCacle.updateAppend(_globalCacle);
	_localCacles.insert(map<pthread_t,Cacle>::value_type(pid,pthCacle));
}

Cacle *CacleManager::getCacle(pthread_t pid){
	auto it=_localCacles.find(pid);
	if(it!=_localCacles.end()){
		return &(it->second);
	}else{
		return nullptr;	
	}
}

void CacleManager::initCacle(){
	std::ifstream ifs;
    string caclePath;
    string queryWord;
    string restultWord;
    {
		//================================================================================================
        //Configuration conf; 
        //auto confMap=conf.getConfMap();
        //caclePath=confMap["cacle"];
		//================================================================================================
    }
    ifs.open(caclePath);
    if(ifs.good()){//判断是否有本地缓存
		ifs.close();
		_globalCacle.readFile(caclePath);
    }
    ifs.close();	
}

void CacleManager::update(){
	map<pthread_t,Cacle>::iterator beg=_localCacles.begin();
	map<pthread_t,Cacle>::iterator end=_localCacles.end();
	//将各个子线程缓存更新到全局缓存
	while(beg!=end){
		beg->second._isUsing=true;//防止在更新的时候写入新数据，以免迭代器失效
		_globalCacle.updateAppend(beg->second);
		beg->second._isUsing=false;
		++beg;
	}
	//更新各个子线程缓存为全局缓存
	beg=_localCacles.begin();
	while(beg!=end){
		beg->second._isUsing=true;
		beg->second.updateAppend(_globalCacle);
		beg->second._isUsing=false;
		++beg;
	}
	//将全局缓存写入磁盘文件
	string caclePath;
    {
		//==========================================================================
        //Configuration conf; 
        //auto confMap=conf.getConfMap();
        //caclePath=confMap["cacle"];
		//==========================================================================
    }
	_globalCacle.writeFile(caclePath);	
}

void CacleManager::reset(){
	map<pthread_t,Cacle>::iterator beg=_localCacles.begin();
	map<pthread_t,Cacle>::iterator end=_localCacles.end();
	while(beg!=end){
		beg->second._isUsing=true;//防止在更新的时候写入新数据，以免迭代器失效
		beg->second.clear();	
		beg->second._isUsing=false;
		++beg;
	}
}


}//end of namespace cc
