#include "common.h"
#include "game_state.h"

static LetterResult get_result_for_letter(const char* word_to_guess, const char* guess, int char_index, int word_len) {
	char guessed_letter = guess[char_index];

	if (word_to_guess[char_index] == guessed_letter) {
		return CORRECT_POS;
	}

	// first we count how many times the char appears in the secret word
	int guessed_letter_count_in_word_to_guess = 0;
	for (int i = 0; i < word_len; ++i) {
		if (word_to_guess[i] == guessed_letter) {
			guessed_letter_count_in_word_to_guess += 1;
		}	
	}	

	// Then we calculate how many times it has matched before
	int previous_matches = 0;
	for (int i = 0; i < char_index; ++i) {
		if (guess[i] == guessed_letter) {
			previous_matches += 1;
		}
	}

	int matches_left = guessed_letter_count_in_word_to_guess - previous_matches;
	if (matches_left <= 0) {
		return ABSENT;
	}
	else {
		return WRONG_POS;
	}

	return ABSENT;
}

GameState create_new_game(const char* word, int word_len) {
	GameState new_state = { 0 };

	if (word_len > MAX_WORD_LENGTH) {
		new_state.error_type = WORD_TOO_LONG;		
		return new_state; 	
	}

	new_state.word_len = word_len;

	// initialize arrays
	for (int i = 0; i < word_len; ++i) {
		if (word[i] == '\0') {
			new_state.error_type = WORD_LENGTH_MISMATCH;
			return new_state;
		}
		new_state.word_to_guess[i] = word[i];
	}
	for (int i = 0; i < TOTAL_GUESSES; ++i) {
		new_state.previous_guesses[i][0] = '\0';
		for (int j = 0; j < (MAX_WORD_LENGTH - 1); ++j) {
			new_state.previous_results[i][j] = ABSENT;
		}
	}

	new_state.status = IN_PROGRESS;
	return new_state;
}

GameState reduce(const GameState old_state, const char* guess) {
	GameState new_state = old_state;

	// add new guess to guesses and results
	for (int i = 0; i < old_state.word_len; ++i) {
		new_state.previous_guesses[old_state.guess_num][i] = guess[i];
		new_state.previous_results[old_state.guess_num][i] = get_result_for_letter(old_state.word_to_guess, guess, i, old_state.word_len);
	}

	new_state.guess_num += 1;
	return new_state;
}