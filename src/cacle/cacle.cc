 ///
 /// @file    Cacle.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-19 10:03:15
 ///
 
#include "cacle.h"
#include "configuration.h"
namespace cc
{
void Cacle::clear(){
	_cacleMap.clear();
} 

void Cacle::addData(const string & queryWord,const string & restultWord){//将新的数据加入缓存
	if(!_isUsing)
	_cacleMap.insert(std::pair<string,string>(queryWord,restultWord));	
}

void Cacle::readFile(const string & filenamePath){
	std::ifstream ifs;
	ifs.open(filenamePath);
	if(!ifs.good()){
		cout<<"Cacle::readFile open Error"<<endl;	
		ifs.close();
		return;
	}
	string line,queryWord,restultWord;
	while(getline(ifs,line)){
		std::istringstream iss(line);
		iss>>queryWord>>restultWord;
		_cacleMap.insert(std::make_pair(queryWord,restultWord));
	}
	ifs.close();
}

void Cacle::writeFile(const string & filenamePath){
	std::ofstream ofs;
	ofs.open(filenamePath);
	if(!ofs.good()){
		cout<<"Cacle::writeFile open Error"<<endl;	
		ofs.close();
		return;
	}
	unordered_map<string,string>::iterator it=_cacleMap.begin();
	unordered_map<string,string>::iterator end=_cacleMap.end();
	while(it!=end){
		ofs<<it->first<<" "<<it->second<<endl;
		++it;
	}
	ofs.close();
}

void Cacle::updateAppend(const Cacle & rhs){//同步本地磁盘缓存文件
	unordered_map<string,string>::const_iterator beg=rhs._cacleMap.begin();
	unordered_map<string,string>::const_iterator end=rhs._cacleMap.end();
	while(beg!=end){
		_cacleMap.insert(*beg++);
	}
}
}//namespace cc

