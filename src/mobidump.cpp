/* 
 * mobidump - dump the contents of a .mobi file
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "MobiDoc.h"
#include <iostream>

#define BUF_SIZE 4096

#ifdef _WIN32
 #define SEP "\\"
#else
 #define SEP "/"
#endif

using std::string; 
using std::cerr;

/*
 * 
 */
int main(int argc, char** argv) {
    if(argc == 3) {
	MobiDoc * m = MobiDoc::CreateFromFile(argv[1]);
	if(m==NULL) {
	    cerr << "Unable to open file " << argv[1] << std::endl;
	    return 1;
	}

	// Get text
	char name[BUF_SIZE];
	FILE * text;
	sprintf(name, "%s%stext.html", argv[2], SEP);
	text = fopen(name, "wb");
	fprintf(text,"%s", m->GetBookHtmlData().c_str());
	fclose(text);
	
	// Get images
	ImageData * id;
	FILE * img;
		
	for(int i = 1; i <= m->imagesCount; ++i) {
	    id = m->GetImage(i);
	    if(id==NULL) break;
	    sprintf(name, "%s%simg_%02d%s", argv[2], SEP, i, id->type);
	    img = fopen(name, "wb");
	    fwrite(id->data, 1, id->len, img);
	    fclose(img);
	}
	
	id = m->GetCoverImage();
	sprintf(name, "%s%scover%s", argv[2], SEP, id->type);
	img = fopen(name, "wb");
	fwrite(id->data, 1, id->len, img);
	fclose(img);

	delete m;
	return 0;
    }

    //no args
    cerr << "Usage: " << argv[0] << " <mobifile> <outdir>" << std::endl;
    return 1;
}

