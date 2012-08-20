#ifndef TOKEN_H
 #define TOKEN_H

typedef enum
{
	TC_INVALID,
	
	TC_IDENTIFIER,
	TC_STRING,
	TC_NUMBER,
	
	TC_IF,
	TC_THEN,
	TC_ELSE,
	TC_ELSEIF,
	TC_END,
	TC_WHILE,
	TC_FOR,
	TC_DO,
	
	TC_PLUS,
	TC_MINUS,
	TC_MULT,
	TC_DIV,
	TC_LT,
	TC_GT,
	TC_LE,
	TC_GE,
	TC_EQ,
	TC_DIFF,
	
	TC_LPAREN,
	TC_RPAREN,
	TC_LCURLY,
	TC_RCURLY,
	TC_LBRACK,
	TC_RBRACK
	
} TokenCode;

typedef struct
{
	TokenCode code;
	char* repr;
} Token;

void token_init     (Token* t, TokenCode code);
void token_initrepr (Token* t, TokenCode code, char* repr, int length);
void token_free     (Token* t);

void token_debug    (Token* t);

#endif
