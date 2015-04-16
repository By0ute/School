#ifndef AXE_HH
# define AXE_HH

# include <opencv2/core/core.hpp>
# include <cv.h>
# include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Axe
{
    public:
	Axe();
	Axe(Point pt1, Point pt2);
	Axe(int x1, int y1, int x2, int y2);

	~Axe();

    public:
	Point p1_;
	Point p2_;
};

bool operator==(Axe const& a1, Axe const& a2);

bool operator<(Axe const& a1, Axe const& a2);

inline bool operator==(Axe const& a1, Axe const& a2)
{
    return ((a1.p1_.x == a2.p1_.x) && (a1.p1_.y == a2.p1_.y) &&
	    (a1.p2_.x == a2.p2_.x) && (a1.p2_.y == a2.p2_.y));
}

inline bool operator<(Axe const& a1, Axe const& a2)
{
    int r1 = a1.p1_.x + a1.p1_.y + a1.p2_.x + a1.p2_.y;
    int r2 = a2.p1_.x + a2.p1_.y + a2.p2_.x + a2.p2_.y;
    //return ((a1.p1_.x < a2.p1_.x) &&// (a1.p1_.y == a2.p1_.y) &&
    //(a1.p2_.x < a2.p2_.x));// && (a1.p2_.y == a2.p2_.y));
    return (r1 < r2);
}

#endif // AXE_HH
