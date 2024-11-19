#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int argParser(int argc, char** argv) {
	unsigned short nbFlag = 4;
	char* args = "aomp";
	char* used = malloc(sizeof(char) * nbFlag + 1);
	unsigned int flagCount = 0;

	// store the values
	char* values[nbFlag];

	if (used == NULL) {
		printf("Error: Memory allocation failed\n");
		exit(1);
	}

	// retrieve the valid flags
	for (unsigned short i = 1; i < argc - 1; ++i) {

		if (argv[i][0] == '-' &&		// must start with "-"
			strlen(argv[i]) == 2  &&		// must be of length 2 
			strchr(args, argv[i][1]) &&		// 2nd char must be valid flag 
			strchr(used, argv[i][1]) == NULL &&		// 2nd char must not be used already
			argv[i + 1][0] != '-' ) {		// next arg must not be a flag

			// add flag to 'used'
			strcat(used, &argv[i][1]);

			// copy value to array
			values[flagCount] = (char*) malloc(strlen(argv[i + 1]) + 1);
			strcpy(values[flagCount], argv[i + 1]);

			// increment index
			flagCount++;
			// break if all flags are already used
			if (flagCount == nbFlag) { 
				break;
			}
		}
	}
	// debug
	for (int i = 0; i < strlen(used); ++i) {
		printf("%c : %s\n", used[i], values[i]);
	}

	return 0;
}

