#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	char dict[255];
	char target[255];

	unsigned short bSize = 255;
	char buffer[bSize];

	if (argc != 3) {
		printf("This program performs dictionnary attack on a hashed SHA-256 password\n");
		printf("It takes two arguments :\n");
		printf("1 - Dictionnary file path\n");
		printf("2 - SHA-256-hashed password\n");
		exit(0);
	}
	// store arguments
	strcpy(dict, argv[1]);
	strcpy(target, argv[2]);

	// setting a ptr to the data
	FILE *pDict = fopen(dict, "r");

	// avoid null ptr dereference
	if (pDict == NULL) {
		printf("Error: '%s' doesn't exist.\n", dict);
		exit(1);
	}

	while (fgets(buffer, bSize, pDict) != NULL) {
		//remove '\n' that prevent matching
		buffer[strlen(buffer) - 1] = '\0';

		if (strcmp(buffer, target) == 0) {
			printf("%s\n", buffer);
		}
	}
	
	fclose(pDict);
}
