/* 
 * Zip
 * zip archive helper
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "Zip.h"

Zip::Zip(const char * path) {
    archive = zip_open(path, ZIP_CHECKCONS, NULL);
}

bool Zip::hasFile(const char * path) {
    if(!isValid()) return false;
    return zip_name_locate(archive, path, ZIP_FL_NOCASE) != -1;
}

Zip::~Zip() {
    if(isValid()) zip_close(archive);
}

