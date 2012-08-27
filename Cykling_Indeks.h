#ifndef CI_H
#define CI_H

#include "def.h"
#include <cassert>

class Cykling_Indeks
{
private:
	const size_2t m_uper_border;

public:
	Cykling_Indeks(const size_2t uper_border): m_uper_border(uper_border) 
    {}

	size_2t operator() (const size_2t i) const
	{
		assert(-1 <= i);
		assert(i<=m_uper_border);
		if(i == -1)
		{
			return m_uper_border-1;
		}
		if(i == m_uper_border)
		{
			return 0;
		}
		return i;
	}
};
#endif
