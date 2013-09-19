#ifndef MODEL_HH
# define MODEL_HH

# include <string>
# include <list>
# include "Sign.hh"

# define MODEL_SIZE 25

using namespace std;

typedef string id_type;

class Model
{
  public:
    // constructors
    Model(id_type id, list<Sign*> signatures);

    // getters
    const id_type& get_id() const { return id_; }
    const Sign& get_ref_sign() const { return ref_sign_; }
    const list<Sign*>& get_signatures() const { return signatures_; }

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
    list<Sign*> signatures_; // the list of training signatures
};

#endif //MODEL_HH
