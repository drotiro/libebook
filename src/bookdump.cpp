/* 
 * mobidump - dump the contents of a .mobi file
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "MobiBook.h"
#include "MobiDumper.h"
#include "Epub.h"
#include <iostream>
#include <string>

using std::string; 
using std::cerr;
using std::vector;

/*
 * Dump ebook content in a directory
 * 1st arg is ebook path
 * 2nd arg is output dir
 */
int main(int argc, char** argv) {
    if(argc == 3) {
	Ebook * m = NULL;
	string file = argv[1];

	if(file.find(".mobi",file.length()-5, 5) != string::npos)
	    m = (Ebook*) MobiBook::createFromFile(argv[1]);
	else if(file.find(".epub",file.length()-5, 5) != string::npos)
	    m = (Ebook*) Epub::createFromFile(argv[1]);

	if(m==NULL) {
	    cerr << "Unable to open ebook " << file << std::endl;
	    return 1;
	}

	Dumper * h = m->getDumper(argv[2]);
	h->dump();

	delete h;
	delete m;
	return 0;
    }

    //bad args
    cerr << "Usage: " << argv[0] << " <ebook> <outdir>" << std::endl;
    return 1;
}
