#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "token.h"

void token_init(Token* t, TokenCode code)
{
	t->code = code;
	t->repr = NULL;
}

void token_initrepr(Token* t, TokenCode code, char* repr, int length)
{
	t->code = code;
	t->repr = malloc(length + 1);
	strncpy(t->repr, repr, length);
	t->repr[length] = '\0';
}

void token_free(Token* t)
{
	if (t->repr != NULL)
		free(t->repr);
}

void token_debug(Token* t)
{
	static const char* codestrings[] = {
		"TC_INVALID",
		
		"TC_IDENTIFIER",
		"TC_STRING",
		"TC_NUMBER",
	
		"TC_IF",
		"TC_THEN",
		"TC_ELSE",
		"TC_ELSEIF",
		"TC_END",
		"TC_WHILE",
		"TC_FOR",
		"TC_DO",
	
		"TC_PLUS",
		"TC_MINUS",
		"TC_MULT",
		"TC_DIV",
		"TC_LT",
		"TC_GT",
		"TC_LE",
		"TC_GE",
		"TC_EQ",
		"TC_DIFF",
	
		"TC_LPAREN",
		"TC_RPAREN",
		"TC_LCURLY",
		"TC_RCURLY",
		"TC_LBRACK",
		"TC_RBRACK"
	};
	
	printf("code = %d\n", t->code);
	
	printf("%s", codestrings[t->code]);
	
	if (t->repr != NULL)
		printf("\t(%s)", t->repr);
		
	printf("\n");
}


