/* 
 * MobiHtmlHelper - transforms mobi markup in standard HTML
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#ifndef MOBIHTMLHELPER_H
#define	MOBIHTMLHELPER_H

#include <string>
#include <vector>
#include "MobiDoc.h"

class MobiDumper {
public:
    MobiDumper(MobiDoc * book, char * op) 
	: srcdoc(book), outDir(op) {
	    scanImages();
	    scanLinks();
	}

    void dumpImages();
    void dumpText();
    void dumpMetadata();

    virtual ~MobiDumper();
private:
    MobiDoc *	srcdoc;
    char *	outDir;
    std::vector<std::string> imgNames;
    std::vector<int> filepos;


    void jsonAdd(std::string &, std::string, std::string);
    std::string fixLinks(std::string );
    void write(const char * name, std::string content);
    void write(const char * name, char* content, size_t len);
    void scanImages();
    void scanLinks();
};

#endif	/* MOBIHTMLHELPER_H */

