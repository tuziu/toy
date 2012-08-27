#ifndef HELPERS_H
#define HELPERS_H

#include "def.h"

size_t two2one(const size_t aX,const size_t aY, const size_t aSize)
{
    return (aX * aSize ) + aY;
}

class DE
{
	const std::vector<size_2t>& s_;
	const Cykling_Indeks& i_;
public:
	DE(const std::vector<size_2t>& ss,const Cykling_Indeks& ii): s_(ss), i_(ii) 
    {}
	size_2t operator() (const size_2t x,const size_2t y) const
	{
		return s_[two2one(x,y,s_.size())]*(
                s_[two2one(i_(x+1),y,s_.size())]+
                s_[two2one(x,i_(y+1),s_.size())]+
                s_[two2one(i_(x-1),y,s_.size())]+
                s_[two2one(x,i_(y-1),s_.size())]
                );
	}
};

class Obracacz
{
	std::vector<size_2t>& s_;
public:
	Obracacz(std::vector<size_2t>& ss): s_(ss) 
    {}
	void operator() (const size_2t x,const size_2t y)
	{
		s_[two2one(x,y,s_.size())]*=-1;
	}
};



#endif
