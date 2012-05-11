/* 
 * Epub 
 * Support for epub ebooks
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "Epub.h"
#include "Xml.h"
#include <algorithm>

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
    vector<string> xr = cx.xpath("//rootfile/@full-path");
    if(xr.size() == 0 )  return false;
    string opfpath = xr[0];
    base = opfpath.substr(0, opfpath.find_last_of('/')+1);
    
    // parse opf
    Xml::nslist * ns = new Xml::nslist();
    (*ns)["dc"] = "http://purl.org/dc/elements/1.1/";
    (*ns)["opf"] = "http://www.idpf.org/2007/opf";
    Xml opf(zf->getFile(opfpath));
    xr = opf.xpath("//dc:title", ns);
    if(xr.size()) title = xr[0];
    xr = opf.xpath("//dc:creator", ns);
    if(xr.size()) author = xr[0];
    xr = opf.xpath("//dc:publisher", ns);
    if(xr.size()) publisher = xr[0];
    // Items:
    // get //itemref/@idref and read the item's href
    xr = opf.xpath("//opf:itemref/@idref", ns);
    string ix;
    vector<string> nestx;
    for(vector<string>::iterator it = xr.begin(); it != xr.end(); ++it) {
	ix = "//opf:item[@id='";
	ix.append(*it);
	ix.append("']/@href");
	nestx = opf.xpath(ix, ns);
	if(nestx.size()>0) items.push_back(nestx[0]);
    }
    // Resources:
    // <item> not in vector items
    xr = opf.xpath("//opf:item/@href", ns);
    for(vector<string>::iterator it = xr.begin(); it != xr.end(); ++it) {
	if(std::find(items.begin(), items.end(), *it) == items.end())
	    resources.push_back(*it);
    }
    delete ns;

    return true;
}

Dumper * Epub::getDumper(const char * outdir) {
    return new EpubDumper(this, outdir);
}

Epub::~Epub() {
    delete zf;
}

void EpubDumper::dumpMetadata() {
    std::map<string, string> meta;
    meta["author"] = book->getAuthor();
    meta["title"] = book->getTitle();
    meta["publisher"] = book->getPublisher();
    //meta["cover"] = imgNames[mobi->getCoverIndex()];

    write("info.json", jsonize(meta));
}

void EpubDumper::dumpText() {
    vector<string> items = epub->itemNames();
    int pos;
    vector<string>::iterator it;
    for(it = items.begin(), pos = 0; it != items.end(); ++it, ++pos) {
	write(it->c_str(), epub->getItem(pos));
    }
}

void EpubDumper::dumpResources() {
    vector<string> items = epub->resourceNames();
    int pos;
    vector<string>::iterator it;
    for(it = items.begin(), pos = 0; it != items.end(); ++it, ++pos) {
	vector<unsigned char> res = epub->getResource(pos);
	write(it->c_str(), (char*)&res[0], res.size());
    }    
}

