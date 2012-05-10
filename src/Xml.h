/* 
 * Xml
 * simple xml parser
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#ifndef XML_H
#define	XML_H

#include <string>
#include <set>
#include <vector>
#include <libxml/parser.h>

using std::string;

class Xml {
public:
    typedef struct {
	string value, name;
	std::set<string, string> attributes;
    } Element;
    
    Xml(string xmlstring);
    Xml(const char * xmlstring, int len);
    
    bool isValid() { return doc!=NULL; }
    std::vector<string> xpath(string expr);
    
    virtual ~Xml();

private:
    Xml(){};
    xmlDoc * doc;

    static bool initDone;
    static bool doInit();
};

#endif	/* XML_H */

