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
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

using std::string;

typedef std::map<string, string> nslist;

class Xpath {
	friend class Xml;
public:
	std::vector<string>	query(string expr);
	string		get(string expr);

	~Xpath();    

private:
	Xpath(xmlDoc * doc, nslist * ns);
	string nodeValue(xmlNode *node);
	xmlXPathContext * context;
	
};

class Xml {
public:
/*    typedef struct {
	string value, name;
	std::map<string, string> attributes;
    } Element;
*/
  
    Xml(string xmlstring);
    
    bool isValid() { return doc!=NULL; }
    Xpath xpath(nslist * ns = NULL) { return Xpath(doc, ns); }
    
    virtual ~Xml();

private:
    Xml(){};
    xmlDoc * doc;

    static bool initDone;
    static bool doInit();
};

#endif	/* XML_H */

