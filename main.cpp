#include <opencv2/core/core.hpp>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int
main (int argc,
      char** argv)
{
    if (argc != 2)
    {
	cerr << "USAGE : [TirfZipCode] [picture.extension]" << endl;
	return -1;
    }

    Mat in;
    Mat out;
    in = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);
    out = in;

    if (!in.data)
    {
	cerr << "Cannot open or find image " << argv[1] << endl;
	return -1;
    }

    cvtColor(in, out, CV_BGR2GRAY);
    imwrite("out.jpg", out);

    namedWindow("Source Picture", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Source Picture", 100, 100);
    imshow("Source Picture", in);

    namedWindow("Output Picture", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Output Picture", 800, 100);
    imshow("Output Picture", out);

    waitKey(0);

    destroyWindow("Source Picture");
    destroyWindow("Output Picture");

    return EXIT_SUCCESS;
}
