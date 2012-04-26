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
	: srcdoc(book), outDir(op) {}

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
};

#endif	/* MOBIHTMLHELPER_H */

