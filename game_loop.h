#ifndef GAME_LOOP_H	
#define GAME_LOOP_H
#include "game_state.h"

#define EXIT_COMMAND "/EXIT"

typedef enum ProgramState {
	RUNNING,
	EXITING
} ProgramState;

ProgramState play_round(GameState game);

void play_game();

#endif // GAME_LOOP_H