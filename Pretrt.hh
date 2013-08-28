#ifndef PRETRT_HH
# define PRETRT_HH

# include <opencv2/core/core.hpp>
# include <cv.h>
# include <opencv2/highgui/highgui.hpp>

# include <iostream>
# include <string>

using namespace cv;

namespace Pretrt
{
	    Mat color2Gray(Mat in);
	    Mat blackHat(Mat in);
	    //Mat blackHat2(Mat in);
	    Mat binarize(Mat in);

}

#endif //PRETRT_HH
