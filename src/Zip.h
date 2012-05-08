/* 
 * Zip
 * zip archive helper
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#ifndef ZIP_H
#define	ZIP_H

#include <zip.h>

class Zip {
public:
    Zip(const char * path);
    
    bool isValid() { return archive!=NULL; }
    bool hasFile(const char * path);
    
    virtual ~Zip();

private:
    zip * archive;
};

#endif	/* ZIP_H */

