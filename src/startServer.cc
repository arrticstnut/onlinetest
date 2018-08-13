 ///
 /// @file    startServer.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-22 08:42:35
 ///
#include <string>
#include "configuration.h"
#include "wordSegmentation.h"
#include "wordQuery.h"
#include "onlineServer.h"
#include <unistd.h>

void test1(){
	daemon(1,0);
	cc::Configuration conf = cc::Configuration::getInstance();
	cc::OnlineServer ser(conf);
}

int main(){
	test1();
	return 0;
}
