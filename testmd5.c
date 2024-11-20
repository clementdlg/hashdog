#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

int hex_digit_to_int(char c) {
	switch (c) {
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		return c - '0';
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
		return c + 10 - 'A';
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
		return c + 10 - 'a';
	default: assert(0 && "invalid hex character");
	}
	return -1;
}

void hex_string_to_bytes(char* hex, uint8_t bytes[16]) {
	assert(strlen(hex) == 32);
	int j = 0;
	for (int i = 0; i < 32; i+= 2) {
		bytes[j] = 16 * hex_digit_to_int(hex[i])
			+ hex_digit_to_int(hex[i+1]);
		j++;
	}
}

void print_bytes(uint8_t bytes[16]) {
	for (int i = 0; i < 16; i++) {
		printf("%02X", bytes[i]);
	}
	printf("\n");
}

void test(char* input, char* expected) {
	md5_context ctx;
	md5_init(&ctx);
	md5_digest(&ctx, input, strlen(input));

	uint8_t md5_actual[16] = {0};
	md5_output(&ctx, md5_actual);

	uint8_t md5_expected[16] = {0};
	hex_string_to_bytes(expected, md5_expected);

	if (memcmp(md5_actual, md5_expected, 16) != 0) {
		printf("test:     %s\n", input);
		printf("actual:   "); print_bytes(md5_actual);
		printf("expected: "); print_bytes(md5_expected);
		assert(0 && "test cases failed");
	}
}

int main() {
	test("a", "0cc175b9c0f1b6a831c399e269772660");
	

	printf("All tests passed!\n");
	
	
	}
