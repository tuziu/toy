#ifndef U_2ZIU_K
#define U_2ZIU_K

#include <cassert>
#include <vector>
#include <cmath>
#include <cstddef>

typedef signed int size_2t;

struct Result
{
	double avg_mass;
	size_2t max_size;
	size_2t num_clust;
	size_2t num_unchenged;
};

inline size_t two2one(const size_t aX,const size_t aY, const size_t aSize)
{
    return (aX * aSize ) + aY;
}

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
	const size_2t rozmiar_;
	const Cykling_Indeks m_indeks;
	std::vector<size_2t> stany_;
	std::vector<size_2t> m_chenged;
	double m_prawd;
	std::vector<size_2t> tab;

public:
	UkladEwol(const size_2t size,const double p);
	~UkladEwol();

private:
	UkladEwol();
	UkladEwol(UkladEwol const &);
	UkladEwol& operator=(UkladEwol const &);

public:
	inline void cheng_p(double );
	void reset();

    inline void iterate();
    Result get_results();

private:
    int is_claster(size_2t& cl_size, const size_2t ,const size_2t );
	inline size_2t how_many_unchende();
    void step();
};

class DE
{
	private:
		const std::vector<size_2t>& s_;
		const Cykling_Indeks& i_;
	public:
		DE(const std::vector<size_2t>& ss,const Cykling_Indeks& ii): s_(ss), i_(ii) {}
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
private:
	std::vector<size_2t>& s_;
public:
	Obracacz(std::vector<size_2t>& ss): s_(ss) {}
	void operator() (const size_2t x,const size_2t y)
	{
		s_[two2one(x,y,s_.size())]*=-1;
	}
};


#endif

