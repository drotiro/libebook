/* 
 * Ebook 
 * Common interface for the variou formats
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include <string>
#ifndef EBOOK_H
#define	EBOOK_H

// forward decl
class Dumper;

class Ebook {
public:

    virtual ~Ebook() {};
    virtual std::string	getTitle() { return title; }
    virtual std::string	getAuthor() { return author; }
    virtual std::string	getPublisher() { return publisher; }
    virtual Dumper *	getDumper(const char * outdir) = 0;

protected:
    char *	fileName;
    FILE *	fileHandle;
    std::string	title, author, publisher;
    Ebook() : fileName(NULL), fileHandle(0) {};

private:
};

class Dumper {
public:
    Dumper(Ebook * sb, const char * op) : book(sb), outDir(op) {};

    //Dump everything in outdir
    void dump() {
	dumpText();
	dumpImages();
	dumpMetadata();
    }
    
    virtual void dumpImages() = 0;
    virtual void dumpText() = 0;
    virtual void dumpMetadata() = 0;

    
    virtual ~Dumper() {};

protected:
    const char *	outDir;
    Ebook *		book;

private:
};

#endif	/* EBOOK_H */

