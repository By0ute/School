#ifndef BARCODETRT_HH
# define BARCODETRT_HH

# include <opencv2/core/core.hpp>
# include <cv.h>
# include <opencv2/highgui/highgui.hpp>

# include <iostream>
# include <vector>
# include <list>
# include "TabInt.hh"

using namespace cv;
using namespace std;

// whole treatment of barCode
vector<int>	barCodeTrt(Mat &barCode);

// Setup Left vect digit
void	set_VectLDigit(vector<TabInt> &vectLeft);

// Setup Right vect digit
void	set_VectRDigit(vector<TabInt> &vectRight);

// Detect start guard in barcode and set the min_width of a bar
int	detect_lguard(Mat& barCode, int x, int &y);

// Detect end guard
void	detect_rguard(Mat& barCode, int x, int &y, int min_width);

// Detect mid guard
void	detect_midguard(Mat& barCode, int x, int &y, int min_width);

// Detect Digit
int	read_digit(Mat& barCode, int x, int &y, int min_width,
		   vector<TabInt> vectDigit);

#endif
