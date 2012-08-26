#include "uklad.h"
#include <cstdlib>




UkladEwol::UkladEwol(size_2t ii,double p)
	: rozmiar_(ii), m_indeks(ii), stany_(create_tab<size_2t>(rozmiar_)),
        m_chenged(create_tab<size_2t>(rozmiar_)), m_prawd(p),tab(create_tab<size_2t>(rozmiar_))
{
	assert(0<ii);
}

template<typename T>
T **UkladEwol::create_tab(size_2t i) // static
{
	T **a;
	a = new T * [i];
	for(size_2t j=0;j<i;++j)
	{
		a[j]=new T [i];
	}
	return a;
}

UkladEwol::~UkladEwol()
{
    for(size_2t i=0;i<rozmiar_;++i)
	{
		delete [] stany_[i];
		delete [] m_chenged[i];
		delete [] tab[i];
	}
	delete [] stany_;
	delete [] m_chenged;
	delete [] tab;
}

Box::Box(size_2t u_size,size_t nu_i, double p)
    : m_num_of_it(nu_i), m_u(u_size,p)
{}




void UkladEwol::reset()
{
	static MTRand a(std::time(NULL));
	for(size_2t i=0;i<rozmiar_;++i)
	{
		for(size_2t j=0;j<rozmiar_;++j)
		{
			if((a()<m_prawd))
			{
				stany_[i][j]=1;
			}
			else
			{
				stany_[i][j]=-1;
			}
			m_chenged[i][j]=1;
		}
	}
}

void UkladEwol::step()
{
    static MTRand_int32 rand(std::time(NULL));
    size_2t i = rand()%rozmiar_;
    size_2t j = rand()%rozmiar_;
    DE en(stany_,m_indeks);
    double e = en(i,j);
    if(e>0)
    { }
    else if(e<0)
    {
        Obracacz o(stany_);
        o(i,j);
        m_chenged[i][j]=0;
    }
    else
    {
        static MTRand randd(std::time(NULL));
        if(0.5<randd())
        {
            Obracacz o(stany_);
            o(i,j);
            m_chenged[i][j]=0;
        }
    }

}

Result UkladEwol::get_results()
{
    Result r;

    for(size_2t i=0;i<rozmiar_;++i)
    {
        for(size_2t j=0;j<rozmiar_;++j)
        {
            tab[i][j]=stany_[i][j];
        }
    }
    size_2t num_cl=0;
    size_2t max_cl=0;
    size_2t sum_cl=0;
    for(size_2t i=0;i<rozmiar_;++i)
    {
        for(size_2t j=0;j<rozmiar_;++j)
        {
            if(tab[i][j]==1)
            {
                ++num_cl;
                size_2t cl_s=0;
                is_claster(cl_s,i,j);
                if(cl_s>max_cl)
                {
                    max_cl=cl_s;
                }
                sum_cl+=cl_s;
            }
        }
    }
    if(num_cl!=0)
    {
        r.avg_mass=sum_cl/num_cl;
    }
    else
    {
        r.avg_mass=0;
    }
    r.max_size=max_cl;
	r.num_clust=num_cl;
	r.num_unchenged=how_many_unchende();


    return r;
}


int UkladEwol::is_claster(size_2t& cl_size, size_2t x,size_2t y)
{
    if(tab[x][y]==1)
    {
	++cl_size;
	tab[x][y]=-1;
    is_claster(cl_size,m_indeks(x-1),y);
    is_claster(cl_size,x,m_indeks(y+1));
    is_claster(cl_size,x,m_indeks(y-1));
    is_claster(cl_size,m_indeks(x+1),y);

    }
	return 0;
}



std::vector<Result> Box::grind()
{
    m_u.reset();
    std::vector<Result> res;
    for(size_t i=0;i<m_num_of_it;++i)
    {

        Result r;
        m_u.iterate();
        r = m_u.get_results();
        res.push_back(r);
    }
    return res;
}
