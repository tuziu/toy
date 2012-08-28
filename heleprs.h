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
	const size_t mSize;
public:
	DE(const std::vector<size_2t>& ss,const Cykling_Indeks& ii,const size_t aSize)		
		: s_(ss), i_(ii) , mSize(aSize)
    {}
	size_2t operator() (const size_2t x,const size_2t y) const
	{
		return s_[two2one(x,y,mSize)]*(
                s_[two2one(i_(x+1),y,mSize)]+
                s_[two2one(x,i_(y+1),mSize)]+
                s_[two2one(i_(x-1),y,mSize)]+
                s_[two2one(x,i_(y-1),mSize)]
                );
	}
};

class Obracacz
{
	std::vector<size_2t>& s_;
	const size_t mSize;
public:
	Obracacz(std::vector<size_2t>& ss,const size_t aSize)
		: s_(ss) , mSize(aSize) 
    {}
	void operator() (const size_2t x,const size_2t y)
	{
		s_[two2one(x,y,mSize)]*=-1;
	}
};



#endif
