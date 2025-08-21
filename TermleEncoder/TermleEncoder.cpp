#include <stdio.h>
// Encode given word list
// Algorithm:
// 1. Read the word list from a file
// 2. Every letter is represented by a number (0-25)
// 3. The number is stored in a 5 bit binary representation
// 4. Because it's sorted, we can calculate the delta of the next word from the previous word
// 4a. Compress the word into 25-bits like the previous steps
// 4b. Subtract the current value from the previous value
// 5. We store the deltas in an array and then write the array to a file

// Variable length encoding:
// First 5 bits where every bit represents wether the character has changed or not, then 5 bits per changed letter.

enum Bit {
	zero = 0,
	one = 1
};

void compress_word_difference(enum Bit previous_word_bits[25], enum Bit word_bits[25], enum Bit result[25])
{
	// Zero initialize result
	for (int i = 0; i < 25; ++i) {
		result[i] = zero;
	}

	
	for (int i = 0; i < 25; ++i) {

	}

}

void char_to_binary(char c, enum Bit bits[5]) {
	if (c < 'a' || c > 'z') {
		printf("The value of this character is invalid.");
		return;
	}
	const int bit_arr_size = 5;
	int char_value = c - 'a';

	for (int i = 0; i < bit_arr_size; ++i) {
		int mask = 1 << (bit_arr_size - 1 - i);
		bits[i] = (char_value & mask) ? one : zero;
	}
}

void encode_word(char* word, enum Bit word_bits[25])
{
	const int word_len = 5;
	for (int i = 0; i < word_len; ++i) {
		enum Bit char_bits[5];
		char c = word[i];
		char_to_binary(c, char_bits);
		for (int j = 0; j < 5; ++j) {
			word_bits[j + (i * 5)] = char_bits[j];
		}
	}
}

int bits_to_int(enum Bit word_bit[25]) {
	const int bit_arr_size = 25;
	int word_value = 0;
	for (int i = 0; i < bit_arr_size; ++i) {
		enum Bit bit = word_bit[i];
		int mask = 1 << (bit_arr_size - 1 - i);
		int bit_value = bit == 1 ? mask : 0;
		word_value += bit_value;
	}
	return word_value;
}

void int_to_bits(int num, enum Bit bits[25]) {
	const int bit_arr_size = 25;
	for (int i = 0; i < bit_arr_size; ++i) {
		int mask = 1 << (bit_arr_size - 1 - i);
		bits[i] = (num & mask) ? one : zero;
	}
}

int calculate_difference(enum Bit word_bit1[25], enum Bit word_bit2[25]) {
	int word1_val = bits_to_int(word_bit1);
	int word2_val = bits_to_int(word_bit2);
	int difference = word2_val ^ word1_val;
	return difference;
}

void word_xor(enum Bit word1_bit[25], enum Bit word2_bit[25], enum Bit bit_result[25]) {
	for (int i = 0; i < 25; ++i) {
		bit_result[i] = (word1_bit[i] != word2_bit[i]) ? one : zero;
	}
}

void print_word_encoded(const char* word, enum Bit word_bits[25]) {
	printf("Original word: ");
	printf(word);
	printf("\n");
	printf("Encoded: ");
	for (int i = 0; i < 25; ++i) {
		switch (word_bits[i]) {
			case zero:
				printf("0");
				break;
			case one:
				printf("1");
				break;
		}
		if ((i+1) % 5 == 0 && i != 0) {
			printf(" ");
		}
	}
	printf("\n");

	int word_value = bits_to_int(word_bits);
	printf("Int value: ");
	printf("%i", word_value);
	printf("\n");	
}

void process_word_list(int word_list_len) {

	// for word in word list: 
	// encode the word and store it as 5 bits
	// look at the previous encoded word and xor the two
	// in a variable encoded list you put the xor result (0 or 1) per character (if it changed or not)
	// then you put the 5 bits for each of the letters that changed compared to the previous word

	// at the end you delete the normal encoded list and save the variable encoded list
	char* curr_word; //tODO: initialize the first word.
	Bit curr_word_bits[25];
	char* next_word;
	Bit next_word_bits[25];

	Bit changed_letters_bits[5];

	for (int i = 1; i < word_list_len - 1; ++i) {		
		encode_word(curr_word, curr_word_bits);
		next_word; // TODO: select next word.
		encode_word(next_word, next_word_bits);
		Bit words_bits_xor[25];
		word_xor(curr_word_bits, next_word_bits, words_bits_xor);
		curr_word = next_word;
		// Save xor result: reduce 5 bits of a letter xor to 1 bit each
		// then, save the relevant bits of the letters that need to be changed.
	}
}


int main() {
	char word[6] = "aback";
	enum Bit word_bits[25];
	encode_word(word, word_bits);
	print_word_encoded(word, word_bits);
	
	char word2[6] = "abase";
	enum Bit word_bits2[25];
	encode_word(word2, word_bits2);
	print_word_encoded(word2, word_bits2);	

	int dif = calculate_difference(word_bits, word_bits2);
	printf("Difference: %i", dif);
	printf("\nXOR: ");
	enum Bit xor_result[25];
	word_xor(word_bits, word_bits2, xor_result);
	for (int i = 0; i < 25; ++i) {
		switch (xor_result[i]) {
		case zero:
			printf("0");
			break;
		case one:
			printf("1");
			break;
		}
		if ((i + 1) % 5 == 0 && i != 0) {
			printf(" ");
		}
	}

	// It can be further compressed by variable length encoding: first 5 bits represent which letters have changed and then per changed letter 5 bits.


	return 0;
}