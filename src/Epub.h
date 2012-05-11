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
    std::string		getItem(int pos) { return zf->getFile(items[pos]); }
    std::string		getResource(int pos) { return zf->getFile(resources[pos]); }
    
    Dumper *	getDumper(const char * outdir);
    virtual	~Epub();

private:
    Epub() {};
    bool check();
    Zip * zf;
    std::vector<std::string> items, resources;
    std::string base;
};

#endif	/* EPUB_H */

