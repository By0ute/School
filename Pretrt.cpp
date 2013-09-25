#include "Pretrt.hh"

namespace Pretrt
{
    // Change the image in color to gray
    Mat color2Gray (Mat& in)
    {
	Mat res;

	cvtColor(in, res, CV_BGR2GRAY);

	return res;
    }

    // Top Hat transformation
    Mat blackHat (Mat& in)
    {
	Mat res;
	Mat src = color2Gray(in);

	Mat element = getStructuringElement(MORPH_RECT,
					    Size(25,25), Point(-1,-1));

	morphologyEx(src, res, MORPH_BLACKHAT, element);

	return res;
    }

    Mat binarize (Mat& in)
    {
	Mat res;
	Mat src = blackHat(in);

	threshold(src, res, 50, 255, THRESH_BINARY);

	return res;
    }
}
