#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <strings.h>

int dict_atk(char dict[255], char algo[7], char target[255]);
int sha_hash(char *str, char *hash);

int main(int argc, char** argv) {
	char dict[255];
	char target[255];
	char algo[7];

	if (argc != 5) {
		printf("This program performs attacks on a hashed password\n");
		printf("It takes the following arguments :\n");
		printf("1 - Method : 'dict', 'rainbow', 'bruteforce', \n");
		printf("2 - text file input. Required for 'dict' methods\n");
		printf("3 - Hashed password\n");
		printf("4 - Hashing algorithm (md5, sha256)\n");
		exit(0);
	}
	// store arguments
	strcpy(dict, argv[2]);
	strcpy(target, argv[3]);
	strcpy(algo, argv[4]);

	// choice tree
	if (strcmp(argv[1], "dict\n") != 0) {
		printf("Method : Dictionnary Attack\n");
		printf("Target : %s\n", target);
		printf("Algorithm : %s\n", algo);
		dict_atk(dict, algo, target);

	} else  if (strcmp(argv[1], "rainbow\n") != 0) {
		printf("Method : Rainbow table Attack\n");

	} else  if (strcmp(argv[1], "bruteforce\n") != 0) {
		printf("Method : Bruteforce Attack\n");

	}


	return 0;
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

int dict_atk(char dict[255], char algo[7], char target[255]){
	unsigned short bSize = 255;
	char buffer[bSize];
	unsigned int count = 0;

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
		count++;

		if (strcasecmp(algo, "sha256") == 0) {
			char* hash = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
			if (hash == NULL) {
				printf("Error: Memory allocation failed\n");
			}
			sha_hash(buffer, hash);
			if (strcasecmp(hash, target) == 0) {
				printf("Tried : %u words\n", count);
				printf("Found password : %s\n", buffer);
				return 0;
			}
		}

	}
	printf("Tried : %u words\n", count);
	printf("Found 0 match\n", count);
	fclose(pDict);
	return 0;
}
