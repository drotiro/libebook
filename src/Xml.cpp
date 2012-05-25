/* 
 * Xml
 * simple xml parser
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include <libxml2/libxml/tree.h>

#include "Xml.h"

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

std::vector<string> Xpath::query(string expr) {
    std::vector<string> res;
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
		xmlNode * cn = nodeset->nodeTab[i];
		nsi = xmlNodeListGetString(context->doc, cn->xmlChildrenNode, 1);
		if(!nsi) res.push_back(nodeValue(cn));
		if(nsi) {
			res.push_back((char *)nsi);
			xmlFree(nsi);
		}
	    }
	}
    }  

    xmlXPathFreeObject(result);
    return res;
}

string	Xpath::get(string expr) {
    std::vector<string> res = query(expr);
    if(res.size()) return res[0];
    return "";
}

Xml::~Xml() {
    if(doc) xmlFreeDoc(doc);
}


Xpath::Xpath(xmlDoc * doc, nslist * ns) {
    context = xmlXPathNewContext(doc);

    if(ns && context)
	for ( nslist::iterator it=ns->begin() ; it != ns->end(); it++ ) {
		xmlXPathRegisterNs(context, 
		(xmlChar*)it->first.c_str() , (xmlChar*)it->second.c_str());
    }
}

Xpath::~Xpath() {
    if(context) xmlXPathFreeContext(context);
}

string Xpath::nodeValue(xmlNode *node) {
	if(node->xmlChildrenNode == NULL) return (char*)xmlNodeListGetString(context->doc, node, 1);
	string res;
	for(xmlNode* it = node->xmlChildrenNode; it != NULL; it = it->next) {
	    res.append(nodeValue(it));
	}
	return res;
}