#include <iostream>
#include "uklad.h"
std::vector<Result> t(size_t ll ,size_t i,size_t it)
{
    std::vector<Result> k(it);
    for(size_t j=0;j<i;++j)
    {
        Box u(ll,it);
        std::vector<Result> a=u.grind();
        for(int l=0 ;l<it;++l )
        {
            k[l].avg_mass+=a[l].avg_mass;
            k[l].max_size+=a[l].max_size;
            k[l].num_clust+=a[l].num_clust;
            k[l].num_unchenged+=a[l].num_unchenged;
        }
    }
    for(int l=0 ;l<it;++l )
    {
        k[l].avg_mass/=i;
        k[l].max_size/=i;
        k[l].num_clust/=i;
        k[l].num_unchenged/=i;
    }
    return k;
}

int main()
{
    /*size_t ll=0 , aa=0, bb=0;
        std::cout << "roz" << std::endl;
        std::cin >> ll ;
        std::cout << "\nusr" << std::endl;
        std::cin >> aa ;
        std::cout << "\niter" << std::endl;
        std::cin >> bb ;
    */

	std::vector<Result> a = t(10,5,30);
	int k=0;
	for(std::vector<Result>::iterator i=a.begin();i!=a.end();++i)
	{
        std::cout << k ;
		std::cout << "\t" << i->avg_mass ;
		std::cout << "\t" << i->max_size ;
		std::cout << "\t" << i->num_clust ;
		std::cout << "\t" << i->num_unchenged ;
        std::cout << std::endl;
        ++k;
	}
	return 0;;
}
