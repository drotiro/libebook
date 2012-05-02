/* 
 * Locale - Translates LCIDs into their names
 * the table data is taken from internet
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#ifndef LOCALE_H
#define LOCALE_H

#include <string>
#include <map>

class Locale {
	private:
		static Locale * theInstance;
		std::map<unsigned int, std::string> l;
		Locale();
	
	public:
		static Locale * getInstance();
		static std::string getName(int lcid);
};

#endif //LOCALE_H