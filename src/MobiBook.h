/* 
 * MobiBook and related classes
 * Based non MobiDoc from SumatraPDF code
 * 
 * Original copyright:
 *   SumatraPDF project authors
 *   License: Simplified BSD (see COPYING.BSD) 
 * 
 * Modified by:
 *   Domenico Rotiroti
 *   License: GPL3 (see COPYING)
 */

#ifndef MobiBook_h
#define MobiBook_h

#include "Utils.h"
#include "Ebook.h"

#include <string>

class HuffDicDecompressor;

// http://en.wikipedia.org/wiki/PDB_(Palm_OS)
#define kDBNameLength    32
#define kPdbHeaderLen    78

#pragma pack(push)
#pragma pack(1)
struct PdbHeader
{
     /* 31 chars + 1 null terminator */
    char        name[kDBNameLength];
    uint16      attributes;
    uint16      version;
    uint32      createTime;
    uint32      modifyTime;
    uint32      backupTime;
    uint32      modificationNumber;
    uint32      appInfoID;
    uint32      sortInfoID;
    char        type[4];
    char        creator[4];
    uint32      idSeed;
    uint32      nextRecordList;
    uint16      numRecords;
};
#pragma pack(pop)

STATIC_ASSERT(kPdbHeaderLen == sizeof(PdbHeader), validPdbHeader);

#define kPdbRecordHeaderLen 8

#pragma pack(push)
#pragma pack(1)
struct PdbRecordHeader {
    uint32   offset;
    uint8    deleted   : 1;
    uint8    dirty     : 1;
    uint8    busy      : 1;
    uint8    secret    : 1;
    uint8    category  : 4;
    char     uniqueID[3];
};
#pragma pack(pop)

STATIC_ASSERT(kPdbRecordHeaderLen == sizeof(PdbRecordHeader), validPdbRecordHeader);

#define kMaxRecordSize 64*1024

struct ImageData {
    char *      data;
    size_t      len;
    char *	type;
};

class MobiBook : public Ebook
{
    PdbHeader           pdbHeader;
    PdbRecordHeader *   recHeaders;
    char *              firstRecData;

    bool                isMobi;
    size_t              docRecCount;
    int                 compressionType;
    size_t              docUncompressedSize;
    int                 textEncoding;

    bool                multibyte;
    size_t              trailersCount;
    size_t              imageFirstRec; // 0 if no images
    int32_t		coverImage;
    unsigned int	locale;

    // we use bufStatic if record fits in it, bufDynamic otherwise
    char                bufStatic[kMaxRecordSize];
    char *              bufDynamic;
    size_t              bufDynamicSize;

    ImageData *         images;
    std::string		doc;

    HuffDicDecompressor *huffDic;

    MobiBook();

    bool	parseHeader();
    bool	loadDocument();
    char *	getBufForRecordData(size_t size);
    size_t	getRecordSize(size_t recNo);
    char*	readRecord(size_t recNo, size_t& sizeOut);
    bool	loadDocRecordIntoBuffer(size_t recNo, std::string& strOut);
    void	loadImages();
    bool	loadImage(size_t imageNo);

public:

    size_t		imagesCount;

    ~MobiBook();

    std::string&	getText() { return doc; }
    size_t		getTextSize() const { return doc.length(); }
    unsigned int	getLocale();
    ImageData *		getCover();
    int32_t		getCoverIndex() { return coverImage; }
    ImageData *		getImage(size_t imgRecIndex) const;
    char *		getFileName() const { return fileName; }

    static MobiBook *	createFromFile(const char *fileName);
    Dumper *		getDumper(const char * outdir);
};

#endif
