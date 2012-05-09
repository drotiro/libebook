/* 
 * mobiinfo - display mobi file info
 * (author, title, etc.)
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "MobiBook.h"
#include "Epub.h"
#include "Locale.h"
#include <iostream>

using std::string; 
using std::cerr;

/*
 * 
 */
int main(int argc, char** argv) {
    if(argc == 2) {
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

	std::cout << "Title:\t\t" << m->getTitle() << std::endl;
	std::cout << "Author:\t\t" << m->getAuthor() << std::endl;
	std::cout << "Publisher:\t" << m->getPublisher() << std::endl;
	/*
	std::cout << "Language:\t" << Locale::getName(m->getLocale()) << std::endl;
	std::cout << "Length:\t\t" << m->getTextSize() << std::endl;
	std::cout << "Images:\t\t" << m->imagesCount << std::endl;
	*/
	delete m;
	return 0;
    }

    //no args
    cerr << "Usage: " << argv[0] << " <mobifile>" << std::endl;
    return 1;
}

