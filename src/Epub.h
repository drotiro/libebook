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

using std::string;
using std::vector;

class Epub : public Ebook {
public:
    static Epub *	createFromFile(const char *fileName);
    vector<string>	itemNames() { return items; }
    vector<string>	resourceNames() { return resources; }
    int			itemCount() { return items.size(); }
    int			resourceCount() { return resources.size(); }
    string		getItem(int pos) { return zf->getFile(base+items[pos]); }
    vector<unsigned char>	getResource(int pos) { return zf->getBinaryFile(base+resources[pos]); }
    
    Dumper *	getDumper(const char * outdir);
    virtual	~Epub();

private:
    Epub() {};
    bool check();
    Zip * zf;
    vector<string> items, resources;
    string base;
    const static string dcns, dcpref, opfns, opfpref;
};

class EpubDumper : public Dumper {

public:
    EpubDumper(Ebook * book, const char * op) : Dumper(book, op) {
	epub = static_cast<Epub*>(book);
    };
    
    void dumpResources();
    void dumpMetadata();
    void dumpText();
    
private:
    Epub * epub;
};

#endif	/* EPUB_H */

