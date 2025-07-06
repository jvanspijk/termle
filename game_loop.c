#include "common.h"
#include "console_view.h"
#include "dictionary.h"
#include "game_loop.h"
#include "game_state.h"  
#include <stdio.h>

static void read_guess(char* buffer) {
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

static ProgramState play_round(GameState game) {    
	if (game.error_type != NO_ERROR) {
		print_error(game.error_type);		
        return EXITING;
	}
    if (game.status == GAME_OVER) {
        printf("ERROR: Game is over before it began.");
        return EXITING;
    }

    while (game.status != GAME_OVER) {
        clear_console();
        print_game_state(game, 125);
        printf("\n");
        printf("input a guess: ");
        char guess[MAX_WORD_LENGTH + 2]; // +2 for newline and null terminator
        read_guess(guess);        

        if (strcmp(guess, EXIT_COMMAND) == 0) {
            clear_console();
            printf("Exiting the game.\n");
            break;
        }
        // Check if the guess is valid  
		ErrorType guess_err = validate_guess(guess, game.word_len);
		if (guess_err != NO_ERROR) {
            clear_console();
			print_error(guess_err);
            wait_for_user_keypress();
			continue;
		}

        game = reduce(game, guess);
        // Check for win condition  
        if (strcmp(guess, game.word_to_guess) == 0) {
            clear_console();
            printf("Congratulations! You've guessed the word: %s\n", game.word_to_guess);
            return RUNNING;
        }
        // Check for max guesses  
        if (game.guess_num >= TOTAL_GUESSES) {
            clear_console();
            printf("Game over! The word was: %s\n", game.word_to_guess);
            return RUNNING;
        }
        printf("\n");

    }
    return EXITING;
}

void play_game() {
    printf("Welcome to Termle!\n");
    printf("Type '%s' to exit the game at any time.\n", EXIT_COMMAND);
	printf("Press Enter to start a new game.\n");
	
	char word[MAX_WORD_LENGTH];
	ProgramState program_state = RUNNING;

	while (program_state != EXITING) {
        wait_for_user_keypress();
        get_random_answer(word, MAX_WORD_LENGTH);
		int word_len = strlen(word);
        GameState game = create_new_game(word, word_len);
        printf("You have %d guesses to find the word of length %d.\n", TOTAL_GUESSES, word_len);
        if (game.error_type != NO_ERROR) {
            print_error(game.error_type);
            break;
        }

        program_state = play_round(game);
	}
}