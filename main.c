// external libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// internal libs
#include "checkDigest.h"
#include "dictAtk.h"

int dictAtk(char dict[255], char algo[7], char target[255]);
int bruteforceAtk(char options[255], char algo[7], char target[255]);
int sha_hash(char *str, char *hash);
int printHelp();

int main(int argc, char** argv) {
	// exit if argc is invalid
	if (argc != 5) {
		printHelp();
		exit(0);
	}

	char options[255];
	char target[255];
	char algo[7];

	// store arguments
	strcpy(options, argv[2]);
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

	printf("\n");
	// choice tree
	if (strcmp(argv[1], "dict") == 0) {
		printf("Method : Dictionary Attack\n");
		printf("Target : %s\n", target);
		printf("Algorithm : %s\n\n", algo);
		dictAtk(options, algo, target);

	} else  if (strcmp(argv[1], "rainbow") == 0) {

		printf("Method : Rainbow table Attack\n");

	} else  if (strcmp(argv[1], "bruteforce") == 0) {
		printf("Method : Bruteforce Attack\n");
		dictAtk(options, algo, target);

	} else { printf("Error : Unavailable method '%s'\n", argv[1]); }

	return 0;
}


// int bruteforceAtk(char options[255], char algo[7], char target[255]) {
// 	
// 	return 0;
// }

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

