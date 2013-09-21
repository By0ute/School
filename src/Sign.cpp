#include "Sign.hh"

using namespace std;

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

int
Sign::find_tmax()
{
    list<VecParam>::iterator it = datas_.begin();
    int tmax = 0;

    for (it = datas_.begin(); it != datas_.end(); it++)
    {
	int ttemp = it->get_timeStamp();

	if (ttemp > tmax)
	    tmax = ttemp;
    }

    return tmax;
}

void
Sign::normalize()
{
    map<int, list<VecParam> > vecs_origin;

    int time_max = find_tmax();

    if (time_max > NORMA_SIZE)
    {
	double slice = ((double)time_max /
			(double)(NORMA_SIZE - 1));

	list<VecParam>::iterator it = datas_.begin();
	map<int, list<VecParam> >::iterator it_place;


	for (it = datas_.begin(); it != datas_.end(); it++)
	{
	    double place = (double)it->get_timeStamp() / slice;

	    it_place = vecs_origin.find(place);

	    if (it_place == vecs_origin.end())
		vecs_origin[place] = list<VecParam>();

	    vecs_origin[place].push_back(*it);
	}

	list<VecParam> new_datas;

	for (int i = 0; i < NORMA_SIZE; i++)
	{
	    it_place = vecs_origin.find(i);

	    if (it_place != vecs_origin.end())
		new_datas.push_back(norma_vect(it_place->second));
	}

	datas_ = new_datas;
    }
}

VecParam
Sign::norma_vect(list<VecParam>& list_v)
{
    VecParam res;

    int size = list_v.size();

    vector<int> new_params(7);

    list<VecParam>::iterator it = list_v.begin();

    for (it = list_v.begin(); it != list_v.end(); it++)
    {
	vector<int> params = it->get_vector_params();

	for (int i = 0; i < new_params.size(); i++)
	    new_params[i] += params[i];
    }

    for (int i = 0; i < new_params.size(); i++)
	new_params[i] /= size;

    res.set_vector_params(new_params);

    return res;
}

void
Sign::print()
{
    cout << id_ << " : " << datas_.size() << "vectors" << endl;
}
