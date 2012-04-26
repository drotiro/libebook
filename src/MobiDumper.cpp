/* 
 * MobiHtmlHelper - transforms mobi markup in standard HTML
 * 
 * Author:  Domenico Rotiroti
 * License: GPL3 (see COPYING)
 */

#include "MobiDumper.h"
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <string>

using std::string;
using std::vector;

#define FPOSLEN 10

#ifdef _WIN32
 #define SEP "\\"
#else
 #define SEP "/"
#endif


MobiDumper::~MobiDumper() {
}

void MobiDumper::write(const char * name, string content) {
    FILE * f;
    char fname[MAX_PATH];
    sprintf(fname, "%s%s%s", outDir, SEP, name);
    f = fopen(fname, "wb");
    fprintf(f,"%s", content.c_str());
    fclose(f);
}

void MobiDumper::jsonAdd(string & js, string key, string val) {
    js.append("\"").append(key).append("\":\"").append(val).append("\",");
}

void MobiDumper::dumpMetadata() {
    string js = "{";
    jsonAdd(js, "author", srcdoc->GetAuthor());
    jsonAdd(js, "publisher", srcdoc->GetPublisher());
    jsonAdd(js, "title", srcdoc->GetTitle());
    jsonAdd(js, "cover", imgNames[srcdoc->GetCoverImageIndex()]);
    //TODO: TOC
    jsonAdd(js, "content-path", outDir);
    //TODO: RES
    js.append("}");
    
    write("info.json", js);
}

string MobiDumper::fixLinks() {
    string src = srcdoc->GetBookHtmlData();
    char fbuf[24];

    // Step 1. fix a[@href]
    vector<int> fpos;
    string fmark = "filepos=";
    int val;
    
    // find all filepos marks (avoiding duplicates)
    string::size_type pos = src.find(fmark);
    while(pos!=string::npos) {
	val = atoi(src.substr(pos+fmark.length(), FPOSLEN).c_str());
	if( std::find(fpos.begin(), fpos.end(), val) == fpos.end())
		fpos.push_back(val);
	pos = src.find(fmark, pos+1);
    }
    
    // sort them in reverse order
    std::sort(fpos.begin(), fpos.end(), std::greater<int>());
    
    // add anchors    
    for( vector<int>::iterator ip = fpos.begin(); ip != fpos.end(); ip++) {
	sprintf(fbuf, "<a name=\"%010d\"/>", *ip);
	src.insert(*ip, fbuf);
    }
    
    // replace filepos with href
    pos = src.find(fmark);
    while(pos!=string::npos) {
	src.replace(pos, fmark.length(), "href=#");
	pos = src.find(fmark, pos+1);
    }

    // Step 2. fix img[@src]
    for(int i = 0; i < imgNames.size(); ++i) {
	sprintf(fbuf, "recindex=\"%05d\"", i+1);
	string f1 = string(fbuf);
	string r1 = "src=\"";
	r1.append(imgNames[i]);
	r1.append("\"");
	pos = src.find(f1);
	while(pos!=string::npos) {
	    src.replace(pos, f1.length(), r1);
	    pos = src.find(f1);
	}
    }

    return src;
}

void MobiDumper::dumpText() {
    string text = fixLinks();
    write("text.html", text);
}

void MobiDumper::dumpImages() {
	ImageData * id;
	FILE * img;
	char fname[MAX_PATH];
	
	for(int i = 1; i <= srcdoc->imagesCount; ++i) {
	    id = srcdoc->GetImage(i);
	    if(id==NULL) break;
	    sprintf(fname, "%s%simg_%03d%s", outDir, SEP, i, id->type);
	    imgNames.push_back(string(fname));
	    img = fopen(fname, "wb");
	    fwrite(id->data, 1, id->len, img);
	    fclose(img);
	}
}