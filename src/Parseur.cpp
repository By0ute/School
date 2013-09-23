#include "Parseur.hh"

/**
 * PARSE
 */
list<Sign*>  parse (string filename)
{
    list<Sign*> listSign;
    string line;
    ifstream file(filename.c_str());

    if (file)
    {
	while (getline(file, line))
	{
	    string username;
	    size_t j = 0;
	    int i = 0;
	    if (line == "")
		continue;
	    while ((j = line.find(' ')) != string::npos)
	    {
		// set username
		if (i == 0)
		    username = line.substr(0, j);
		else
		{
		    string tempFileName = line.substr(0, j);
		    Sign* sign = parseFile(tempFileName, username);
		    if (sign == NULL)
			cerr << "File " << tempFileName
			    << " signature error" <<endl;
		    else
			listSign.push_back(sign);
		}
		i++;
		line = line.substr(j + 1);
	    }
	    Sign* sign = parseFile(line, username);
	    if (sign == NULL)
		cerr << "File " << line
		    << " signature error" <<endl;
	    else
		listSign.push_back(sign);
	}
	file.close();
    }
    else
    {
	cerr << "File " << filename << " not found" << endl;
    }

    return listSign;
}

/**
 * PARSEFILE
 */
Sign*	parseFile (string filename, string user)
{
    list<VecParam> listVP;
    string line;
    ifstream file (filename.c_str());
    Sign *signature = NULL;

    cout << filename << endl;

    if (!file.is_open())
    {
	cout << "File " << filename << " not found" << endl;
	return signature;
    }
    else
    {
	// skip the first line
	// because contains number of points of the signature
	getline(file, line);
	while (getline(file, line))
	{
	    int i = 0;
	    size_t j = 0;
	    string tab[6];
	    while ((j = line.find(' ')) != string::npos)
	    {
		tab[i] = line.substr(0, j);
		line = line.substr(j + 1);
		i++;
	    }
	    int x = atoi(tab[0].c_str());
	    int y = atoi(tab[1].c_str());
	    int t = atoi(tab[2].c_str());
	    int po = atoi(tab[3].c_str());
	    int a = atoi(tab[4].c_str());
	    int alt = atoi(tab[5].c_str());
	    int pr = atoi(line.c_str());
	    VecParam param(x, y, t, po, a, alt, pr);
	    listVP.push_back(param);
	}
	signature = new Sign(listVP, user);
	file.close();
    }
    return signature;
}

/**
 * PARSETRT*
 */
TestObj*  parseTrt (string filename)
{
    TestObj *testingObj = NULL;
    list<tuple<Sign*, string, string> > tests;
    string line;
    ifstream file(filename);

    if (file)
    {
	while (getline(file, line))
	{
	    int j = 0;
	    if (line == "")
		continue;
	    if ((j = line.find(' ')) != string::npos)
	    {
		string tempFileName = line.substr(0, j);
		Sign* sign = parseFile(tempFileName, "");
		if (sign == NULL)
		{
		    cerr << "File " << line << " error" << endl;
		    continue;
		}
		tests.push_back(make_tuple(sign, line.substr(j + 1),
					   tempFileName));
	    }
	    else
		cerr << "File " << line
		    << " error" << endl;
	}
	file.close();
	testingObj = new TestObj(tests);
    }
    else
    {
	cout << "File " << filename << " not found" << endl;
    }

    return testingObj;
}


/**
 * WRITEFINALFILE
 */
void	writeFinalFile (string filetest, string id, int score, char decision)
{
    ofstream file;

    file.open("score.txt", std::ios_base::app);
    file << filetest << " " <<
	    id << " " <<
	    score << " " << decision << endl;
    file.close();

}
