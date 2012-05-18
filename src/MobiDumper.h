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
#include "MobiBook.h"

class MobiDumper : public Dumper {
public:
    MobiDumper(Ebook * book, const char * op) : Dumper(book, op) {
	mobi = static_cast<MobiBook*>(book);
	scanImages();
	scanLinks();
    }

    void dumpResources();
    void dumpText();
    void dumpMetadata();

    virtual ~MobiDumper();
private:
    MobiBook * mobi;
    std::vector<std::string> imgNames, txtFileNames;
    std::vector<int> filepos;


    std::string fixLinks(std::string );
    void scanImages();
    void scanLinks();
};

#endif	/* MOBIHTMLHELPER_H */

