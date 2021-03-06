#ifndef U_2ZIU_K
#define U_2ZIU_K

#include "def.h"

#include <vector>
#include "Cykling_Indeks.h"

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
	void cheng_p(double );
	void reset();

    void iterate();
    Result get_results();

private:
    int is_claster(size_2t& cl_size, const size_2t ,const size_2t );
	size_2t how_many_unchende() const;
    void step();
};




#endif

