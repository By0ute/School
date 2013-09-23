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
Sign::find_tmin()
{
  list<VecParam>::iterator it = datas_.begin();
  int tmin = INT_MAX;

  for (it = datas_.begin(); it != datas_.end(); it++)
  {
    int ttemp = it->get_timeStamp();

    if (ttemp < tmin)
      tmin = ttemp;
  }

  return tmin;
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
  int time_min = find_tmin();
  int time_max = find_tmax();
  int duration = time_max - time_min;
  int slice = (duration / NORMA_SIZE);

  vector<list<VecParam> > slices(NORMA_SIZE);

  // split the list of entries into NORMA_SIZE sublists
  list<VecParam>::iterator it;
  for (it = datas_.begin(); it != datas_.end(); it++)
  {
    VecParam elt = (*it);
    int timeStamp = elt.get_timeStamp();
    int index = (timeStamp - time_min) / slice;
    if (index == NORMA_SIZE)
      index--;

    slices[index].push_back(elt);
  }

  // normalize each VecParam and update datas_
  datas_.clear();
  for (int i = 0; i < slices.size(); i++)
  {
    int slice_size = slices[i].size();
    if (slice_size == 0)
    {
      cerr << "Warning: normalized signature of " << id_
	   << ": line number " << (i + 1) << " is wrong..." << endl;
    }
    datas_.push_back(norma_vect(slices[i]));
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
