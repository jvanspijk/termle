#include "common.h"

void print_error(ErrorType err)
{
	switch (err) {
		case NO_ERROR:		
			break;
		case WORD_TOO_LONG:
			printf("Error: The word is too long.\n");
			break;
		case WORD_TOO_SHORT:
			printf("Error: The word is too short.\n");
			break;
		case WORD_LENGTH_MISMATCH:
			printf("Error: The word length does not match the expected length.\n");
			break;
		case WORD_NOT_IN_DICTIONARY:
			printf("Error: The word is not in the dictionary.\n");
			break;
		default:
			printf("Unknown error.\n");
			break;
	}
}
