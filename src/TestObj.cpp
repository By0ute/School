#include "TestObj.hh"

TestObj::TestObj()
{
}


TestObj::TestObj(list<pair<Sign*, string> > t)
    : tests_ (t)
{
}

TestObj::~TestObj()
{
}

list<pair<Sign*, string> >
TestObj::get_tests()
{
    return tests_;
}


void
TestObj::set_test(list<pair<Sign*, string> > t)
{
    tests_ = t;
}

