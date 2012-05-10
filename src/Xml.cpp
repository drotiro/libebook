/* 
 * Xml
 * simple xml parser
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "Xml.h"
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <string.h>

bool Xml::initDone = Xml::doInit();

bool Xml::doInit() {
    xmlInitParser();
    return true;
}


Xml::Xml(string xmlstring) {
    //strip "default" namespace
    size_t pos = xmlstring.find("xmlns="), pos1, pos2;
    if (pos != string::npos) {
        pos1 = xmlstring.find('"', pos); //open quotes
        pos1 = xmlstring.find('"', pos1+1); //close
        xmlstring.erase(pos, pos1-pos+1);
    }
    doc = xmlReadMemory(xmlstring.c_str(), xmlstring.size(),
            "Xml.xml", "UTF-8", XML_PARSE_RECOVER | XML_PARSE_NONET );
}

std::vector<string> Xml::xpath(string expr, Xml::nslist * xns) {
    std::vector<string> res;
    if(!isValid()) return res;
    xmlXPathContext * context = xmlXPathNewContext(doc);
    if(!context) {
        return res;
    }
    //register namespaces
    if(xns)
    for ( Xml::nslist::iterator it=xns->begin() ; it != xns->end(); it++ ) {
        xmlXPathRegisterNs(context, 
            (xmlChar*)it->first.c_str() , (xmlChar*)it->second.c_str());
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
