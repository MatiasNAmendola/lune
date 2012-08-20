#ifndef TOKENLIST_H
 #define TOKENLIST_H

#include "token.h"

typedef struct TokenListNode
{
	Token token;
	struct TokenListNode* next;
} TokenListNode;

typedef struct
{
	TokenListNode* first;
	TokenListNode* last;
} TokenList;

void tokenlist_init (TokenList* tl);
void tokenlist_free (TokenList* tl);

void tokenlist_add  (TokenList* tl, Token token);

#endif
