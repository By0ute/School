#include "Model.hh"

Model::Model(id_type id, Signatures& signatures)
    : id_ (id)
    , ref_sign_ (id)
    , signatures_ (signatures)
{
    int model_size = NORMA_SIZE; // should be 25
    int nb_signatures = signatures.size(); // should be 4 or 8

    if (nb_signatures == 0)
	return;
    else if (nb_signatures == 1)
    {
        ref_sign_ = Sign((*signatures.begin())->get_datas(), id);
	return;
    }

    list<VecParam> sum_vects;
    for (int j = 0; j < model_size; ++j) // foreach vector
    {
	VecParam sum_vect;

	Signatures::iterator it_sign = signatures.begin();
	if (it_sign != signatures.end())
	{
	    list<VecParam> vectors = (*it_sign)->get_datas();
	    list<VecParam>::iterator it_vect = vectors.begin();
	    advance(it_vect, j);
	    sum_vect = (*it_vect);

	    it_sign++;
	}
	for (; it_sign != signatures.end(); ++it_sign) // foreach signature
	{
	    list<VecParam> vectors = (*it_sign)->get_datas();
	    list<VecParam>::iterator it_vect = vectors.begin();
	    advance(it_vect, j);
	    VecParam vector = (*it_vect);

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
	sum_vect.set_x(sum_vect.get_x() / nb_signatures);
	sum_vect.set_y(sum_vect.get_y() / nb_signatures);
	sum_vect.set_timeStamp(sum_vect.get_timeStamp() / nb_signatures);
	sum_vect.set_position(sum_vect.get_position() / nb_signatures);
	sum_vect.set_azimut(sum_vect.get_azimut() / nb_signatures);
	sum_vect.set_altitude(sum_vect.get_altitude() / nb_signatures);
	sum_vect.set_pression(sum_vect.get_pression() / nb_signatures);

	// add sum_vect to the list
	sum_vects.push_back(sum_vect);
    }

    /* WARNING: ONLY CONSIDERS SOME PARAMETERS
    list<VecParam>::iterator it_vect;
    for (it_vect = sum_vects.begin(); it_vect != sum_vects.end(); ++it_vect)
    {
      (*it_vect).set_position(1);
      (*it_vect).set_azimut(0);
      (*it_vect).set_altitude(0);
    }
    //*/

    // create model signature from list of vectors
    ref_sign_ = Sign(sum_vects, id);
}

bool Model::operator==(const Model& other)
{
    return ((other.get_id() == id_) && (other.get_ref_sign() == ref_sign_));
}
