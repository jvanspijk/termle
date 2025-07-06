#ifndef GAME_STATE_H	
#define GAME_STATE_H
#include "common.h"

typedef enum GameStatus {
	GAME_OVER,
	IN_PROGRESS,
} GameStatus;

typedef enum LetterResult {
	ABSENT,
	WRONG_POS,
	CORRECT_POS
} LetterResult;

typedef struct GameState {
	ErrorType error_type;
	int guess_num;

	int word_len;
	char word_to_guess[MAX_WORD_LENGTH];

	char previous_guesses[TOTAL_GUESSES][MAX_WORD_LENGTH];
	LetterResult previous_results[TOTAL_GUESSES][MAX_WORD_LENGTH];
	GameStatus status;
} GameState;

GameState create_new_game(const char* word, int word_len);

GameState reduce(const GameState old_state, const char* guess);

#endif // GAME_STATE_H