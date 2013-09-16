#include "Parseur.hh"

list<Sign*>  parse(string filename)
{
    list<Sign*> listSign;
    string line;
    ifstream file(filename);

    if (file)
    {
	while (getline(file, line))
	{
	    string username;
	    size_t j = 0;
	    int i = 0;
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
			    << " error" <<endl;
		    else
			listSign.push_back(sign);
		}
		i++;
		line = line.substr(j + 1);
	    }
	    Sign* sign = parseFile(line, username);
	    if (sign == NULL)
		cerr << "File " << line
		    << " error" <<endl;
	    else
		listSign.push_back(sign);
	}
	file.close();
    }

    return listSign;
}

Sign*	parseFile(string filename, string user)
{
    list<VecParam> listVP;
    string line;
    ifstream file (filename);
    Sign *signature = NULL;

    if (file)
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

void	parseTrt(string filename)
{
    ifstream file(filename);
    string line;

    if (file)
    {
	while (getline(file, line))
	{
	    size_t j = line.find(' ');
	    string filename;
	    string username;
	    if (j == string::npos)
		cerr << filename << ": Wrong format" << endl;
	    else
	    {
		filename = line.substr(0, j);
		username = line.substr(j);
	    }
	}
	file.close();
    }
}
