/** This header is for host tools; don't use in the embedded build!
*/
#ifndef ADVMAP_H_
#define ADVMAP_H_
//Generated
extern const char * const diagnames[];
extern const size_t diagnames_size;
extern const char * const paramnames[];
extern const size_t paramnames_size;
//Man-made
typedef unsigned long ulong;
typedef struct word_t word_t;
typedef struct word_t {
	char *word;
} word_t;

typedef struct dict_t {
	word_t * w; //a pointer to a particularly sorted array of word_t pointers
	ulong wcount; //how many words there are
	size_t maxlen;
    char *text;
    size_t size; //of the whole text array
} dict_t;
extern int file2dict(dict_t **dict, const char *fname, int replacement);

//private error codes
#define MYERR_OK 0        //do not change
#define MYERR_NOMEM (-1) //out of memory
#define MYERR_BADDIR (-2) //cannot change to this dir
#define MYERR_BADCONF (-3) //cannot open or read config file
#define MYERR_DSTFILE (-4) //cannot open or write to destination file
#define MYERR_REGEXP (-5) //regexp error
//#define MYERR_BADSRCFILE (-6) //src file error
#define MYERR_SEARCH (-7) //bad file search pattern
#define MYERR_MAXNESTED (-8) //include/use statements too nested
#define MYERR_FILEREAD (-9) //include/use statements too nested

#define MYERR_INTERNAL (-128) //internal err; should never happen
u32 mn_CalcAdvanced(size_t advkey_sz, const u8 *advkey, size_t devid_sz, const u8 *dev_id);

#endif //ADVMAP_H_
