#include "TestObj.hh"

TestObj::TestObj()
{
}

TestObj::TestObj(list<Sign*> ls, list<string> ids) :
    listSign(ls), identities(ids)
{
}

TestObj::~TestObj()
{
}

list<Sign*>
TestObj::get_listSign()
{
    return listSign;
}

list<string>
TestObj::get_identities()
{
    return identities;
}

void
TestObj::set_listSign(list<Sign*> ls)
{
    listSign = ls;
}

void
TestObj::set_identities(list<string> ids)
{
    identities = ids;
}
