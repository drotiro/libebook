/* 
 * Epub 
 * Support for epub ebooks
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#ifndef EPUB_H
#define	EPUB_H

#include "Ebook.h"
#include "Zip.h"
#include <vector>
#include <string>

class Epub : public Ebook {
public:
    static Epub *	createFromFile(const char *fileName);
    Dumper *		getDumper(const char * outdir);
    virtual ~Epub();

private:
    Epub() {};
    bool check();
    Zip * zf;
    std::vector<std::string> items, resources;
    std::string base;
};

#endif	/* EPUB_H */

