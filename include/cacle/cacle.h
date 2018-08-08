 ///
 /// @file    cacle.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-18 22:49:38
 ///
#ifndef __CC_CACLE_H__
#define __CC_CACLE_H__
#include "MutexLock.h"
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

using std::string;
using std::unordered_map;
namespace cc
{
class Cacle
{
	public:
		Cacle(){_isUsing=false;}
		void addData(const string &,const string &);
		void clear();
		void readFile(const string & filenamePath);
		void writeFile(const string & filenamePath);
		void updateAppend(const Cacle &);
	public:
	//	wd::MutexLock _mutex;
		bool _isUsing;
		unordered_map<string,string> _cacleMap;
};
}//namespace cc
#endif
