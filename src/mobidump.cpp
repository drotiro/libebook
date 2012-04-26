/* 
 * mobidump - dump the contents of a .mobi file
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "MobiDoc.h"
#include "MobiDumper.h"
#include <iostream>

using std::string; 
using std::cerr;
using std::vector;

/*
 * 
 */
int main(int argc, char** argv) {
    if(argc == 3) {
	MobiDoc * m = MobiDoc::CreateFromFile(argv[1]);
	if(m==NULL) {
	    cerr << "Unable to open file " << argv[1] << std::endl;
	    return 1;
	}

	MobiDumper h = MobiDumper(m, argv[2]);
	h.dumpImages();
	h.dumpText();
	h.dumpMetadata();
	
	delete m;
	return 0;
    }

    //no args
    cerr << "Usage: " << argv[0] << " <mobifile> <outdir>" << std::endl;
    return 1;
}

