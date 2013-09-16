#include "Sign.hh"

Sign::Sign()
    : datas_ ()
{
}

Sign::Sign(string i)
    : datas_ (),
    id_ (i)
{
}

Sign::Sign(list<VecParam> d, string i)
    : datas_ (d),
    id_ (i)
{
}

Sign::~Sign()
{
}

// getter

list<VecParam>
Sign::get_datas() const
{
    return datas_;
}

string
Sign::get_id() const
{
    return id_;
}

// setter

void
Sign::set_datas(list<VecParam> d)
{
    datas_ = d;
}

void
Sign::set_id(string i)
{
    id_ = i;
}

void
Sign::add_data(VecParam v)
{
   datas_.push_back(v);
}
