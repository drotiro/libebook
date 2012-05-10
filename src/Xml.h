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
#include <map>
#include <vector>
#include <libxml/parser.h>

using std::string;

class Xml {
public:
    typedef struct {
	string value, name;
	std::map<string, string> attributes;
    } Element;
    
    typedef std::map<string, string> nslist;
    
    Xml(string xmlstring);
    
    bool isValid() { return doc!=NULL; }
    std::vector<string> xpath(string expr, nslist * xns = NULL);
    
    virtual ~Xml();

private:
    Xml(){};
    xmlDoc * doc;

    static bool initDone;
    static bool doInit();
};

#endif	/* XML_H */

