/* 
 * Epub 
 * Support for epub ebooks
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "Epub.h"
#include "Xml.h"

#define BREAK_XPATH "xmlns=\"urn:oasis:names:tc:opendocument:xmlns:container\""

using std::string;

Epub *	Epub::createFromFile(const char *fileName) {
    Epub * book = new Epub();
    book->zf = new Zip(fileName);
    
    if(!book->check()) {
        delete book;
        return NULL;
    }
    
    return book;
}

bool Epub::check() {
    //this checks both archive validity and mimetype presence
    if(!zf->hasFile("mimetype")) return false;
    if(!zf->hasFile("META-INF/container.xml")) return false;
    
    // read opf path from container
    string container = zf->getFile("META-INF/container.xml");
    // libxml2's xpath has a problem with this...
    size_t pos = container.find(BREAK_XPATH);
    if(pos!=string::npos) container.erase( pos, sizeof(BREAK_XPATH)-1);
    Xml cx(container);
    std::vector<string> xr = cx.xpath("//rootfile/@full-path");
    if(xr.size() == 0 )  return false;
    
    // parse opf
    Xml * opf = new Xml(zf->getFile(xr[0]));
    xr = opf->xpath("/metadata/title");
    if(xr.size()) title = xr[0];
    xr = opf->xpath("/metadata/creator");
    if(xr.size()) author = xr[0];
    delete opf;

    
    return true;
}

Dumper * Epub::getDumper(const char * outdir) {
    return NULL; //TBD
}

Epub::~Epub() {
    delete zf;
}