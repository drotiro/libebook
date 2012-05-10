/* 
 * Xml
 * simple xml parser
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "Xml.h"
#include <iostream>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <string.h>

bool Xml::initDone = Xml::doInit();

bool Xml::doInit() {
    xmlInitParser();
    std::cerr << "Init done." << std::endl;
    return true;
}


Xml::Xml(string xmlstring) {
    doc = xmlReadMemory(xmlstring.c_str(), xmlstring.size(),
            "Xml.xml", "UTF-8", XML_PARSE_RECOVER | XML_PARSE_NONET );
}

Xml::Xml(const char * xmlstring, int len) {
    doc = xmlReadMemory( xmlstring, len,
        "Xml.xml", "UTF-8", XML_PARSE_RECOVER | XML_PARSE_NONET );
}

std::vector<string> Xml::xpath(string expr) {
    std::vector<string> res;
    if(!isValid()) return res;
    xmlXPathContext * context = xmlXPathNewContext(doc);
    if(!context) {
        return res;
    }
    
    xmlXPathObject * result = xmlXPathEvalExpression((xmlChar*)expr.c_str(), context);

    xmlNodeSet * nodeset;
    xmlChar * nsi;
    if(result) {
	if(result->type == XPATH_STRING) res.push_back((char *)result->stringval);
	else if(result->type == XPATH_NODESET) {
	    nodeset = result->nodesetval;
	    if (nodeset) for (int i=0; i < nodeset->nodeNr; i++) {
		nsi = xmlNodeListGetString(doc, nodeset->nodeTab[i]->xmlChildrenNode, 1);
		res.push_back((char *)nsi);
		xmlFree(nsi);
	    }
	}
    }  

    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    return res;
}

Xml::~Xml() {
    if(doc) xmlFreeDoc(doc);
}
