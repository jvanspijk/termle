#ifndef COMMON_H
#define COMMON_H

#define MAX_WORD_LENGTH 10
#define TOTAL_GUESSES 6

typedef enum ErrorType {
    NO_ERROR = 0,
    WORD_TOO_LONG,
    WORD_TOO_SHORT,
    WORD_LENGTH_MISMATCH,
    WORD_NOT_IN_DICTIONARY,
} ErrorType;

void print_error(ErrorType err);

#endif // COMMON_H