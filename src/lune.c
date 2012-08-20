#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"
#include "tokenmap.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	Tokenizer t;
	tokenizer_init(&t);
	tokenizer_readfile(&t, argv[1]);
	tokenizer_debug(&t);
	tokenizer_free(&t);
	
	return EXIT_SUCCESS;
}

