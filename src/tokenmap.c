#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tokenmap.h"

void tokenmap_init(TokenMap* tm, const TokenStringCodePair tokens[])
{
	tm->tree = NULL;
	int i;
	for (i = 0; tokens[i].string != NULL; i++)
		tokenmap_add(tm, tokens[i].string, tokens[i].code);
}

void tokenmap_free(TokenMap* tm)
{
	tokenmap_freetree(tm, tm->tree);
}

TokenCode tokenmap_find(TokenMap* tm, const char* string)
{
	return tokenmap_findlength(tm, string, strlen(string));
}

TokenCode tokenmap_findlength(TokenMap* tm, const char* string, int length)
{
	TokenTree* tree = tm->tree;
	int i;
	TokenCode code = TC_INVALID;
	for (i = 0; tree != NULL && i < length; i++)
	{
		while (tree != NULL && tree->character != string[i])
			tree = tree->nextword;

		if (tree != NULL)
			tree = tree->nextcharacter;
	}
	
	if (tree != NULL && tree->character == '\0')
		code = tree->code;
		
	return code;
}

void tokenmap_add(TokenMap* tm, const char* string, TokenCode code)
{
	TokenTree* tree = tm->tree;
	int length = strlen(string);
	int i;
	for (i = 0; i < length; i++)
	{
		TokenTree* prev = NULL;
		while (tree != NULL && tree->character != string[i])
		{
			prev = tree;
			tree = tree->nextword;
		}
		
		if (tree == NULL)
		{
			/* new node */
			tokenmap_createtree(tm, prev, string + i, code);
			break;
		}
		else
		{
			tree = tree->nextcharacter;
		}
	}
}

void tokenmap_debug(TokenMap* tm)
{
	tokenmap_dumptree(tm, tm->tree, 0, 1);
}

void tokenmap_createtree(TokenMap* tm, TokenTree* tt, const char* string, TokenCode code)
{
	TokenTree* prev = NULL;
	
	{
		TokenTree* tree = malloc(sizeof(TokenTree));
		tree->character = string[0];
		tree->code = TC_INVALID;
		tree->nextword = NULL;
		tree->nextcharacter = NULL;
		prev = tree;
	}
	
	if (tt == NULL)
		tm->tree = prev;
		
	else
		tt->nextword = prev;
		
	int i;
	for (i = 1; string[i - 1] != '\0'; i++)
	{
		TokenTree* tree = malloc(sizeof(TokenTree));
		tree->character = string[i];
		tree->code = TC_INVALID;
		tree->nextword = NULL;
		tree->nextcharacter = NULL;
		prev->nextcharacter = tree;
		prev = tree;
	}
	prev->code = code;
}

void tokenmap_freetree(TokenMap* tm, TokenTree* tt)
{
	if (tt != NULL)
	{
		tokenmap_freetree(tm, tt->nextcharacter);
		tokenmap_freetree(tm, tt->nextword);
		free(tt);
	}
}

void tokenmap_dumptree(TokenMap* tm, TokenTree* tt, int level, int nextword)
{
	if (tt != NULL)
	{
		if (nextword)
		{
			int i;
			for (i = 0; i < level; i++)
				printf("  ");
				
			printf("\\");
		}
		
		if (tt->code != TC_INVALID)
			printf(" => %d\n", tt->code);
			
		else
			printf("-%c", tt->character);
			
		tokenmap_dumptree(tm, tt->nextcharacter, level + 1, 0);
		tokenmap_dumptree(tm, tt->nextword, level, 1);
	}
}


