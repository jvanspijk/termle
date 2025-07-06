#include "answer_words_EN_5.h"
#include "common.h"
#include "dictionary.h"
#include "guessable_words_EN_5.h"

#define LINE_END_LEN 1
#define NULL 0x0

const char* binary_search(const char* word, WordList word_list) {
	int low = 0;
	int high = word_list.amount_of_words;

	while (low <= high) {
		int mid = low + (high - low) / 2;
		char* mid_ptr = word_list.begin_ptr + (mid * (word_list.word_len + LINE_END_LEN));
		char mid_word[MAX_WORD_LENGTH];
		for (int i = 0; i < word_list.word_len; ++i) {
			mid_word[i] = toupper(mid_ptr[i]);
		}
		mid_word[word_list.word_len] = '\0';

		int compare_result = strcmp(word, mid_word);

		if (compare_result == 0) {
			return mid_ptr;
		}
		else if (compare_result < 0) {
			high = mid - 1;
		}
		else if (compare_result > 0) {
			low = mid + 1;
		}
	}

	return NULL;
}

ErrorType lookup_word_in_dictionary(const char* word) {
	int word_len = strlen(word);
	char word_to_check[MAX_WORD_LENGTH];
	
	for (int i = 0; i < word_len; ++i) {
		word_to_check[i] = word[i];
	}
	word_to_check[word_len] = '\0';


	WordList answers_list;
	answers_list.begin_ptr = (const char*)answer_words_EN_5_txt;
	answers_list.end_ptr = answers_list.begin_ptr + answer_words_EN_5_txt_len;
	answers_list.amount_of_words = answer_words_EN_5_txt_len / (answer_words_EN_5_word_len + LINE_END_LEN);
	answers_list.word_len = answer_words_EN_5_word_len;
	
	const char* answers_res = binary_search(word_to_check, answers_list);
	if (answers_res != NULL) {
		return NO_ERROR;
	}
	else if (answers_res == NULL) {
		WordList guessables_list;
		guessables_list.begin_ptr = (const char*)guessable_words_EN_5_txt;
		guessables_list.end_ptr = guessables_list.begin_ptr + guessable_words_EN_5_txt_len;
		guessables_list.amount_of_words = guessable_words_EN_5_txt_len / (guessable_words_EN_5_word_len + LINE_END_LEN);
		guessables_list.word_len = guessable_words_EN_5_word_len;
		const char* guessables_res = binary_search(word_to_check, guessables_list);
		if (guessables_res != NULL) {
			return NO_ERROR;
		}
	}
	return WORD_NOT_IN_DICTIONARY;
}

ErrorType validate_guess(const char* guess, int word_len) {
	if (strlen(guess) > word_len) {
		return WORD_TOO_LONG;
	}
	if (strlen(guess) < word_len) {
		return WORD_TOO_SHORT;
	}

	if (strlen(guess) != word_len) {
		return WORD_LENGTH_MISMATCH;
	}

	return lookup_word_in_dictionary(guess);
}

void get_random_answer(char* buffer, int buffer_len) {
	WordList answers_list;
	answers_list.begin_ptr = (const char*)answer_words_EN_5_txt;
	answers_list.end_ptr = answers_list.begin_ptr + answer_words_EN_5_txt_len;
	answers_list.word_len = answer_words_EN_5_word_len;
	answers_list.amount_of_words = answer_words_EN_5_txt_len / (answers_list.word_len + LINE_END_LEN);


	int random_index = rand() % answers_list.amount_of_words;
	const char* random_word_ptr = answers_list.begin_ptr + (random_index * (answers_list.word_len + LINE_END_LEN));

	
	if (random_word_ptr >= answers_list.end_ptr) {
		perror("Tried to access word outside of bounds.");
		return;
	}

	for (unsigned int i = 0; i < answer_words_EN_5_word_len; ++i) {
		if (i >= buffer_len) {
			perror("buffer length not long enough to support word.");
			return;
		}
		buffer[i] = toupper(random_word_ptr[i]);
	}
	buffer[answers_list.word_len] = '\0';
}

