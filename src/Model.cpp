#include "Model.hh"

Model::Model(list<Sign> signatures)
  : ref_sign_(nullptr)
  , signatures_(signatures)
{
	// FIXME: create model
}

Model::~Model()
{
	delete(ref_sign_);
	delete(signatures_);
}

// getters

Sign
Model::get_ref_sign() const
{
	return ref_sign_;
}

list<Sign>
Model::get_signatures() const
{
	return signatures_;
}

// setters

void
Model::set_ref_sign(Sign s)
{
	ref_sign_ = s;
}

void
Model::set_signatures(list<Sign> signatures)
{
	signatures_ = signatures;
}