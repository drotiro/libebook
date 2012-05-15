/* 
 * JsonObj
 * Easy json
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "JsonObj.h"
#include "Utils.h"

JsonObj::~JsonObj() {
}

string JsonObj::json() {
    string js = "{";
    bool empty = true, aempty;
    // simple values
    for( std::map<string, string>::iterator it = strings.begin(); it != strings.end(); ++it) {
	if(!empty) js.append(","); else empty = false;
	js.append("\"").append(it->first).append("\":\"");
	js.append(replaceAll(it->second, "/", "\\/")).append("\"");
	empty = false;
    }
    // objects
    for( std::map<string, JsonObj>::iterator it = objects.begin(); it != objects.end(); ++it) {
	if(!empty) js.append(","); else empty = false;
	js.append("\"").append(it->first).append("\":");
	js.append(it->second.json());
    }
    // arrays
    for( std::map<string, vector<JsonObj> >::iterator it = arrays.begin(); it != arrays.end(); ++it) {
	if(!empty) js.append(","); else empty = false;
	js.append("\"").append(it->first).append("\":[");
	aempty = true;
	for( vector<JsonObj>::iterator ait = it->second.begin(); ait != it->second.end(); ++ait) {
		if(!aempty) js.append(","); else aempty = false;
		js.append(ait->json());
	}
	js.append("]");
    }

    js.append("}");
    return js;
}
