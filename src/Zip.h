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
#include <string>
#include <vector>

class Zip {
public:
    Zip(const char * path);
    
    bool isValid() { return archive!=NULL; }
    bool hasFile(const char * path);
    std::string getFile(std::string path);
    std::vector<unsigned char> getBinaryFile(std::string path);
    virtual ~Zip();

private:
    zip * archive;
};

#endif	/* ZIP_H */

