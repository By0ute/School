#ifndef PARSEUR_HH
# define PARSEUR_HH

# include "Sign.hh"
# include <list>
# include <fstream>
# include <string>
# include <stdlib.h>

using namespace std;

/// ------ Main App -----------

/// Parse the input file which associate identity to file
/// return a list of Signature obtains with the function parseFile
/// The File contains the following information
/// <id1> <File1>
/// <id2> <File2> <File3> ...
list<Sign*>  parse(string filename);

/// Parse a signature file and create a signature with id
/// The file contains the following informations
/// x-coord y-coord Timestamp ButtonStatus Azimuth Altitude Pressure
Sign*	parseFile(string filename, string user);

/// ------ Main Trt -----------

/// Parse a treatement file
/// This file contains the following information
/// <file test> <id>
/// ...
void	parseTrt(string filename);

#endif
