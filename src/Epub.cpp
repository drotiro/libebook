/* 
 * Epub 
 * Support for epub ebooks
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "Epub.h"
#include "Xml.h"

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
    Xml cx(container);
    std::vector<string> xr = cx.xpath("//rootfile/@full-path");
    if(xr.size() == 0 )  return false;
    
    // parse opf
    Xml::nslist * ns = new Xml::nslist();
    (*ns)["dc"] = "http://purl.org/dc/elements/1.1/";
    Xml opf(zf->getFile(xr[0]));
    xr = opf.xpath("//dc:title", ns);
    if(xr.size()) title = xr[0];
    xr = opf.xpath("//dc:creator", ns);
    if(xr.size()) author = xr[0];
    delete ns;
    
    return true;
}

Dumper * Epub::getDumper(const char * outdir) {
    return NULL; //TBD
}

Epub::~Epub() {
    delete zf;
}