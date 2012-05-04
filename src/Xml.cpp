/* 
 * Xml
 * simple xml parser
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "Xml.h"
#include <libxml/xpath.h>

bool Xml::initDone = Xml::doInit();

bool Xml::doInit() {
    xmlInitParser();
    return true;
}


Xml::Xml(string xmlstring) {
    Xml(xmlstring.c_str());
}

Xml::Xml(const char * xmlstring) {
    doc = xmlReadDoc( (const xmlChar*)xmlstring, "somedoc.xml", "UTF-8", 
	    XML_PARSE_RECOVER | XML_PARSE_NONET );    
}

std::vector<string> Xml::xpath(string expr) {
    std::vector<string> res;
    xmlXPathContext * context = xmlXPathNewContext(doc);
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

