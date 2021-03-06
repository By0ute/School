#include "VecParam.hh"

using namespace std;

VecParam::VecParam()
    : x_ (0),
    y_ (0),
    timeStamp_ (0),
    position_ (0),
    azimut_ (0),
    altitude_ (0),
    pression_ (0)
{
}


VecParam::VecParam(int x, int y, int t, int po, int a, int alt, int pr)
    : x_ (x),
    y_ (y),
    timeStamp_ (t),
    position_ (po),
    azimut_ (a),
    altitude_ (alt),
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
VecParam::get_timeStamp() const
{
    return timeStamp_;
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
VecParam::get_altitude() const
{
	return altitude_;
}

int
VecParam::get_pression() const
{
    return pression_;
}


/**
 *  returns [x, y, timeStamp, position, azimut, altitude, pression]
 */
vector<int>
VecParam::get_vector_params() const
{
    vector<int> res;

    res.push_back(x_); // x
    res.push_back(y_); // y
    res.push_back(timeStamp_); // time of this point
    res.push_back(position_); // pen up or down
    res.push_back(azimut_); // azimut
    res.push_back(altitude_); // altitude
    res.push_back(pression_); // pression

    return res;
}


/**
 *  setter
 */
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
VecParam::set_timeStamp(int t)
{
    timeStamp_ = t;
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
VecParam::set_altitude(int a)
{
    altitude_ = a;
}

void
VecParam::set_pression(int p)
{
    pression_ = p;
}

void
VecParam::set_vector_params(vector<int> params)
{
   x_ = params[0];
   y_ = params[1];
   timeStamp_ = params[2];
   position_ = params[3];
   azimut_ = params[4];
   altitude_ = params[5];
   pression_ = params[6];
}


/**
 *  utils
 */
void
VecParam::print()
{
    cout << "x : " << x_ << endl;
    cout << "y : " << y_ << endl;
    cout << "timeStamp : " << timeStamp_ << endl;
    cout << "position : " << position_ << endl;
    cout << "azimut : " << azimut_ << endl;
    cout << "altitude : " << altitude_ << endl;
    cout << "pression : " << pression_ << endl;
}
