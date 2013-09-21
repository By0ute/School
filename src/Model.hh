#ifndef MODEL_HH
# define MODEL_HH

# include <string>
# include <list>
# include "Sign.hh"

using namespace std;

typedef string id_type;
typedef list<Sign*> Signatures;

class Model
{
  public:
    // constructors
	Model(id_type id, Signatures& signatures);

    // getters
    const id_type& get_id() const { return id_; }
    const Sign& get_ref_sign() const { return ref_sign_; }
    const Signatures& get_signatures() const { return signatures_; }

    // operators
    bool operator==(const Model& other);

  private:
    // deleted default methods
    Model();
    Model(const Model&);
    Model& operator=(const Model&);

  private:
    // attributes
    id_type id_; // identity of the user
    Sign ref_sign_; // the model
    Signatures signatures_; // the list of training signatures
};

#endif //MODEL_HH
