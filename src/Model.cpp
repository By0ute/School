#include "Model.hh"

Model::Model(id_type id, list<Sign*> signatures)
  : id_(id)
  , ref_sign_(nullptr)
  , signatures_(signatures)
{
  int n = signatures_.size();
  int m = 25;
  //int t = 5;

  list<VecParam> sum_vects;
  for (int j = 0; j < m; ++j) // foreach vector
  {
    VecParam sum_vect;

    list<Sign*>::iterator it_sign = signatures_.begin();
    if (it_sign != signatures_.end())
    {
      sum_vect = (*it_sign)->get_datas()[0];
      it_sign++;
    }
    for (; it_sign != signatures_.end(); ++it_sign) // foreach signature
    {
      VecParam vector = (*it_sign)->get_datas()[j];

      // sum j-th vector from all signatures into sum_vect
      sum_vect.set_x(sum_vect.get_x() + vector.get_x());
      sum_vect.set_y(sum_vect.get_y() + vector.get_y());
      sum_vect.set_timeStamp(sum_vect.get_timeStamp() + vector.get_timeStamp());
      sum_vect.set_position(sum_vect.get_position() + vector.get_position());
      sum_vect.set_azimut(sum_vect.get_azimut() + vector.get_azimut());
      sum_vect.set_altitude(sum_vect.get_altitude() + vector.get_altitude());
      sum_vect.set_pression(sum_vect.get_pression() + vector.get_pression());
    }

    // divide sum_vect by n
    sum_vect.set_x(sum_vect.get_x() / n);
    sum_vect.set_y(sum_vect.get_y() / n);
    sum_vect.set_timeStamp(sum_vect.get_timeStamp() / n);
    sum_vect.set_position(sum_vect.get_position() / n);
    sum_vect.set_azimut(sum_vect.get_azimut() / n);
    sum_vect.set_altitude(sum_vect.get_altitude() / n);
    sum_vect.set_pression(sum_vect.get_pression() / n);

    // add sum_vect to the list
    sum_vects.push_back(sum_vect);
  }

  // create model signature from list of vectors
  ref_sign_ = new Sign(sum_vects, id);
}

Model::~Model()
{
  delete(ref_sign_);
  delete(signatures_);
}

// getters

Sign*
Model::get_ref_sign() const
{
  return ref_sign_;
}

list<Sign*>
Model::get_signatures() const
{
  return signatures_;
}

// setters

void
Model::set_ref_sign(Sign* s)
{
  ref_sign_ = s;
}

void
Model::set_signatures(list<Sign*> signatures)
{
  signatures_ = signatures;
}
