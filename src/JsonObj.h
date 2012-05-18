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
#include <vector>

using std::string;
using std::map;
using std::vector;

class JsonObj {
public:
    JsonObj() {}
    virtual ~JsonObj();
    
    JsonObj& add(string key, string val) {
	strings[key] = val;
	return *this;
    }
    
    JsonObj& add(string key, JsonObj& val) {
	objects[key] = val;
	return *this;
    }
    
    JsonObj& add(string key, vector<JsonObj>& val) {
	arrays[key] = val;
	return *this;
    }

    JsonObj& add(string key, vector<string>& val) {
	sarrays[key] = val;
	return *this;
    }

    string json();
    
private:
    map<string, string> strings;
    map<string, JsonObj> objects;
    map<string, vector<JsonObj> > arrays;
    map<string, vector<string> > sarrays;
};

#endif	/* JSONOBJ_H */

