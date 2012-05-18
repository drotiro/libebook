/* 
 * Epub 
 * Support for epub ebooks
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "Epub.h"
#include "JsonObj.h"
#include "Xml.h"
#include "Utils.h"
#include <algorithm>
#include <iostream>

const string Epub::dcns = "http://purl.org/dc/elements/1.1/";
const string Epub::dcpref = "dc";
const string Epub::opfns = "http://www.idpf.org/2007/opf";
const string Epub::opfpref = "opf";

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
    Xpath cp = cx.xpath();
    vector<string> xr = cp.query("//rootfile/@full-path");
    if(xr.size() == 0 )  return false;
    string opfpath = xr[0];
    base = opfpath.substr(0, opfpath.find_last_of('/')+1);

    // parse opf
    nslist * ns = new nslist();

    string opfxml = zf->getFile(opfpath);
    (*ns)[dcpref] = dcns;
    (*ns)[opfpref] = opfns;
    string mydc = (opfxml.find("<title")==string::npos ? "//dc:" : "//");
    string myopf = (opfxml.find("<item")==string::npos ? "//opf:" : "//");

    Xml opf(opfxml);
    Xpath ox = opf.xpath(ns);
    title = ox.get(mydc+"title");
    author = ox.get(mydc+"creator");
    publisher = ox.get(mydc+"publisher");
    // cover info
    string coverId = ox.get("//meta[@name='cover']/@content");
    string coverHref = ox.get(myopf+"item[@id='"+coverId+"']/@href");

    // Items:
    // get //itemref/@idref and read the item's href
    xr = ox.query(myopf+"itemref/@idref");
    string ix;
    vector<string> nestx;
    for(vector<string>::iterator it = xr.begin(); it != xr.end(); ++it) {
	ix = myopf+"item[@id='";
	ix.append(*it);
	ix.append("']/@href");
	nestx = ox.query(ix);
	if(nestx.size()>0) {
	    items.push_back(nestx[0]);
	}
    }

    // Resources:
    // <item> not in items vector
    xr = ox.query(myopf+"item/@href");
    for(vector<string>::iterator it = xr.begin(); it != xr.end(); ++it) {
	if(std::find(items.begin(), items.end(), *it) == items.end()) {
		if(coverHref.compare(*it) == 0) coverIndex = resources.size();
		resources.push_back(*it);
	}
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
    JsonObj meta;
    meta.add("author", book->getAuthor());
    meta.add("title", book->getTitle());
    meta.add("publisher", book->getPublisher());
    if(epub->getCover() >= 0)
	meta.add("cover", epub->resourceNames()[epub->getCover()]);
    vector<JsonObj> res;
    for(int i = 0; i < epub->resourceCount(); ++i) {
	JsonObj ares;
	ares.add("path", epub->resourceNames()[i]);
	res.push_back(ares);
    }
    meta.add("res", res);
    vector<string> itemNames = epub->itemNames();
    meta.add("items", itemNames);

    write("info.json", meta.json());
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

