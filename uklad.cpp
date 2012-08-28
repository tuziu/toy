#include "uklad.h"
#include "mtrand.h"
#include <ctime>
#include "heleprs.h"
#include <cmath>


UkladEwol::UkladEwol(const size_2t ii,double p)
	: rozmiar_(ii), m_indeks(ii), stany_(std::pow(static_cast<double>(rozmiar_),2)),
        m_chenged(std::pow(static_cast<double>(rozmiar_),2)), m_prawd(p),tab(std::pow(static_cast<double>(rozmiar_),2))
{
	assert(0<ii);
}

UkladEwol::~UkladEwol()
{
}

void UkladEwol::cheng_p(double p)
{
	m_prawd=p;
}

void UkladEwol::iterate()
{
    for(size_2t i=0;i<std::pow(static_cast<double>(rozmiar_),2);++i)
    {
        step();
    }
}

size_2t UkladEwol::how_many_unchende() const
{
    size_2t h=0;
    for(size_2t i=0;i<std::pow(static_cast<double>(rozmiar_),2);++i)
    {
        h+=m_chenged[i];
    }
    return h;
}

void UkladEwol::reset()
{
	static MTRand a(std::time(NULL));
	for(size_2t i=0;i<std::pow(static_cast<double>(rozmiar_),2);++i)
	{
		stany_[i]= ( a() < m_prawd ) ? 1 : -1;			
		m_chenged[i] =1 ;		
	}
}

void UkladEwol::step()
{
    static MTRand_int32 rand(std::time(NULL));
    const size_2t i = rand()%rozmiar_;
    const size_2t j = rand()%rozmiar_;
    DE en(stany_,m_indeks,rozmiar_);
    const double e = en(i,j);
    if(e<0)
    {
        Obracacz o(stany_,rozmiar_);
        o(i,j);
        m_chenged[two2one(i,j,rozmiar_)]=0;
    }
    else if(e ==0)
    {
        static MTRand randd(std::time(NULL));
        if(0.5<randd())
        {
            Obracacz o(stany_,rozmiar_);
            o(i,j);
            m_chenged[two2one(i,j,rozmiar_)]=0;
        }
    }

}

Result UkladEwol::get_results()
{
    Result r;
    
    tab=stany_;
        
    r.num_clust=0;
    r.max_size=0;

    size_2t sum_cl=0;
    for(size_2t i=0;i<std::pow(static_cast<double>(rozmiar_),2);++i)
    {
        if(tab[i]==1)
        {
            ++r.num_clust;
            size_2t cl_s=0;
            is_claster(cl_s,i,i%rozmiar_);
            if(cl_s>r.max_size)
            {
                r.max_size=cl_s;
            }
            sum_cl+=cl_s;
        }       
    }
    if(r.num_clust!=0)
    {
        r.avg_mass=sum_cl/r.num_clust;
    }
    else
    {
        r.avg_mass=0;
    } 
	
	r.num_unchenged=how_many_unchende();


    return r;
}


int UkladEwol::is_claster(size_2t& cl_size,const size_2t x,const size_2t y)
{
    if(tab[two2one(x,y,rozmiar_)]==1)
    {
	    ++cl_size;
	    tab[two2one(x,y,rozmiar_)]=-1;
        is_claster(cl_size,m_indeks(x-1),y);
        is_claster(cl_size,x,m_indeks(y+1));
        is_claster(cl_size,x,m_indeks(y-1));
        is_claster(cl_size,m_indeks(x+1),y);
    }
	return 0;
}


