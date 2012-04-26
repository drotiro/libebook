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

class MobiHelper {
public:
    MobiHelper(MobiDoc * book, std::vector<std::string> in, char * op) 
	: srcdoc(book), imgNames(in), outDir(op) {}
    
    std::string fixLinks();
    std::string getJsonInfo();

    virtual ~MobiHelper();
private:
    MobiDoc *	srcdoc;
    char *	outDir;
    std::vector<std::string> imgNames;
    void jsonAdd(std::string &, std::string, std::string);
};

#endif	/* MOBIHTMLHELPER_H */

