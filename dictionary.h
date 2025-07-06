#ifndef DICTIONARY_H	
#define DICTIONARY_H
#include "common.h"

typedef struct WordList {
	const char* begin_ptr;
	const char* end_ptr;
	unsigned int word_len;
	unsigned int amount_of_words;
} WordList;

const char* binary_search(const char* word, WordList word_list);

ErrorType lookup_word_in_dictionary(const char* word);

ErrorType validate_guess(const char* guess, int word_len);

void get_random_answer(char* buffer, int buffer_len);

#endif // DICTIONARY_H