#ifndef MODEL_HH
# define MODEL_HH

# include <string>
# include <list>
# include <vector>
# include "Sign.hh"

using namespace std;

typedef string id_type;

class Model
{
  public:
    Model(id_type id, list<Sign*> signatures);
    ~Model();

    // getters
    Sign* get_ref_sign() const;
    list<Sign*> get_signatures() const;

    // setters
    void set_ref_sign(Sign* s);
    void set_signatures(list<Sign*> signatures);

  private:
    id_type id_;
    Sign* ref_sign_;
    list<Sign*> signatures_;
};

#endif //MODEL_HH
