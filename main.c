// external libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// internal libs
#include "functions.h"

// local functions
int printHelp();


int main(int argc, char** argv) {
	
	char args[] = {'a', 'd', 'm', 'p', 'c', 's', 't', 'x', 'n'}; // defines possible arguments
	unsigned short nbFlag = strlen(args);

	char*** params; // hold the config and current args

	char** argValues = malloc(nbFlag * sizeof(char*)); // store all argument values
	if (argValues == NULL) {
		printf("Error : Memory allocation failed\n");
	}


	unsigned int* nv = malloc(sizeof(int)); // number of params
	if (nv == NULL) {
		printf("Error: Memory allocation failed\n");
		exit(1);
	} 

	// exit if no args
	if (argc == 1) {
		printHelp();
		exit(0);
	}

	// initializing config-file
	FILE* config = fopen("config", "r");

	if (config == NULL) {
		printf("Error: No config file found\n");
		exit(1);
	} 

	// initializing params from config-file
	params = configParser(config, nv);
	if (params == NULL) {
		fclose(config);
		return 1;
	}

	// parsing arguments
	argParser(argc, argv, args, argValues, nbFlag);

	// fallback to default values
	if (fallbackToConfig(args, argValues, params, *nv) != 0) {
		return 1;
	}
	
	//debug print after fallback
	// printParams(params, *nv);
	// for (unsigned short i = 0; i < nbFlag; i++) {
	// 	printf("-%c = %s\n", args[i], argValues[i]);
	// }

	// validating arguments
	if (argValidate(args, argValues) != 0) {
		return 1;
	}

	printf("\n"); //debug

	// Mode
	if (strcmp(*argVal('m', args, argValues), "dict") == 0) {

		printf("Method : Dictionary Attack\n");
		printf("Target : %s\n", argValues[3]);
		printf("Algorithm : %s\n\n", argValues[0]);
		dictAtk(argValues[1], argValues[0], argValues[3]);

	} else  if (strcmp(*argVal('m', args, argValues), "rainbow") == 0) {

		printf("Method : Rainbow table Attack\n");

	} else  if (strcmp(*argVal('m', args, argValues), "bruteforce") == 0) {
		printf("Method : Bruteforce Attack\n");
		
		bruteforce(*argVal('c', args, argValues), *argVal('a', args, argValues), *argVal('x', args, argValues), *argVal('n', args, argValues), *argVal('p', args, argValues));

	} else { printf("Error : Unavailable method '%s'\n", argValues[2]); }

	// for Mr. Sananes
	fclose(config);

	free(argValues);

	//free params
	for (unsigned int i = 0; i < *nv; i++) {
		free(params[0][i]);
	}
	free(params[0]);
	free(params[1]);
	free(params);
	free(nv);
	return 0;
}


int printHelp() {
	// char args[] = {'a', 'd', 'm', 'p', 'c', 's', 't', 'x', 'n'}; // defines possible arguments
	printf(BOLD YELLOW "This program performs attacks on a hashed passord\n" RESET);
	printf(BOLD YELLOW "It takes the following arguments :\n" RESET);

	printf(BOLD GREEN "-p : Hashed password\n\n" RESET);
	printf("  Example : '5E884898DA28047151D0E56F8DC6292773603D0D6AABBDD62A11EF721D1542D8'\n\n");

	printf(BOLD GREEN "-m : Methode\n" RESET);
	printf("    'dict', 'bruteforce'\n\n" );

	printf(BOLD GREEN "-a : Hashing algorithm\n" RESET);
	printf("  Currently supported : 'md5' or 'sha256'\n\n");

	printf(BOLD GREEN "-d : Dictionnary [dict]\n" RESET);
	printf("  - Provides a wordlist file for a dictionnary attack\n\n");

	printf(BOLD GREEN "-c : Character-set [bruteforce]\n" RESET);
	printf("  - Provides a character set for a bruteforce attack\n");
	printf("  - 'n' : numbers [0-9]\n");
	printf("  - 'l' : lowercase letters [abc]\n");
	printf("  - 'u' : uppercase letters [ABC]\n");
	printf("  Example: 'ln' for lowercase + numbers\n\n");

	printf(BOLD GREEN "-s : Salt\n" RESET);
	printf("  - allows to use a salt to try on the password\n\n");

	printf(BOLD GREEN "-n : Minimum length [bruteforce]\n" RESET);
	printf("  - When in bruteforce mode, this is the base number of characters\n\n");

	printf(BOLD GREEN "-x : Max length [bruteforce]\n" RESET);
	printf("  - When in bruteforce mode, this is the max number of characters\n\n");

	return 0;
}

