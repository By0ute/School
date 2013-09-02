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

#endif // AXE_HH
