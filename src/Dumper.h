/* 
 * Dumper 
 * Interface for format-specific dumpers
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#ifndef DUMPER_H
#define	DUMPER_H

class Dumper {
public:
    Dumper(char * op) : outDir(op) {};

    //Dump everything in outdir
    void dump() {
	dumpText();
	dumpImages();
	dumpMetadata();
    }
    
    virtual void dumpImages() = 0;
    virtual void dumpText() = 0;
    virtual void dumpMetadata() = 0;

    
    virtual ~Dumper() {};

protected:
    char *	outDir;

private:
};

#endif	/* DUMPER_H */

