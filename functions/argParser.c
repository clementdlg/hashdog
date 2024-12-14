#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Input : main function argument-count and argument-value
 *		   array of strings (type char**) and max number of flags
 *
 * Output : int 0
 */
int argParser(int argc, char** argv, char args[], char* values[], unsigned short nbFlag) {
	unsigned short flagCount = 0;
	unsigned short valIndex;
	char* used = malloc(sizeof(char) * nbFlag + 1);

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

			// the position of the letter inside the 'args' string
			valIndex = strchr(args, argv[i][1]) - args;

			// allocate the size of the argument (argv[i + 1])
			values[valIndex] = (char*) malloc(strlen(argv[i + 1]) + 1);
			if (values[valIndex] == NULL) {
				printf("Error : Memory allocation failed\n");
			}

			// copy the value
			strcpy(values[valIndex], argv[i + 1]);

			flagCount++;

			// break if all flags are already used
			if (flagCount == nbFlag) { 
				break;
			}
		}
	}

	return 0;
}

char* argVal(char c, char args[], char** argValues) {
	int len = strlen(args);

	for (unsigned int i = 0; i < len; ++i) {
		if (args[i] == c) {
			return argValues[i];
		}
	}
	return NULL;
}
