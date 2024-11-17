#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	char dict[255];
	char target[255];

	unsigned short bSize = 255;
	char buffer[bSize];

	printf("This program performs dictionnary attack on a hashed SHA-256 password\n");
	printf("Insert path of dictionnary txt file : ");
	scanf("%254s", dict);

	printf("Insert hashed password : ");
	scanf("%254s", target);

	// setting a ptr to the data
	FILE *pDict = fopen(dict, "r");

	// avoid null ptr dereference
	if (pDict == NULL) {
		printf("Error: '%s' doesn't exist.\n", dict);
		exit(1);
	}

	while (fgets(buffer, bSize, pDict) != NULL) {
		buffer[strlen(buffer) - 1] = '\0';

		if (strcmp(buffer, target) == 0) {
			printf("%s\n", buffer);
		}
	}
	
	fclose(pDict);
}
