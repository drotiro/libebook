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

class MobiHtmlHelper {
public:
    MobiHtmlHelper(std::string book) : src(book) {}
    
    std::string fixLinks(std::vector<std::string>);

    virtual ~MobiHtmlHelper();
private:
    std::string src;
};

#endif	/* MOBIHTMLHELPER_H */

