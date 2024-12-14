// external libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// internal libs
#include "functions.h"

// local functions
int printHelp();

// macros
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"

int main(int argc, char** argv) {
	
	char args[] = {'a', 'o', 'm', 'p'};
	unsigned short nbFlag = strlen(args);

	char** values = malloc(nbFlag * sizeof(char*));
	if (values == NULL) {
		printf("Error : Memory allocation failed\n");
	}

	char*** params;

	unsigned int* nv = malloc(sizeof(int));
	if (nv == NULL) {
		printf("Error: Memory allocation failed\n");
		exit(1);
	} 

	// check for config file
	FILE* config = fopen("config", "r");

	if (config == NULL) {
		printf("Error: No config file found\n");
		exit(1);
	} 
	params = configParser(config, nv);
	if (params == NULL) {
		fclose(config);
		return 1;
	}

	// exit if no args
	if (argc == 1) {
		printHelp();
		exit(0);
	}

	argParser(argc, argv, args, values, nbFlag);

	// falling back on config-file values
	if (values[0] == NULL) {
		values[0] = queryConfig(params, *nv, "attack.algorithm");
	}
	// TODO: : Create dedicated param for bruteforce charset
	if (values[1] == NULL) {
		values[1] = queryConfig(params, *nv, "path.wordlist");
	}
	if (values[2] == NULL) {
		values[2] = queryConfig(params, *nv, "attack.mode");
	}
	
	//debug print after fallback
	// printParams(params, *nv);
	// for (unsigned short i = 0; i < nbFlag; i++) {
	// 	printf("values[%c] = %s\n", args[i], values[i]);
	// }

	// # check arguments
	// check algo
	if (strcasecmp(values[0], "sha256") != 0 && strcasecmp(values[0], "md5") != 0) {
		printf("Error : Invalid algorithm '%s'\n", values[0]);
		exit(1);
	}

	// check digest length
	if (checkDigest(values[0], values[3]) >= 0) {
		printf("Error : Invalid hash length\n");
		exit(1);
	}

	// check digest charset
	char ret = checkDigestCharset(values[3]);
	if (ret != 0 ){
		printf("Error: Invalid character '%c' in hash\n", ret);
		exit(1);
	}

	printf("\n"); //debug
	// choice tree
	if (strcmp(values[2], "dict") == 0) {
		printf("Method : Dictionary Attack\n");
		printf("Target : %s\n", values[3]);
		printf("Algorithm : %s\n\n", values[0]);
		dictAtk(values[1], values[0], values[3]);

	} else  if (strcmp(values[2], "rainbow") == 0) {

		printf("Method : Rainbo table Attack\n");

	} else  if (strcmp(values[2], "bruteforce") == 0) {
		printf("Method : Bruteforce Attack\n");
		
		// bruteforce(values[1], values[0], unsigned int maxLength, unsigned int minLength) {

	} else { printf("Error : Unavailable method '%s'\n", values[2]); }

	fclose(config);

	//free params
	for (unsigned int i = 0; i < *nv; i++) {
		free(params[0][i]);
	}
	free(params[0]);
	free(params[1]);
	free(params);
	return 0;
}


int printHelp() {
	    printf(BOLD YELLOW "This program performs attacks on a hashed passord\n" RESET);
    printf(BOLD YELLOW "It takes the following arguments :\n" RESET);

    printf(BOLD GREEN "-m : Method\n" RESET);
    printf("    'dict', 'rainbow' or 'bruteforce'\n\n" );

    printf(BOLD GREEN "-p : Hashed password\n\n" RESET);
    printf("  Example : '5E884898DA28047151D0E56F8DC6292773603D0D6AABBDD62A11EF721D1542D8'\n\n");

    printf(BOLD GREEN "-a : Hashing algorithm\n" RESET);
    printf("  Currently supported : 'md5' or 'sha256'\n\n");

    printf(BOLD GREEN "-o : Options :\n" RESET);
    printf("  - For dict method, provide a wordlist file\n");
    printf("  - For bruteforce method, provide a character-set\n");
    printf("    'n' for numbers, 'l' for lowercase, 'u' for uppercase, 's' for symbols\n");
    printf("    Example : nsl for number + symbols + lowercase characters\n\n");

	return 0;
}

