/* 
 * Ebook 
 * Common interface for the various formats
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#ifndef EBOOK_H
#define	EBOOK_H

#include <string>
#include <map>

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
	dumpResources();
	dumpMetadata();
    }
    
    virtual void dumpResources() = 0;
    virtual void dumpText() = 0;
    virtual void dumpMetadata() = 0;

    
    virtual ~Dumper() {};

protected:
    void	write(const char * name, std::string content);
    void	write(const char * name, char* content, size_t len);
    std::string	jsonize(std::map<std::string, std::string> kv);
    std::string replaceAll(std::string & src, std::string what, std::string with);
    const char *	outDir;
    Ebook *		book;

private:
};

#endif	/* EBOOK_H */

