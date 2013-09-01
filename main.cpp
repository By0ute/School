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

    Mat in;
    in = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);

    if (!in.data)
    {
	cerr << "Cannot open or find image " << argv[1] << endl;
	return EXIT_FAILURE;
    }

    Mat out = binarize(blackHat(color2Gray(in)));
    //Mat out = blackHat(color2Gray(in));
    Trt trt(out);
    //trt.axes_bounding();
    //Mat res = trt.get_mat();
    //Mat res = trt.contours_bar();
    //trt.find_friends();
    Mat res = trt.find_friends();

    //trt.print_contours();

    namedWindow(name_in, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(name_in, 100, 100);
    imshow(name_in, in);

    namedWindow(name_out, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(name_out, 450, 100);
    imshow(name_out, out);

    namedWindow(name_trt, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(name_trt, 800, 100);
    imshow(name_trt, res);

    waitKey(0);


    destroyWindow(name_in);
    destroyWindow(name_out);
    destroyWindow(name_trt);

    return EXIT_SUCCESS;
}
