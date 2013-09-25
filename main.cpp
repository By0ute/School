#include "main.hh"

using namespace cv;
using namespace std;
using namespace Pretrt;

int
main (int argc,
      char** argv)
{
    if (argc != 2)
    {
	cerr << "USAGE : [TirfBarCode] [picture.extension]" << endl;
	return EXIT_FAILURE;
    }

    const char name_in[] = "Source Picture";
    const char name_out[] = "Pretrt Picture";
    const char name_trt[] = "Trt Picture";
    const char name_test[] = "Test Cropped";

    Mat in;
    in = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);

    if (!in.data)
    {
	cerr << "Cannot open or find image " << argv[1] << endl;
	return EXIT_FAILURE;
    }

    Mat out = binarize(in);
    Trt trt(out);

    Mat clone = in.clone();
    Mat test;
    Mat res = trt.print_results(clone, test);

    namedWindow(name_in, CV_WINDOW_NORMAL);
    cvMoveWindow(name_in, 100, 100);
    imshow(name_in, in);

    namedWindow(name_out, CV_WINDOW_NORMAL);
    cvMoveWindow(name_out, 450, 100);
    imshow(name_out, out);

    namedWindow(name_trt, CV_WINDOW_NORMAL);
    cvMoveWindow(name_trt, 800, 100);
    imshow(name_trt, res);

    namedWindow(name_test, CV_WINDOW_NORMAL);
    cvMoveWindow(name_test, 100, 300);
    imshow(name_test, test);


    waitKey(0);


    destroyWindow(name_in);
    destroyWindow(name_out);
    destroyWindow(name_trt);
    destroyWindow(name_test);

    return EXIT_SUCCESS;
}
