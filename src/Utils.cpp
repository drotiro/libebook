/* Utils
 * Commmon utilities
 */

#include "Utils.h"

std::string replaceAll(std::string & src, std::string what, std::string with) {
    std::string::size_type pos = src.find(what),
	len = what.length(),
	rlen = with.length();
    while(pos!=std::string::npos) {
	src.replace(pos, len, with);
	pos = src.find(what, pos+rlen);
    }
    return src;
}

