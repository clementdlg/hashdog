#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

int sha_hash(char *str, char *hash);

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

		char* hash = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
		if (hash == NULL) {
			printf("Error: Memory allocation failed\n");
		}

		sha_hash(buffer, hash);

		if (strcasecmp(hash, target) == 0) {
			printf("%s\n", buffer);
		}
	}
	
	fclose(pDict);
}

int sha_hash(char *str, char *hash) {
    unsigned char buff[SHA256_DIGEST_LENGTH]; 

    SHA256((unsigned char *)str, strlen(str), buff);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", buff[i]);
    }
    hash[SHA256_DIGEST_LENGTH * 2] = '\0';
    return 0;
}
