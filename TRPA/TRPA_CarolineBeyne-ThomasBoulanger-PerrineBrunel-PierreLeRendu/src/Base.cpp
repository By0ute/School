#include "Base.hh"

Base::Base()
    : models_ ()
{
}

Base::Base(set<Model*> m)
    : models_ (m)
{
}

Base::~Base()
{
}

set<Model*>
Base::get_models() const
{
    return models_;
}

void
Base::set_models(set<Model*> m)
{
    models_ = m;
}

void
Base::add_model(Model* m)
{
   models_.insert(m);
}
