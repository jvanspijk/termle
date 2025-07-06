#ifndef CONSOLE_VIEW_H	
#define CONSOLE_VIEW_H
#include "game_state.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void wait_for_user_keypress();
void clear_console();
void read_guess(char* buffer);
void print_game_state(const GameState state, int animation_delay_ms);

#endif // CONSOLE_VIEW_H
