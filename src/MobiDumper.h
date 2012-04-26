/* 
 * MobiDumper 
 * Utilities for content extraction and
 * markup "normalization" of mobi files
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
	}

    void dumpImages();
    void dumpText();
    void dumpMetadata();

    virtual ~MobiDumper();
private:
    MobiDoc *	srcdoc;
    char *	outDir;
    std::vector<std::string> imgNames;

    void jsonAdd(std::string &, std::string, std::string);
    std::string fixLinks();
    void write(const char * name, std::string content);
    void write(const char * name, char* content, size_t len);
    void scanImages();
};

#endif	/* MOBIHTMLHELPER_H */

