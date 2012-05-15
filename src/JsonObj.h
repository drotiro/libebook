/* 
 * JsonObj
 * Easy json
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#ifndef JSONOBJ_H
#define	JSONOBJ_H

#include <string>
#include <map>

using std::string;
using std::map;

class JsonObj {
public:
    JsonObj() {}
    virtual ~JsonObj();
    
    void addVal(string key, string val) {
	strings[key] = val;
    }
    
    void addObj(string key, JsonObj& val) {
	objects[key] = val;
    }
    
    string json();
    
private:
    map<string, string> strings;
    map<string, JsonObj> objects;
};

#endif	/* JSONOBJ_H */

