#include "box.h"

std::vector<Result> Box::grind()
{
    m_u.reset();
    std::vector<Result> res;
    for(size_t i=0;i<m_num_of_it;++i)
    {        
        m_u.iterate();        
        res.push_back(m_u.get_results());
    }
    return res;
}

Box::Box(size_2t u_size,size_t nu_i, double p)
    : m_num_of_it(nu_i), m_u(u_size,p)
{}
