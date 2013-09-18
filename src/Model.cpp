#include "Model.hh"

Model::Model(id_type id, list<Sign*> signatures)
    : id_ (id),
    ref_sign_ (nullptr),
    signatures_ (signatures)
{
    //int n = signatures_.size();
    //int m = MODEL_SIZE; // should be 25
    ////int t = 5;

    //ref_sign_ = new Sign(id);
    //vector<VecParam> sum_vects(m);
    //vector<bool> sum_vects_b(m, false);

    //// sum vectors from all signatures
    //int i = 0;
    //list<Sign*>::iterator it_sign = signatures_.begin();

    //for (it_sign = signatures_.begin();
	 //it_sign != signatures_.end(); ++it_sign) // foreach signature
    //{
	//Sign* sign = (*it_sign);

	//int j = 0;
	//list<VecParam> vectors = sign->get_datas();
	//list<VecParam>::iterator it_vect;
	//for (; it_vect != vectors.end(); ++it_vect) // foreach vector
	//{
	    //VecParam vector = (*it_vect);

	    //if (sum_vects_b[j] == false)
	    //{
		//sum_vects[j] = vector;
		//sum_vects_b[j] = true;
	    //}
	    //else
	    //{
		//sum_vects[j].set_x(sum_vects[j].get_x() + vector.get_x());
		//sum_vects[j].set_y(sum_vects[j].get_y() + vector.get_y());
		//// ...
	    //}

	    //++j;
	//}

	//++i;
  int n = signatures_.size();
  int m = 25;

  list<VecParam> sum_vects;
  for (int j = 0; j < m; ++j) // foreach vector
  {
    VecParam sum_vect;

    list<Sign*>::iterator it_sign = signatures_.begin();
    if (it_sign != signatures_.end())
    {
      list<VecParam>::iterator it_vect = (*it_sign)->get_datas().begin();
      advance(it_vect, j);
      sum_vect = (*it_vect);

      it_sign++;
    }
    for (; it_sign != signatures_.end(); ++it_sign) // foreach signature
    {
      list<VecParam>::iterator it_vect = (*it_sign)->get_datas().begin();
      advance(it_vect, j);
      VecParam vector = (*it_vect);

      //<<<<<<< HEAD
    // divide by n
    for (int j = 0; j < m; ++j)
    {
	VecParam moyen_j;
	moyen_j.set_x(sum_vects[j].get_x() / n);
	moyen_j.set_y(sum_vects[j].get_y() / n);
	// ...

	ref_sign_->add_data(moyen_j);
    }
}

Model::~Model()
{
    //delete(ref_sign_);
    //delete(signatures_);
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
    //=======
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
  //>>>>>>> 65656986193ffa4fbbb8e4a74ffa0e974f890e73
}
