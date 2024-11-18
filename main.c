#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

int dict_atk(char dict[255], char algo[7], char target[255]);
int checkDigestCharset(char target[255]);
int checkDigest(char algo[7], char target[255]);
int sha_hash(char *str, char *hash);
int printHelp();

int main(int argc, char** argv) {
	// exit if argc is invalid
	if (argc != 5) {
		printHelp();
		exit(0);
	}

	char dict[255];
	char target[255];
	char algo[7];


	// store arguments
	strcpy(dict, argv[2]);
	strcpy(target, argv[3]);
	strcpy(algo, argv[4]);

	// # check arguments
	// check algo
	if (strcasecmp(algo, "sha256") != 0 && strcasecmp(algo, "md5") != 0) {
		printf("Error : Invalid algorithm '%s'\n", algo);
		exit(1);
	}

	// check digest length
	if (checkDigest(algo, target) != 0) {
		printf("Error : Invalid hash length\n");
		exit(1);
	}

	// check digest charset
	char ret = checkDigestCharset(target);
	if (ret != 0 ){
		printf("Error: Invalid character '%c' in hash\n", ret);
		exit(1);
	}

	// choice tree
	if (strcmp(argv[1], "dict") == 0) {
		// printf("Method : Dictionary Attack\n");
		// printf("Target : %s\n", target);
		// printf("Algorithm : %s\n", algo);
		dict_atk(dict, algo, target);

	} else  if (strcmp(argv[1], "rainbow") == 0) {

		printf("Method : Rainbow table Attack\n");

	} else  if (strcmp(argv[1], "bruteforce") == 0) {

		printf("Method : Bruteforce Attack\n");

	} else { printf("Error : Unavailable method '%s'\n", argv[1]); }

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
	char* hash;
	// setting a ptr to the data
	FILE *pDict = fopen(dict, "r");

	// avoid null ptr dereference
	if (pDict == NULL) {
		printf("Error: wordlist '%s' doesn't exist\n", dict);
		exit(1);
	}

	while (fgets(buffer, bSize, pDict) != NULL) {
		//remove '\n' that prevent matching
		buffer[strlen(buffer) - 1] = '\0';
		count++;

		if (strcasecmp(algo, "sha256") == 0) {
			hash = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
			if (hash == NULL) {
				printf("Error: Memory allocation failed\n");
			}
			sha_hash(buffer, hash);
		}
		if (strcasecmp(hash, target) == 0) {
			printf("Tried : %u words\n", count);
			printf("Found password : %s\n", buffer);
			free(hash);
			return 0;
		}
		free(hash);

	}
	printf("Tried : %u words\n", count);
	printf("Found 0 match\n");
	fclose(pDict);
	return 0;
}

int bruteforce_atk() {
	return 0;
}

int printHelp() {
	printf("This program performs attacks on a hashed password\n");
	printf("It takes the following arguments :\n");
	printf("1] Method :\n");
	printf("    'dict', 'rainbow' or 'bruteforce'\n");

	printf("2] Method Options :\n");
	printf("  - For dict method, provide a wordlist file\n");
	printf("  - For bruteforce method, provide a charcter-set\n");
	printf("    'n' for numbers, 'l' for lowercase, 'u' for uppercase, 's' for symbols\n");
	printf("    Example : nsl for number + symbols + lowercase characters\n");

	printf("3] Hashed password\n");
	printf("4] Hashing algorithm ('md5' or 'sha256')\n");
	return 0;
}

/*
 * Input : hashing algorithm and target hash
 * Output: Either  or 0
 */
int checkDigest(char algo[7], char target[255]) {

	unsigned short lenTarget = strlen(target);

	if (strcasecmp(algo, "sha256") == 0 && lenTarget != 64) {
		return lenTarget;
	}
	if (strcasecmp(algo, "md5") == 0 && lenTarget != 32) {
		return lenTarget;
	}
	
	return 0;
}

/*
 * Input : target string
 * Output: Either invalid character or 0
 */
int checkDigestCharset(char target[255]) {

	const char *hashCharset = "0123456789abcdefABCDEF";
	const unsigned short lenHashCharset = 22;
	unsigned short lenTarget = strlen(target);

	// loop over the target
	for (unsigned short i = 0; i < lenTarget; ++i) {
		char isValid = 0;

		// loop over the allowed charset
		for (unsigned short j = 0; j < lenHashCharset; ++j) {
			if (target[i] == hashCharset[j]) {
				isValid = 1;
			}
		}
		if (isValid == 0) {
			return target[i];
		}
	}
	return 0;
}
