#include "common.h"
#include "console_view.h"
#include "game_state.h"
#include <ctype.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#include <synchapi.h>
#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep(ms * 1000)
#endif

void wait_for_user_keypress() {
	getchar();	
}

void clear_console() {
	printf("\033[H\033[J"); // ANSI escape code to clear the console
}

void read_guess(char* buffer) {
	if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
		clear_console();
		printf("Error reading input.\n");
		return;
	}

	// Remove newline character if present  
	size_t len = strlen(buffer);
	if (len > 0 && buffer[len - 1] == '\n') {
		buffer[len - 1] = '\0';
	}

	// convert guess to uppercase
	for (int i = 0; buffer[i]; i++) {
		buffer[i] = (unsigned char)toupper(buffer[i]);
	}
}

void print_game_state(const GameState state, int animation_delay_ms) {
	//printf("Word to guess: %.*s\n", state.word_len, state.word_to_guess);
	for (int i = 0; i < state.guess_num; ++i) {
		for (int j = 0; j < state.word_len; ++j) {
			switch (state.previous_results[i][j]) {
			case CORRECT_POS:
				printf(ANSI_COLOR_GREEN "%c " ANSI_COLOR_RESET, toupper(state.previous_guesses[i][j]));
				break;
			case WRONG_POS:
				printf(ANSI_COLOR_YELLOW "%c " ANSI_COLOR_RESET, toupper(state.previous_guesses[i][j]));
				break;
			case ABSENT:
				printf(ANSI_COLOR_RED "%c " ANSI_COLOR_RESET, toupper(state.previous_guesses[i][j]));
				break;
			}
			// animation for most recent guess
			if (i == state.guess_num - 1) {
				SLEEP_MS(animation_delay_ms);
			}
		}
		printf("\n");
	}
	for (int i = state.guess_num; i < TOTAL_GUESSES - 1; ++i) {
		for (int j = 0; j < state.word_len; ++j) {
			printf("- ");
		}
		printf("\n");
	}
}