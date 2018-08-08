 ///
 /// @file    startServer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-22 08:42:35
 ///
#include <string>
#include "configuration.h"
#include "wordSegmentation.h"
#include "wordQuery.h"

void test1(){
	cc::Configuration conf("../configuration/configuration.conf");
	cc::WordSegmentation jieba;
	cc::WordQuery wordQuery(conf,jieba);
	//=============================
	cout << "TESt 0000000000" << endl;
	//=============================
	wordQuery.doQuery("程序");
	//vector<string> testVec {"襄阳","360","我是特征吧"};
	//auto ret = wordQuery.getQueryWordsWeightVector(testVec);
	//for(auto & elem:ret){
	//	cout << elem << endl;
	//}
}

int main(){
	test1();
	return 0;
}
