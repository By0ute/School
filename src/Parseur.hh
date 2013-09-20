#ifndef PARSEUR_HH
# define PARSEUR_HH

# include "Sign.hh"
# include <list>
# include <fstream>
# include <string>
# include <stdlib.h>
# include "TestObj.hh"

using namespace std;

/** ------ Main App ----------- */

/**
 * Parses the input file which associate identity to file
 * returns a list of Signature obtained with the function parseFile
 * The File contains the following informations
 * <id1> <File1>
 * <id2> <File2> <File3> ...
 */
    list<Sign*> parse(string filename);

/**
 * Parses a signature file and creates a signature with id
 * The file contains the following informations
 * x-coord y-coord Timestamp ButtonStatus Azimuth Altitude Pressure
 */
    Sign* parseFile(string filename, string user);

/** ------ Main Trt ----------- */

/**
 * Parses a treatement file
 * This file contains the following informations
 * <file test> <id>
 * ...
 */
    TestObj* parseTrt(string filename);

/**
 * Writes final decision in score.txt
 * <file> <id> <score <decision: t/f>
 */
    void writeFinalFile(string filename);

#endif
