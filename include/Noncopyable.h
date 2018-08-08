 ///
 /// @file    Noncopyable.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-07-04 16:44:07
 ///

#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__
 

namespace wd
{

class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}

private:
	Noncopyable(const Noncopyable &);
	Noncopyable & operator=(const Noncopyable &);
};
}//end of namespace wd

#endif
