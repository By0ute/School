#ifndef MODEL_HH
# define MODEL_HH

# include <string>
# include <list>
# include <vector>
# include "Sign.hh"

# define MODEL_SIZE 25

using namespace std;

typedef string id_type;

class Model
{
    public:
	// constructors
	Model() = delete;
	Model(const Model&) = delete;
	Model(id_type id, list<Sign*> signatures);
	// destructors
	virtual ~Model() { delete(ref_sign_); }

	// getters
	const Sign* get_ref_sign() const { return ref_sign_; }
	const list<Sign*> get_signatures() const { return signatures_; }

	// operators
	Model& operator=(const Model&) = delete;
	Model& operator==(const Model&) = delete;

    private:
	id_type id_;
	Sign* ref_sign_;
	list<Sign*> signatures_;
};


#endif //MODEL_HH
