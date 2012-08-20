#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

void tokenizer_init(Tokenizer* t)
{
	t->source = NULL;
	t->length = 0;
	t->pointer = 0;
	t->line = 1;
	tokenlist_init(&t->tokens);
	
	static const TokenStringCodePair keywords[] = {
		{"if",     TC_IF},
		{"then",   TC_THEN},
		{"else",   TC_ELSE},
		{"elseif", TC_ELSEIF},
		{"end",    TC_END},
		{"while",  TC_WHILE},
		{"for",    TC_FOR},
		{"do",     TC_DO},
		{NULL, 0}
	};
	tokenmap_init(&t->keywords, keywords);
	
	static const TokenStringCodePair operators[] = {
		{"+",  TC_PLUS},
		{"-",  TC_MINUS},
		{"*",  TC_MULT},
		{"/",  TC_DIV},
		{"<",  TC_LT},
		{">",  TC_GT},
		{"<=", TC_LE},
		{">=", TC_GE},
		{"==", TC_EQ},
		{"!=", TC_DIFF},
	
		{"(",  TC_LPAREN},
		{")",  TC_RPAREN},
		{"{",  TC_LCURLY},
		{"}",  TC_RCURLY},
		{"[",  TC_LBRACK},
		{"]",  TC_RBRACK},
		{NULL, 0}
	};
	tokenmap_init(&t->operators, operators);
}

void tokenizer_free(Tokenizer* t)
{
	if (t->source != NULL)
		free(t->source);
		
	tokenlist_free(&t->tokens);
	tokenmap_free(&t->keywords);
	tokenmap_free(&t->operators);
}

int tokenizer_readstring(Tokenizer* t, const char* source)
{
	t->length = strlen(source);
	t->source = malloc(t->length + 1);
	strcpy(t->source, source);
	t->source[t->length] = '\0';
	
	tokenizer_readtokens(t);
	
	return 0;
}

int tokenizer_readfile(Tokenizer* t, const char* filename)
{
	FILE* fp = fopen(filename, "r");
	
	if (fp == NULL)
		return 1;
	
	fseek(fp, 0, SEEK_END);
	t->length = ftell(fp);
	t->source = malloc(t->length + 1);
	rewind(fp);
	fread(t->source, 1, t->length, fp);
	t->source[t->length] = '\0';
	fclose(fp);
	
	tokenizer_readtokens(t);
	
	return 0;
}

void tokenizer_debug(Tokenizer* t)
{
	printf("source:\n%s\n\n", t->source);
	
	TokenListNode* node = t->tokens.first;
	while (node != NULL)
	{
		token_debug(&node->token);
		node = node->next;
	}
}

void tokenizer_readtokens(Tokenizer* t)
{
	tokenizer_skipspaces(t);
	while (t->pointer < t->length)
	{
		tokenizer_readtoken(t);
		tokenizer_skipspaces(t);
	}
}

void tokenizer_readtoken(Tokenizer* t)
{
	char c = t->source[t->pointer];
	int begin = t->pointer;
	t->pointer++;
	if (isalpha(c)) /* identifier or keyword */
	{
		while (isalnum(t->source[t->pointer]))
			t->pointer++;
			
		int length = t->pointer - begin;
			
		/* checking if the token is a keyword */
		TokenCode code = tokenmap_findlength(&t->keywords, t->source + begin, length);
		code = code == TC_INVALID ? TC_IDENTIFIER : code;
		
		Token token;
		token_initrepr(&token, code, t->source + begin, length);
		tokenlist_add(&t->tokens, token);
	}
	else if (isdigit(c)) /* number */
	{
		while (isdigit(t->source[t->pointer]))
			t->pointer++;
			
		if (t->source[t->pointer] == '.')
		{
			t->pointer++;
			
			while (isdigit(t->source[t->pointer]))
				t->pointer++;
		}
		
		int length = t->pointer - begin;
		Token token;
		token_initrepr(&token, TC_NUMBER, t->source + begin, length);
		tokenlist_add(&t->tokens, token);
	}
	else if (c == '"' || c == '\'') /* string */
	{
		while (t->pointer < t->length && t->source[t->pointer] != c)
		{
			if (t->source[t->pointer] == '\\')
				t->pointer++;

			t->pointer++;
		}
		t->pointer++;
		
		int length = t->pointer - begin;
		Token token;
		token_initrepr(&token, TC_STRING, t->source + begin, length);
		tokenlist_add(&t->tokens, token);
	}
	else /* operator or error */
	{
		while (t->pointer < t->length && !tokenizer_isspace(t, t->source[t->pointer]))
			t->pointer++;
		
		int length = t->pointer - begin;
			
		/* checking if the token is an operator */
		TokenCode code = tokenmap_findlength(&t->operators, t->source + begin, length);
		
		if (code == TC_INVALID)
			tokenizer_unknown(t, t->source + begin, length);
			
		else
		{
			Token token;
			token_initrepr(&token, code, t->source + begin, length);
			tokenlist_add(&t->tokens, token);
		}
	}
}

int tokenizer_isspace(Tokenizer* t, char c)
{
	return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

void tokenizer_skipspaces(Tokenizer* t)
{
	char c = t->source[t->pointer];
	while (tokenizer_isspace(t, c))
	{
		if (c == '\n')
			t->line++;
			
		t->pointer++;
		c = t->source[t->pointer];
	}
}

void tokenizer_unknown(Tokenizer* t, const char* string, int length)
{
	char* token = malloc(length + 1);
	strncpy(token, string, length);
	token[length] = '\0';
	fprintf(stderr, "Unknown token: \'%s\' on line %d\n", token, t->line);
	free(token);
}


