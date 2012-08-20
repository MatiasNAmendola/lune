#ifndef TOKENREADER_H
 #define TOKENREADER_H

#include "tokenlist.h"
#include "tokenmap.h"

typedef struct
{
	char* source;
	int length;
	int pointer;
	int line;
	TokenList tokens;
	TokenMap keywords;
	TokenMap operators;
} Tokenizer;

void tokenizer_init       (Tokenizer* t);
void tokenizer_free       (Tokenizer* t);

int  tokenizer_readstring (Tokenizer* t, const char* source);
int  tokenizer_readfile   (Tokenizer* t, const char* filename);

void tokenizer_debug      (Tokenizer* t);

/* private */
void tokenizer_readtokens (Tokenizer* t);
void tokenizer_readtoken  (Tokenizer* t);
int  tokenizer_isspace    (Tokenizer* t, char c);
void tokenizer_skipspaces (Tokenizer* t);

void tokenizer_unknown    (Tokenizer* t, const char* string, int length);

#endif
