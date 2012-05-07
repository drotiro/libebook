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
#include "Dumper.h"

class MobiDumper : public Dumper {
public:
    MobiDumper(MobiBook * book, char * op) : Dumper(op), srcdoc(book) {
	scanImages();
	scanLinks();
    }

    void dumpImages();
    void dumpText();
    void dumpMetadata();

    virtual ~MobiDumper();
private:
    MobiBook *	srcdoc;
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

