#ifndef TABINT_HH
# define TABINT_HH

class TabInt
{
    public:
	TabInt();
	TabInt(int d0, int d1, int d2, int d3, int d4, int d5,
	       int d6, int d);

	~TabInt() {};

	int digit0;
	int digit1;
	int digit2;
	int digit3;
	int digit4;
	int digit5;
	int digit6;
	int digit;
};

int operator==(TabInt const& t1, TabInt const& t2);

inline int operator==(TabInt const& t1, TabInt const& t2)
{
    if ((t1.digit0 == t2.digit0) &&
        (t1.digit1 == t2.digit1) &&
        (t1.digit2 == t2.digit2) &&
        (t1.digit3 == t2.digit3) &&
        (t1.digit4 == t2.digit4) &&
        (t1.digit5 == t2.digit5) &&
        (t1.digit6 == t2.digit6))
	return t1.digit;
    return -1;
}

#endif
