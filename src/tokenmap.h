#ifndef TOKENMAP_H
 #define TOKENMAP_H

#include "token.h"

typedef struct
{
	const char* string;
	TokenCode code;
} TokenStringCodePair;

typedef struct TokenTree
{
	char character;
	TokenCode code;
	struct TokenTree* nextword;
	struct TokenTree* nextcharacter;
} TokenTree;

typedef struct
{
	TokenTree* tree;
} TokenMap;

void      tokenmap_init       (TokenMap* tm, const TokenStringCodePair tokens[]);
void      tokenmap_free       (TokenMap* tm);

TokenCode tokenmap_find       (TokenMap* tm, const char* string);
TokenCode tokenmap_findlength (TokenMap* tm, const char* string, int length);

void      tokenmap_add        (TokenMap* tm, const char* string, TokenCode code);

void      tokenmap_debug      (TokenMap* tm);

/* private */
void      tokenmap_createtree (TokenMap* tm, TokenTree* tt, const char* string, TokenCode code);
void      tokenmap_freetree   (TokenMap* tm, TokenTree* tt);
void      tokenmap_dumptree   (TokenMap* tm, TokenTree* tt, int level, int nextword);

#endif


