#include "BarCodeTrt.hh"

void	barCodeTrt(Mat &barCode)
{
    int min_width = 0;
    // skip white space
    int x = 0;
    int y = 0;

    vector<TabInt> map_left;
    vector<TabInt> map_right;

    set_MapLDigit(map_left);
    set_MapRDigit(map_right);

    while (y < barCode.cols && barCode.at<uchar>(x, y) != 255)
	y++;

    // Detect Start guard
    min_width = detect_lguard(barCode, x, y);

    vector<int> digitsList;

    // Detect 6 left digits
    for (int i = 0; i < 6; i++)
	digitsList.push_back(read_digit(barCode, x, y, min_width,
					map_left));

    // Detect midguard
    detect_midguard(barCode, x, y, min_width);

    // Detect 6 right digits
    for (int i = 0; i < 6; i++)
	digitsList.push_back(read_digit(barCode, x, y, min_width,
					map_right));

    //detect right guard
    detect_rguard(barCode, x, y, min_width);

    cout << "Result barcode :" << endl;
    for (auto digit : digitsList)
	std::cout << digit << " ";
   cout << endl;
}

int	detect_lguard(Mat &barCode, int x, int &y)
{
    int guard[3] = {255, 0, 255};
    int min_width = 0;
    for (int i = 0; i < 3; i++)
    {
	while (y < barCode.cols &&
	       barCode.at<uchar>(x, y) == guard[i])
	{
	    // compute the minimum width of a bar
	    if (i == 0)
	    {
	        min_width++;
		y++;
	    }
	    else
		y += min_width;
	}
    }
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

void	detect_rguard(Mat &barCode, int x, int &y, int min_width)
{
    int guard[3] = {255, 0, 255};
    for (int i = 0; i < 3; i++)
    {
	while (y < barCode.cols &&
	       barCode.at<uchar>(x, y) == guard[i])
	    y += min_width;
    }
}


void	set_MapLDigit(vector<TabInt> &mapLeft)
{
    TabInt d0(0,0,0,255,255,0,255);
    TabInt d1(0,0,255,255,0,0,255);
    TabInt d2(0,0,255,0,0,255,255);
    TabInt d3(0,255,255,255,255,0,255);
    TabInt d4(0,255,0,0,0,255,255);
    TabInt d5(0,255,255,0,0,0,255);
    TabInt d6(0,255,0,255,255,255,255);
    TabInt d7(0,255,255,255,0,255,255);
    TabInt d8(0,255,255,0,255,255,255);
    TabInt d9(0,0,0,255,0,255,255);
    mapLeft.push_back(d0);
    mapLeft.push_back(d1);
    mapLeft.push_back(d2);
    mapLeft.push_back(d3);
    mapLeft.push_back(d4);
    mapLeft.push_back(d5);
    mapLeft.push_back(d6);
    mapLeft.push_back(d7);
    mapLeft.push_back(d8);
    mapLeft.push_back(d9);
}

void	set_MapRDigit(vector<TabInt> &mapRight)
{
    TabInt d0(255,255,255,0,0,255,0);
    TabInt d1(255,255,0,0,255,255,0);
    TabInt d2(255,255,0,255,255,0,0);
    TabInt d3(255,0,0,0,0,255,0);
    TabInt d4(255,0,255,255,255,0,0);
    TabInt d5(255,0,0,255,255,255,0);
    TabInt d6(255,0,255,0,0,0,0);
    TabInt d7(255,0,0,0,255,0,0);
    TabInt d8(255,0,0,255,0,0,0);
    TabInt d9(255,255,255,0,255,0,0);
    mapRight.push_back(d0);
    mapRight.push_back(d1);
    mapRight.push_back(d2);
    mapRight.push_back(d3);
    mapRight.push_back(d4);
    mapRight.push_back(d5);
    mapRight.push_back(d6);
    mapRight.push_back(d7);
    mapRight.push_back(d8);
    mapRight.push_back(d9);
}

int	read_digit(Mat& barCode, int x, int &y, int min_width,
		   vector<TabInt> mapDigit)
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
    TabInt testTabInt(test [0], test[1], test[2], test[3],
		      test[4], test[5], test[6]);

    // Final Test to retrieve the digit
    for (unsigned int i = 0; i < mapDigit.size(); i++)
    {
	TabInt digitTest = mapDigit[i];
	if (digitTest == testTabInt)
	{
	    digit = i;
	    break;
	}
    }

    // if we haven't recognize a digit it's a wrong barcode
    if (digit == -1)
	cerr << "Invalid Barcode" << endl;

    return digit;
}
