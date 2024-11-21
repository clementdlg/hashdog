// external libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// internal libs
#include "functions.h"

int printHelp();

int main(int argc, char** argv) {
	
	char args[] = {'a', 'o', 'm', 'p'};
	unsigned short nbFlag = sizeof(args);
	char** values = malloc(nbFlag * sizeof(char*));

	// temporary fallback values :
	char* fallback[] = {"sha256", "wordlists/rockyou.txt", "dict", ""};
	if (values == NULL) {
		printf("Error : Memory allocation failed\n");
	}

	// exit if no args
	if (argc == 1) {
		printHelp();
		exit(0);
	}

	argParser(argc, argv, args, values, nbFlag);

	// falling back on default values
	for (unsigned short i = 0; i < nbFlag; i++) {

		// if user did not provided an argument
		if (values[i] == NULL && strlen(fallback[i]) != 0) {

			// allocate memory for the value
			values[i] = malloc(strlen(fallback[i] + 1));
	
			if (values[i] == NULL) {
				printf("Error: Memory allocation failed\n");
			}

			// copy the default value to it
			strcpy(values[i], fallback[i]);
		}
	}
	//debug
	for (unsigned short i = 0; i < nbFlag; i++) {
		if (values[i] != NULL) {
			printf("values[%c] = %s\n", args[i], values[i]);
		}
	}

	/*
	// # check arguments
	// check algo
	if (strcasecmp(values[algo], "sha256") != 0 && strcasecmp(values[algo], "md5") != 0) {
		// printf("Error : Invalid algorithm '%s'\n", values[algo]);
		printf("invalid algo\n");
		exit(1);
	}

	// check digest length
	if (checkDigest(values[algo], values[passw]) != 0) {
		printf("Error : Invalid hash length\n");
		exit(1);
	}

	// check digest charset
	char ret = checkDigestCharset(values[passw]);
	if (ret != 0 ){
		printf("Error: Invalid character '%c' in hash\n", ret);
		exit(1);
	}

	printf("\n");
	// choice tree
	if (strcmp(values[method], "dict") == 0) {
		printf("Method : Dictionary Attack\n");
		printf("Target : %s\n", values[passw]);
		printf("Algorithm : %s\n\n", values[algo]);
		dictAtk(values[options], values[algo], values[passw]);

	} else  if (strcmp(values[method], "rainbow") == 0) {

		printf("Method : Rainbow table Attack\n");

	} else  if (strcmp(values[method], "bruteforce") == 0) {
		printf("Method : Bruteforce Attack\n");
		dictAtk(values[options], values[algo], values[passw]);

	} else { printf("Error : Unavailable method '%s'\n", values[method]); }

	return 0;
	*/
}


int printHelp() {
	printf("This program performs attacks on a hashed password\n");
	printf("It takes the following arguments :\n");
	printf("-m : Method\n");
	printf("    'dict', 'rainbow' or 'bruteforce'\n\n");

	printf("-p : Hashed password\n\n");
	printf("-a : Hashing algorithm ('md5' or 'sha256')\n\n");
	printf("-o : Options :\n");
	printf("  - For dict method, provide a wordlist file\n");
	printf("  - For bruteforce method, provide a charcter-set\n");
	printf("    'n' for numbers, 'l' for lowercase, 'u' for uppercase, 's' for symbols\n");
	printf("    Example : nsl for number + symbols + lowercase characters\n\n");

	return 0;
}

