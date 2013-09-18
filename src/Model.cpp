#include "Model.hh"

Model::Model(id_type id, list<Sign*> signatures)
  : id_(id)
  , ref_sign_(nullptr)
  , signatures_(signatures)
{
  int n = signatures_.size();
  int m = 25;
  int t = 5;

  ref_sign_ = new Sign(id);
  vector<VecParam> sum_vects(m);
  vector<bool> sum_vects_b(m, false);

  // sum vectors from all signatures
  int i = 0;
  list<Sign*>::iterator it_sign;
  for (; it_sign != signatures_.end(); ++it_sign) // foreach signature
  {
    Sign* sign = (*it_sign);

    int j = 0;
    list<VecParam> vectors = sign->get_datas();
    list<VecParam>::iterator it_vect;
    for (; it_vect != vectors.end(); ++it_vect) // foreach vector
    {
      VecParam vector = (*it_vect);

      if (sum_vects_b[j] == false)
	  {
	    sum_vects[j] = vector;
		sum_vects_b[j] = true;
	  }
      else
      {
	    sum_vects[j].set_x(sum_vects[j].get_x() + vector.get_x());
	    sum_vects[j].set_y(sum_vects[j].get_y() + vector.get_y());
	    sum_vects[j].set_timeStamp(sum_vects[j].get_timeStamp() + vector.get_timeStamp());
	    sum_vects[j].set_position(sum_vects[j].get_position() + vector.get_position());
	    sum_vects[j].set_azimut(sum_vects[j].get_azimut() + vector.get_azimut());
	    sum_vects[j].set_altitude(sum_vects[j].get_altitude() + vector.get_altitude());
	    sum_vects[j].set_pression(sum_vects[j].get_pression() + vector.get_pression());
      }

      ++j;
    }

    ++i;
  }

  // divide by n
  for (int j = 0; j < m; ++j)
  {
    VecParam moyen_j;
    moyen_j.set_x(sum_vects[j].get_x() / n);
    moyen_j.set_y(sum_vects[j].get_y() / n);
    moyen_j.set_timeStamp(sum_vects[j].get_timeStamp() / n);
    moyen_j.set_position(sum_vects[j].get_position() / n);
    moyen_j.set_azimut(sum_vects[j].get_azimut() / n);
    moyen_j.set_altitude(sum_vects[j].get_altitude() / n);
    moyen_j.set_pression(sum_vects[j].get_pression() / n);

    ref_sign_->add_data(moyen_j);
  }
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
