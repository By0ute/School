#include "VecParam.hh"

using namespace std;

VecParam::VecParam()
    : x_ (0),
    y_ (0),
    position_ (0),
    azimut_ (0),
    pression_ (0)
{
}


VecParam::VecParam(int x, int y, int po, int a, int pr)
    : x_ (x),
    y_ (y),
    position_ (po),
    azimut_ (a),
    pression_ (pr)
{
}

VecParam::~VecParam()
{
}


//getter
int
VecParam::get_x() const
{
    return x_;
}

int
VecParam::get_y() const
{
    return y_;
}

int
VecParam::get_position() const
{
    return position_;
}

int
VecParam::get_azimut() const
{
    return azimut_;
}

int
VecParam::get_pression() const
{
    return pression_;
}

// setter
void
VecParam::set_x(int x)
{
    x_ = x;
}

void
VecParam::set_y(int y)
{
    y_ = y;
}

void
VecParam::set_position(int p)
{
    position_ = p;
}

void
VecParam::set_azimut(int a)
{
    azimut_ = a;
}

void
VecParam::set_pression(int p)
{
    pression_ = p;
}

// utils
void
VecParam::print()
{
    cout << "x : " << x_ << endl;
    cout << "y : " << y_ << endl;
    cout << "position : " << position_ << endl;
    cout << "azimut : " << azimut_ << endl;
    cout << "pression : " << pression_ << endl;
}
