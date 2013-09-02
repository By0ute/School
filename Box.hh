#ifndef BOX_HH
# define BOX_HH

# include <opencv2/core/core.hpp>
# include <cv.h>
# include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Box
{
    public:
	Box();
	Box(Point pt1, Point pt2, Point pt3, Point pt4);
	Box(int x1, int y1, int x2, int y2,
	    int x3, int y3, int x4, int y4);

	~Box();
    public:
	Point p1_;
	Point p2_;
	Point p3_;
	Point p4_;
};

#endif // BOX_HH
