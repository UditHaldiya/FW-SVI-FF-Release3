#include <stdio.h>
#include <mnwrap.h>
#include <advmap.h>

/* Configuration retrieval per file extension */
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//a fread() helper (to avoid some old? MS bugs)
static int myfread(char *buf, size_t len, FILE *f)
{
	size_t chunk = 3000;
#if 0
	char *p = fgets(buf, len, f);
	if (p == NULL) {
        return MYERR_FILEREAD;
	}
#endif
	do {
		int n = fread(buf, 1, chunk, f);
		if(ferror(f)) {
			return MYERR_FILEREAD;
		}
		if (n < chunk) { 
			chunk = n;
		}
		buf += chunk;
		len -= chunk;
	} while (!feof(f));
	*buf = 0; //terminate

    return MYERR_OK;
}

//slurp the word file
static int fslurp(FILE *f, char **text, size_t *length)
{
	long len;
    int err;
	char *d = NULL;
	err = fseek(f, 0, SEEK_END);
    if(err == 0) {
	    len = ftell(f);
        if(len < 0) {
            //error
            err = (int)len;
        }
    }
    if(err == 0) {
    	err = fseek(f, 0, SEEK_SET);
    }

    if(err == 0) {
	    d = (char*)malloc(len+1+2); //1 for replacement byte and 2 for terminating 0
        //(last string not terminated by EOL will have its terminating 0 replaced; need 1 more)
        if(d==NULL) {
            err = MYERR_NOMEM;
	    }
        else {
	        err = myfread(d, len, f);
            if(err == MYERR_OK) {
                d[len] = 0; //terminate
                d[len+1] = 0; //extra termination
            }
            else {
                free(d);
                d = NULL;
            }
        }
    }
    else {
        err = MYERR_BADCONF;
    }

    *length = len;
    *text = d;
	return err;
}

//prepare a dictionary out of a text file slurped in
//provides line starts, normalizes the text to platform-independent form
//this function is odd-looking but is for being Windows/Unix/Mac-capable
//returns NULL if out of memory
//NB: cannot omit empty lines because of possible line continuation 
//stop at end of line
#define is_separator(c) ((c)=='\n' || (c)=='\r')
static const char *line2end(const char *str)
{
    while(!is_separator(*str) && *str != 0) {
        str++;
    }
    return str;
}
static const char *line2next(const char *str) //from a separator
{
    char c = *str; //skip last char
    if(c==0) {
        return str;
    }
    str++;
    assert(is_separator(c));
    while(is_separator(*str) && *str != c && *str != 0) {
        str++;
    }
    return str;
}
static dict_t *normalize(char *text, size_t len, const char *separator, int replacement)
{
	//let's not mess with vector<> overhead
	//pass 1: count the number of words
	unsigned long nlines, i;
	size_t wlen, maxlen = 0;
	word_t *w;
	dict_t *dict;
    const char *start, *end;
    char *target;

    //Count the number of "lines"
    for(nlines = 0, start = text; *start != 0; nlines++) {
        //start = start + strcspn(start, separator); //skip all separators
        start = line2end(start); 
        //start = start + strspn(start, separator);
        start = line2next(start);
    }

    /*to handle pathological nlines=0*/
    if(nlines==0) {
        nlines=1;
    }

    //create the line info:
	dict = malloc(sizeof(*dict) + sizeof(*w)*(nlines));
	if(dict==NULL) {
		return NULL;
	}
    w = (word_t *)(dict+1); //to get away with one allocation
    
    //for(i=0, start = target = text; *start != 0; i++) {
    //    assert(i<nlines);
    for(i=0, start = target = text; i<nlines; i++) {
        //start = start + strcspn(start, separator); //skip all separators
        end = line2end(start); 
        //if(*start == 0) {
        //    break; //reached the end of text
        //}
        wlen = end - start; //line length
        memmove(target, start, wlen);
        start = line2next(end);
        target[wlen] = replacement;
        w[i].word = target;
        target += wlen+1; //next block position
        if(maxlen < wlen) {
            maxlen = wlen; //keep track of max length
        }
    }

	dict->w = w;
	dict->wcount = nlines;
	dict->maxlen = maxlen+1;
    dict->text = text;
    dict->size = target - text;
    *target = 0; //terminate: we do have this extra byte; see fslurp()'s allocation

	return dict;
}


void dict_destroy(dict_t *dict)
{
    if(dict != NULL) {
        if(dict->text != NULL) {
            free(dict->text);
        }
        free(dict);
    }
}

#define LINE_SEPARATORS "\n\r"

int file2dict(dict_t **dict, const char *fname, int replacement)
{
    char *text;
    size_t len;
    int err;
	FILE *f = stdin;
	if (strcmp(fname, "stdin") != 0) {
		f = fopen(fname, "rt");
	}
	else {
		f = stdin;
	}
    *dict = NULL; //just in case

    if(f == NULL) {
        return MYERR_BADCONF;
    }

    err = fslurp(f, &text, &len); //slurp the file in

    if(f!=stdin)
		fclose(f);

    if(err != MYERR_OK) {
        return err;
    }

    *dict = normalize(text, len, LINE_SEPARATORS, replacement); 
    if(*dict == NULL) {
        free(text);
        return MYERR_NOMEM;
    }

    return MYERR_OK;
}

//--------------- END READ DICTIONARY ------------------



