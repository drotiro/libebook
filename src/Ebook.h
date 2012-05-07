/* 
 * Ebook 
 * Common interface for the variou formats
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include <string>

#ifndef EBOOK_H
#define	EBOOK_H

class Ebook {
public:

    virtual ~Ebook() {};
    virtual std::string	getTitle() { return title; }
    virtual std::string	getAuthor() { return author; }
    virtual std::string	getPublisher() { return publisher; }

protected:
    char *	fileName;
    FILE *	fileHandle;
    std::string	title, author, publisher;
    Ebook() : fileName(NULL), fileHandle(0) {};

private:
};

#endif	/* EBOOK_H */

