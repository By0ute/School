#include "TestObj.hh"

TestObj::TestObj()
{
}

//TestObj::TestObj(list<Sign*> ls, list<string> ids) :
    //listSign(ls), identities(ids)
//{
//}


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


//list<Sign*>
//TestObj::get_listSign()
//{
    //return listSign;
//}

//list<string>
//TestObj::get_identities()
//{
    //return identities;
//}

//void
//TestObj::set_listSign(list<Sign*> ls)
//{
    //listSign = ls;
//}

//void
//TestObj::set_identities(list<string> ids)
//{
    //identities = ids;
//}


