#ifndef MODEL_HH
# define MODEL_HH

# include <list>
# include "Model.hh"

using namespace std;

class Model
{
    public:
	Model(list<Sign> signatures);
	~Model();
	
	// getters
	Sign get_ref_sign() const;
	list<Sign> get_signatures() const;

	// setters
	void set_ref_sign(Sign s);
	void set_signatures(list<Sign> signatures);

    private:
	Sign* ref_sign_;
	list<Sign*> signatures_;
};

#endif //MODEL_HH
