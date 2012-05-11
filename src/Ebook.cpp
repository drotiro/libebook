/* 
 * Ebook 
 * Common interface for the various formats
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "Ebook.h"
#include "Utils.h"
#include <stdio.h>

using std::string;

void Dumper::write(const char * name, string content) {
    FILE * f;
    char fname[PATHLEN];
    sprintf(fname, "%s%s%s", outDir, SEP, name);
    f = fopen(fname, "wb");
    fprintf(f,"%s", content.c_str());
    fclose(f);
}

void Dumper::write(const char * name, char * content, size_t len) {
    FILE * f;
    char fname[PATHLEN];
    sprintf(fname, "%s%s%s", outDir, SEP, name);
    f = fopen(fname, "wb");
    fwrite(content, 1, len, f);
    fclose(f);
}

string Dumper::jsonize(std::map<string, string> kv) {
    string js = "{";
    for( std::map<string, string>::iterator it = kv.begin(); it != kv.end(); ++it) {
	if(it != kv.begin()) js.append(",");
	js.append("\"").append(it->first).append("\":\"");
	js.append(replaceAll(it->second, "/", "\\/")).append("\"");
    }
    js.append("}");
    return js;
}

string Dumper::replaceAll(string & src, string what, string with) {
    string::size_type pos = src.find(what),
	len = what.length(),
	rlen = with.length();
    while(pos!=string::npos) {
	src.replace(pos, len, with);
	pos = src.find(what, pos+rlen);
    }
    return src;
}

