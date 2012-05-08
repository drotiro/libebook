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

class Epub : public Ebook {
public:
    static Epub *	createFromFile(const char *fileName);
    Dumper *		getDumper(const char * outdir);
    virtual ~Epub();

private:
    Epub() {};
    bool check();
    Zip * zf;


};

#endif	/* EPUB_H */

