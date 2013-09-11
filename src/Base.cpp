#include "Base.hh"

Base::Base()
    : signatures_ ()
{
}

Base::Base(set<Sign> s)
    : signatures_ (s)
{
}

Base::~Base()
{
}

set<Sign>
Base::get_signatures() const
{
    return signatures_;
}

void
Base::set_signatures(set<Sign> s)
{
    signatures_ = s;
}

void
Base::add_signature(Sign s)
{
   signatures_.insert(s);
}
