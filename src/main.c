#include <stdio.h>
#include <string.h>

#include "guesses.h"
#include "answers.h"

#define LEN(x) (sizeof(x) / sizeof(x[0]))

// Working buffer for possible answers indexed by depth
static char answers[6][LEN(all_answers)][6];
// Working buffer for possible colors, 1 bit for each depth
static unsigned int colors[243];

unsigned char find_color(const char guess[6], const char answer[6]) {
	unsigned char color[5] = {0};
	unsigned char letters[26] = {0};
	for (int i = 0; i < 5; ++i) {
		if (guess[i] == answer[i]) {
			color[i] = 2;
			letters[(int)(guess[i] - 'A')]++;
		}
	}
	for (int i = 0; i < 5; ++i) {
		if (color[i] == 2)
			continue;
		int n = 0;
		for (int j = 0; j < 5; ++j) {
			if (answer[j] == guess[i])
				n++;
		}
		if (n > letters[(int)(guess[i] - 'A')]) {
			color[i] = 1;
			letters[(int)(guess[i] - 'A')]++;
		}
	}	
	return color[4] + color[3] * 3 + color[2] * 9 + color[1] * 27 + color[0] * 81;
}

void find_best_word(char answers[][6], size_t n_answers, char guess[6]) {
	if (n_answers <= 2) {
		memcpy(guess, answers[0], 6);
		return;
	}

	unsigned int best_elims = 0;
	static unsigned int color_freqs[243];
	static unsigned char colors[LEN(all_answers)];
	for (size_t i = 0; i < LEN(guesses); ++i) {
		memset(color_freqs, 0, sizeof(color_freqs));
		unsigned int elims = 0;
		for (size_t j = 0; j < n_answers; ++j) {
			unsigned char color = find_color(guesses[i], answers[j]);
			colors[j] = color;
			color_freqs[color]++;
		}
		for (size_t color = 0; color < LEN(color_freqs); ++color) {
			if (color_freqs[color] == 0)
				continue;
			for (size_t k = 0; k < n_answers; ++k) {
				if (colors[k] != color)
					elims += color_freqs[color];
			}
		}

		if (i == 0 || elims > best_elims) {
			memcpy(guess, guesses[i], 6);
			best_elims = elims;
		}
	}
}

void generate_tree(size_t n_answers, size_t depth) {
	if (n_answers == 1) {
		printf("\"%s\",", answers[depth][0]);
		return;
	}
	char guess[6];
	find_best_word(answers[depth], n_answers, guess);
	printf("{\"%s\":{", guess);

	for (size_t i = 0; i < LEN(colors); ++i)
		colors[i] &= ~(1 << depth);
	unsigned char color;
	size_t len;
	for (size_t i = 0; i < n_answers; ++i) {
		color = find_color(guess, answers[depth][i]);
		if (colors[color] & 1 << depth)
			continue;
		colors[color] |= 1 << depth;
		printf("\"%d%d%d%d%d\":",
				color / 81,
				color / 27 % 3,
				color / 9 % 3,
				color / 3 % 3,
				color % 3
		);
		len = 0;
		for (size_t j = 0; j < n_answers; j++) {
			if (find_color(guess, answers[depth][j]) == color)
				memcpy(answers[depth + 1][len++], answers[depth][j], 6);
		}
		generate_tree(len, depth + 1);
	}
	printf("}},");
}

int main(void) {
	memcpy(answers[0], all_answers, sizeof(all_answers));
	generate_tree(LEN(all_answers), 0);
    return 0;
}
