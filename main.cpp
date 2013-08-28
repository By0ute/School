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
    const char name_out[] = "Output Picture";

    Mat in;
    in = imread(argv[1], CV_LOAD_IMAGE_UNCHANGED);

    if (!in.data)
    {
	cerr << "Cannot open or find image " << argv[1] << endl;
	return EXIT_FAILURE;
    }

    Mat out = binarize(blackHat(color2Gray(in)));
    //Mat out = blackHat(color2Gray(in));

    namedWindow(name_in, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(name_in, 100, 100);
    imshow(name_in, in);

    namedWindow(name_out, CV_WINDOW_AUTOSIZE);
    cvMoveWindow(name_out, 800, 100);
    imshow(name_out, out);

    waitKey(0);


    destroyWindow(name_in);
    destroyWindow(name_out);

    return EXIT_SUCCESS;
}
