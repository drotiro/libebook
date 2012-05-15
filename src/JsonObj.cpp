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
    bool empty = true;
    // simple values
    for( std::map<string, string>::iterator it = strings.begin(); it != strings.end(); ++it) {
	if(!empty) js.append(","); else empty = false;
	js.append("\"").append(it->first).append("\":\"");
	js.append(replaceAll(it->second, "/", "\\/")).append("\"");
	empty = false;
    }
    // arrays/objects
    for( std::map<string, JsonObj>::iterator it = objects.begin(); it != objects.end(); ++it) {
	if(!empty) js.append(","); else empty = false;
	js.append("\"").append(it->first).append("\":");
	js.append(it->second.json());
    }    
    js.append("}");
    return js;
}
