// external libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// internal libs
#include "functions.h"

int printHelp();

//./main -m dict -o rockyou.txt -a sha256 -h CCAB7857A585ABC
int main(int argc, char** argv) {
	
	unsigned short nbFlag = 4;
	char* used = malloc(sizeof(char) * nbFlag + 1);
	char** values = malloc(sizeof(char*) * nbFlag);
	unsigned short algo, passw, options, method;
	// exit if no args
	if (argc == 1) {
		printHelp();
		exit(0);
	}

	argParser(argc, argv, used, values, nbFlag);

	// assigning indices
	algo = strchr(used, 'a') - used;
	passw = strchr(used, 'p') - used;
	method = strchr(used, 'm') - used;
	options = strchr(used, 'o') - used;

	// # check arguments
	// check algo
	if (strcasecmp(values[algo], "sha256") != 0 && strcasecmp(values[algo], "md5") != 0) {
		printf("Error : Invalid algorithm '%s'\n", algo);
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

