#include <stdlib.h>
#include "tokenlist.h"

void tokenlist_init(TokenList* tl)
{
	tl->first = NULL;
	tl->last = NULL;
}

void tokenlist_free(TokenList* tl)
{
	TokenListNode* node = tl->first;
	while (node != NULL)
	{
		TokenListNode* next = node->next;
		free(node);
		node = next;
	}
}

void tokenlist_add(TokenList* tl, Token token)
{
	if (tl->first == NULL)
	{
		TokenListNode* tln = malloc(sizeof(TokenListNode));
		tln->token = token;
		tln->next = NULL;
		tl->last = tln;
		tl->first = tl->last;
	}
	else
	{
		TokenListNode* last = tl->last;
		TokenListNode* tln = malloc(sizeof(TokenListNode));
		tln->token = token;
		tln->next = NULL;
		last->next = tln;
		tl->last = tln;
	}
}


