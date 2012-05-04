/* 
 * Zip
 * zip archive helper
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "Zip.h"
using std::string;

#define BUFSIZE 4096

Zip::Zip(const char * path) {
    archive = zip_open(path, ZIP_CHECKCONS, NULL);
}

bool Zip::hasFile(const char * path) {
    if(!isValid()) return false;
    return zip_name_locate(archive, path, ZIP_FL_NOCASE) != -1;
}

string Zip::getFile(string path) {
    int pos = zip_name_locate(archive, path.c_str(), ZIP_FL_NOCASE) != -1;
    if(pos < 0 ) return "";
    
    char buf[BUFSIZE];
    string res;
    zip_file * f = zip_fopen_index(archive, pos, 0);
    if(!f) return "";
    int read = zip_fread(f, buf, BUFSIZE);
    while(read>0) {
	res.append(buf, read);
	read = zip_fread(f, buf, BUFSIZE);
    }
    zip_fclose(f);
    return res;
}

Zip::~Zip() {
    if(isValid()) zip_close(archive);
}

