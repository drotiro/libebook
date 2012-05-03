/* 
 * mobiinfo - display mobi file info
 * (author, title, etc.)
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "MobiDoc.h"
#include "Locale.h"
#include <iostream>

using std::string; 
using std::cerr;

/*
 * 
 */
int main(int argc, char** argv) {
    if(argc == 2) {
	MobiDoc * m = MobiDoc::createFromFile(argv[1]);
	if(m==NULL) {
	    cerr << "Unable to open file " << argv[1] << std::endl;
	    return 1;
	}

	std::cout << "Title:\t\t" << m->getTitle() << std::endl;
	std::cout << "Author:\t\t" << m->getAuthor() << std::endl;
	std::cout << "Publisher:\t" << m->getPublisher() << std::endl;
	std::cout << "Language:\t" << Locale::getName(m->getLocale()) << std::endl;
	std::cout << "Length:\t\t" << m->getTextSize() << std::endl;
	std::cout << "Images:\t\t" << m->imagesCount << std::endl;

	delete m;
	return 0;
    }

    //no args
    cerr << "Usage: " << argv[0] << " <mobifile>" << std::endl;
    return 1;
}

