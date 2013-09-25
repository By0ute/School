#include "Pretrt.hh"

namespace Pretrt
{
    // Change the image in color to gray
    Mat color2Gray (Mat in)
    {
	Mat res;

	cvtColor(in, res, CV_BGR2GRAY);

	//equalizeHist(in, res);

	//for (int i = 0; i < in.cols; i++)
	//{
	    //for (int j = 0; j < in.rows; j++)
	    //{
		//Vec3b intensity = in.at<Vec3b>(j,i);

		//uchar b = intensity.val[0];
		//uchar g = intensity.val[1];
		//uchar r = intensity.val[2];

		//uchar color = 0.114*b + 0.587*g + 0.299*r;

		//res.at<Vec3b>(j,i) = Vec3b(color, color, color);
	    //}
	//}

	return res;
    }

    // Top Hat transformation
    Mat blackHat (Mat in)
    {
	Mat res;

	Mat element = getStructuringElement(MORPH_RECT,
					    Size(25,25), Point(-1,-1));

	morphologyEx(in, res, MORPH_BLACKHAT, element);

	return res;
    }

    Mat binarize (Mat in)
    {
	Mat res;

	threshold(in, res, 50, 255, THRESH_BINARY);

	return res;
    }
}
