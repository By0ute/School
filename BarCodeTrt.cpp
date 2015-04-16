#include "BarCodeTrt.hh"


vector<int>   barCodeTrt(Mat &barCode)
{
    int min_width = 0;
    int min_lwidth = 0;
    int min_rwidth = 0;
    int x = barCode.rows / 3;
    int y = 0;

    vector<TabInt> vect_left;
    vector<TabInt> vect_right;

    // Set Vect of all the digit a barcode can have
    // Right and Left
    set_VectLDigit(vect_left);
    set_VectRDigit(vect_right);

    // skip white space
    while (x < barCode.rows)
    {
	while (y < barCode.cols && barCode.at<uchar>(x, y) != 255)
	    y++;
	if (y != barCode.cols)
	    break;
	x++;
	y = 0;
    }

    // Detect Start guard
    min_lwidth = detect_lguard(barCode, x, y);
    min_rwidth = detect_rguard(barCode);

    min_width = (min_lwidth + min_rwidth) / 2;

    vector<int> digitsVect;

    // Detect 6 left digits
    for (int i = 0; i < 6; i++)
	digitsVect.push_back(read_digit(barCode, x, y, min_width,
					vect_left));

    // Detect midguard
    detect_midguard(barCode, x, y, min_width);

    // Detect 6 right digits
    for (int i = 0; i < 6; i++)
	digitsVect.push_back(read_digit(barCode, x, y, min_width,
					vect_right));

    return digitsVect;
}

int	detect_lguard(Mat &barCode, int x, int &y)
{
    int guard[3] = {255, 0, 255};
    int width[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++)
    {
	while (y < barCode.cols &&
	       barCode.at<uchar>(x, y) == guard[i])
	{
	    // compute the minimum width of a bar
	    width[i]++;
	    y++;
	}
    }
    int min_width = (width[0] + width[1] + width[2]) / 3;
    if (min_width == 0)
	cout << "Probleme de detection" << endl;
    return min_width;
}

void	detect_midguard(Mat &barCode, int x, int &y, int min_width)
{
    int guard[5] = {0, 255, 0, 255, 0};
    for (int i = 0; i < 5; i++)
    {
	while (y < barCode.cols &&
	       barCode.at<uchar>(x, y) == guard[i])
	    y += min_width;
    }
}

int	detect_rguard(Mat &barCode)
{
    int x = barCode.rows / 3;
    int y = barCode.cols;

    // skip white space
    while (x < barCode.rows)
    {
	while (y > 0 && barCode.at<uchar>(x, y) != 255)
	    y--;
	if (y != barCode.cols)
	    break;
	x++;
	y = barCode.cols;
    }

    int guard[3] = {255, 0, 255};
    int width[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++)
    {
	while (y > 0 && barCode.at<uchar>(x, y) == guard[i])
	{
	    // compute the minimum width of a bar
	    width[i]++;
	    y--;
	}
    }
    int min_width = (width[0] + width[1] + width[2]) / 3;
    if (min_width == 0)
	cout << "Probleme de detection" << endl;
    return min_width;
}

void	set_VectLDigit(vector<TabInt> &vectLeft)
{
    TabInt d0(0,0,0,255,255,0,255,0);
    TabInt d1(0,0,255,255,0,0,255,1);
    TabInt d2(0,0,255,0,0,255,255,2);
    TabInt d3(0,255,255,255,255,0,255,3);
    TabInt d4(0,255,0,0,0,255,255,4);
    TabInt d5(0,255,255,0,0,0,255,5);
    TabInt d6(0,255,0,255,255,255,255,6);
    TabInt d7(0,255,255,255,0,255,255,7);
    TabInt d8(0,255,255,0,255,255,255,8);
    TabInt d9(0,0,0,255,0,255,255,9);
    vectLeft.push_back(d0);
    vectLeft.push_back(d1);
    vectLeft.push_back(d2);
    vectLeft.push_back(d3);
    vectLeft.push_back(d4);
    vectLeft.push_back(d5);
    vectLeft.push_back(d6);
    vectLeft.push_back(d7);
    vectLeft.push_back(d8);
    vectLeft.push_back(d9);
}

void	set_VectRDigit(vector<TabInt> &vectRight)
{
    TabInt d0(255,255,255,0,0,255,0,0);
    TabInt d1(255,255,0,0,255,255,0,1);
    TabInt d2(255,255,0,255,255,0,0,2);
    TabInt d3(255,0,0,0,0,255,0,3);
    TabInt d4(255,0,255,255,255,0,0,4);
    TabInt d5(255,0,0,255,255,255,0,5);
    TabInt d6(255,0,255,0,0,0,0,6);
    TabInt d7(255,0,0,0,255,0,0,7);
    TabInt d8(255,0,0,255,0,0,0,8);
    TabInt d9(255,255,255,0,255,0,0,9);
    vectRight.push_back(d0);
    vectRight.push_back(d1);
    vectRight.push_back(d2);
    vectRight.push_back(d3);
    vectRight.push_back(d4);
    vectRight.push_back(d5);
    vectRight.push_back(d6);
    vectRight.push_back(d7);
    vectRight.push_back(d8);
    vectRight.push_back(d9);
}

void	align(Mat &barCode, int x, int& y, int first_color,
		   int last_color)
{
    if (barCode.at<uchar>(x, y) == last_color)
    {
	while (barCode.at<uchar>(x, y) == last_color)
	    y++;
    }
    else
    {
	while (barCode.at<uchar>(x, y - 1) == first_color)
	    y --;
    }
}

int	read_digit(Mat& barCode, int x, int &y, int min_width,
		   vector<TabInt> vectDigit)
{
    int digit = -1;
    // Get the digit from the Mat
    int test[7] = {0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 7; i++)
    {
	for (int j = 0; j < min_width; j++)
	{
	    if (barCode.at<uchar>(x, y) == 255)
		test[i]++;
	    y++;
	}
	// re align the last pixel if the result
	// is under the average and it's a bar
	// or if it's > of the average avec it's a space
	if (test[i] == 1 && barCode.at<uchar>(x, y) == 255 ||
	    test[i] == min_width - 1 && barCode.at<uchar>(x, y) == 0)
	    y --;
    }

//    for (int i = 0; i < 7; i++)
//	cout << test[i] << " ";
//    cout << endl;

    // Put the right value to compare with the digit
    // with the average of the min_width
    int average = min_width / 2;
    for (int i = 0; i < 7; i++)
    {
	if (test[i] > average)
	    test[i] = 255;
	else
	    test[i] = 0;
    }

    // on est a gauche
    if (test[0] == 0)
	align(barCode, x, y, 0, 255);
    else
	align(barCode, x, y, 255, 0);

//    for (int i = 0; i < 7; i++)
//	cout << test[i] << " ";
//    cout << endl;

    TabInt testTabInt(test [0], test[1], test[2], test[3],
		      test[4], test[5], test[6], -2);

    // Final Test to retrieve the digit
    for (unsigned int i = 0; i < vectDigit.size(); i++)
    {
	TabInt digitTest = vectDigit[i];
	if ((digit = (digitTest == testTabInt)) >= 0)
	    break;
    }
    // if we haven't recognize a digit it's a wrong barcode
    if (digit < 0)
	cerr << "Invalid Barcode" << endl;

    return digit;
}
