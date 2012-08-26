#ifndef U_2ZIU_K
#define U_2ZIU_K

#include "mtrand.h"
#include <iostream>
#include <ctime>
#include <cassert>
#include <vector>
#include <cmath>

typedef signed int size_2t;

struct Result
{
	double avg_mass;
	size_2t max_size;
	size_2t num_clust;
	size_2t num_unchenged;
};

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





class UkladEwol
{
private:
	size_2t rozmiar_;
	const Cykling_Indeks m_indeks;
	size_2t **stany_;
	size_2t **m_chenged;
	double m_prawd;
	size_2t **tab;


public:
	UkladEwol(size_2t size, double p);
	~UkladEwol();

private:
	UkladEwol();
	UkladEwol(UkladEwol const &);
	UkladEwol& operator=(UkladEwol const &);

public:
	inline void cheng_p(double );
	void reset();

public:
    inline void iterate();
    Result get_results();

private:
    int is_claster(size_2t& cl_size, size_2t ,size_2t );
	inline size_2t how_many_unchende();
    void step();

private:
    template<typename T>
    static T** create_tab(size_2t i);
};

void UkladEwol::cheng_p(double p)
{
	m_prawd=p;
}

inline void UkladEwol::iterate()
{
    for(size_2t i=0;i<pow(rozmiar_,2);++i)
    {
        step();
    }
}

inline size_2t UkladEwol::how_many_unchende()
{
    size_2t h=0;
    for(size_2t i=0;i<rozmiar_;++i)
    {
        for(size_2t j=0;j<rozmiar_;++j)
        {
            h+=m_chenged[i][j];
        }
    }
    return h;
}

class DE
{
	private:
		size_2t ** s_;
		const Cykling_Indeks& i_;
	public:
		DE(size_2t ** ss,const Cykling_Indeks& ii): s_(ss), i_(ii) {}
		size_2t operator() (size_2t x,size_2t y)
		{
			return s_[x][y]*(
                    s_[i_(x+1)][y]+
                    s_[x][i_(y+1)]+
                    s_[i_(x-1)][y]+
                    s_[x][i_(y-1)]
                    );
		}
};

class Obracacz
{
private:
	size_2t ** s_;
public:
	Obracacz(size_2t ** ss): s_(ss) {}
	void operator() (size_2t x,size_2t y)
	{
		s_[x][y]*=-1;
	}
};

class Box
{
private:
    size_t m_num_of_it;
    UkladEwol m_u;
    std::vector<Result> m_r;

public:
    Box(size_2t u_size,size_t nu_i, double p=0.5);

private:
    Box();
    Box(const Box&);
    Box& operator = (const Box& );

public:
    std::vector<Result> grind();

};
#endif

