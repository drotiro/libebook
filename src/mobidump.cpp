/* 
 * mobidump - dump the contents of a .mobi file
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "MobiDoc.h"
#include "MobiDumper.h"
#include <iostream>
#include <vector>

#define BUF_SIZE 4096

#ifdef _WIN32
 #define SEP "\\"
#else
 #define SEP "/"
#endif

using std::string; 
using std::cerr;
using std::vector;

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
	string book = m->GetBookHtmlData();
	sprintf(name, "%s%stext_raw.html", argv[2], SEP);
	text = fopen(name, "wb");
	fprintf(text,"%s", book.c_str());
	fclose(text);
	
	// Get images
	ImageData * id;
	FILE * img;
	vector<string> imgNames;
	for(int i = 1; i <= m->imagesCount; ++i) {
	    id = m->GetImage(i);
	    if(id==NULL) break;
	    sprintf(name, "%s%simg_%03d%s", argv[2], SEP, i, id->type);
	    imgNames.push_back(string(name));
	    img = fopen(name, "wb");
	    fwrite(id->data, 1, id->len, img);
	    fclose(img);
	}
	
	// Fix HTML
	MobiHelper h = MobiHelper(m, imgNames, argv[2]);
	string book2 = h.fixLinks();
	sprintf(name, "%s%stext_fixed.html", argv[2], SEP);
	text = fopen(name, "wb");
	fprintf(text,"%s", book2.c_str());
	fclose(text);
	
	id = m->GetCoverImage();
	sprintf(name, "%s%scover%s", argv[2], SEP, id->type);
	img = fopen(name, "wb");
	fwrite(id->data, 1, id->len, img);
	fclose(img);

	string ji = h.getJsonInfo();
	sprintf(name, "%s%sinfo.json", argv[2], SEP);
	text = fopen(name, "wb");
	fprintf(text,"%s", ji.c_str());
	fclose(text);
	
	delete m;
	return 0;
    }

    //no args
    cerr << "Usage: " << argv[0] << " <mobifile> <outdir>" << std::endl;
    return 1;
}

