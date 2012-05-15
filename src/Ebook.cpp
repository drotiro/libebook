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
#include <libgen.h>

using std::string;

void Dumper::write(const char * name, string content) {
    FILE * f;
    char fname[PATHLEN], dname[PATHLEN];
    
    strcpy(dname, name);
    sprintf(fname, "%s%s%s", outDir, SEP, basename(dname));
    
    f = fopen(fname, "wb");
    fprintf(f,"%s", content.c_str());
    fclose(f);
}

void Dumper::write(const char * name, char * content, size_t len) {
    FILE * f;
    char fname[PATHLEN], dname[PATHLEN];
    
    strcpy(dname, name);
    sprintf(fname, "%s%s%s", outDir, SEP, basename(dname));
    
    f = fopen(fname, "wb");
    fwrite(content, 1, len, f);
    fclose(f);
}
