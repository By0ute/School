#ifndef TRT_HH
# define TRT_HH

# include <opencv2/core/core.hpp>
# include <cv.h>
# include <opencv2/highgui/highgui.hpp>

# include <iostream>
# include <string>
# include <vector>

using namespace cv;
using namespace std;

class Trt
{
    public:
	    // constructor and co
	    Trt();
	    Trt(Mat m);
	    Trt(Mat m, std::vector<std::vector <Point> > c,
		std::vector<Vec4i> h);

	    ~Trt();

	    // Treatment methods
	    Mat contours_bouding();
	    Mat contours_bar();

	    // utils
	    void print_hierarchy();
	    void print_contours();

	    // getters setters
	    Mat get_mat();
	    std::vector<std::vector<Point> > get_contours();
	    std::vector<Vec4i> get_hierarchy();

	    void set_mat(Mat m);
	    void set_contours(std::vector<std::vector<Point> > c);
	    void set_hierarchy(std::vector<Vec4i> h);

    private:
	    Mat mat_;
	    std::vector<std::vector<Point> > contours_;
	    std::vector<Vec4i> hierarchy_;

};


bool four_points_bar(vector<Point> v);
bool two_points_bar(vector<Point> v);

#endif //TRT_HH
