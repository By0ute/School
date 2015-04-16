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

/*
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
*/

vector<int>&
Sign::calculate_moyennes()
{
  vector<int> moyennes;

  // sum values
  list<VecParam>::iterator it;
  for (it = datas_.begin(); it != datas_.end(); ++it)
  {
    auto elt = (*it).get_vector_params();
    for (int i = 0; i < elt.size(); i++)
    {
      if (i >= moyennes.size())
	moyennes.push_back(elt[i]);
      else
	moyennes[i] += elt[i];
    }
  }

  // divide by size
  for (int i = 0; i < moyennes.size(); i++)
    moyennes[i] /= datas_.size();

  return moyennes;
}

vector<int>&
Sign::calculate_variances()
{
  auto moyennes = calculate_moyennes();
  vector<int> variances;

  // sum
  list<VecParam>::iterator it;
  for (it = datas_.begin(); it != datas_.end(); ++it)
  {
    auto elt = (*it).get_vector_params();
    for (int i = 0; i < elt.size(); i++)
    {
      auto value = (elt[i] - moyennes[i]);
      auto squared = (value * value);
      if (i >= variances.size())
	variances.push_back(squared);
      else
	variances[i] += squared;
    }
  }

  // divide by size
  for (int i = 0; i < variances.size(); i++)
    variances[i] /= datas_.size();

  return variances;
}

int
Sign::calculate_cov_x_y()
{
  list<VecParam>::iterator it;

  // calculate E(X) and E(Y)
  int esperance_x = 0;
  int esperance_y = 0;
  for (it = datas_.begin(); it != datas_.end(); ++it)
  {
    auto elt = (*it);
    esperance_x += elt.get_x();
    esperance_y += elt.get_y();
  }
  esperance_x /= datas_.size();
  esperance_y /= datas_.size();

  // calculate cov(X, Y) = E((X - E(X)) * (Y - E(Y)))
  int cov_x_y = 0;
  for (it = datas_.begin(); it != datas_.end(); ++it)
  {
    auto elt = (*it);
    cov_x_y += ((elt.get_x() - esperance_x) * (elt.get_y() - esperance_y));
  }
  cov_x_y /= datas_.size();

  return cov_x_y;
}

list<VecParam>&
Sign::get_pen_down()
{
  list<VecParam>& result = *(new list<VecParam>());

  list<VecParam>::iterator it;
  for (it = datas_.begin(); it != datas_.end(); ++it)
  {
    VecParam elt = (*it);
    if (elt.get_position() == 1)
      result.push_back(elt);
  }

  return result;
}

void
Sign::normalize()
{
  /* WARNING: ONLY CONSIDERS PEN DOWN POINTS
  auto datas = get_pen_down();
  //*/
  auto datas = datas_;
  //*/
  int slice_size = datas.size() / NORMA_SIZE;
  vector<list<VecParam> > slices(NORMA_SIZE);

  // split the list of entries into NORMA_SIZE sublists
  list<VecParam>::iterator it;
  int k = 0;
  for (it = datas.begin(); it != datas.end(); it++)
  {
    VecParam elt = (*it);

    int index = k / slice_size;
    if (index >= NORMA_SIZE)
      index = NORMA_SIZE - 1;

    slices[index].push_back(elt);

    k++;
  }

  // normalize each VecParam and update datas_
  datas_.clear();
  for (int i = 0; i < slices.size(); i++)
  {
    int slice_size = slices[i].size();
    if (slice_size == 0)
    {
      /*
      VecParam v;
      datas_.push_back(v);
      */
      cerr << "Error: Sign.normalize(): no vector in slice." << endl;
    }
    else
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
