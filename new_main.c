#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/md5.h>


int sha_hash(char *str, char *hash);
int md5_hash(char *str, char *hash) ;

int main(int argc, char** argv) {
	char dict[255];
	char target[255];
        char method[255];
	unsigned short bSize = 255;
	char buffer[bSize];

	if (argc != 4) {
		printf("This program performs dictionnary attack on a hashed SHA-256  and md5 password\n");
		printf("It takes three arguments :\n");
		printf("1 - Method of hashing\n");
		printf("2 - Dictionnary file path\n");
		printf("3 - SHA-256-hashed password\n");
		exit(0);
	}
	// store arguments
	strcpy(method, argv[1]);
	strcpy(dict, argv[2]);
	strcpy(target, argv[3]);
        
        
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
                if (strcmp(method , "sha256")==0){
		char* hash = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
		if (hash == NULL) {
			printf("Error: Memory allocation failed\n");
		}

		sha_hash(buffer, hash);
		if (strcasecmp(hash, target) == 0) {
			printf("%s\n", buffer);
		}
                }
                else if(strcmp(method , "md5")==0){
                char* hash = malloc(MD5_DIGEST_LENGTH * 2 + 1);
		if (hash == NULL) {
			printf("Error: Memory allocation failed\n");
		}

		md5_hash(buffer, hash);
		if (strcasecmp(hash, target) == 0) {
			printf("%s\n", buffer);
		}
                }
                else{
                printf("non recognised method \n");
                return 1;
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

int md5_hash(char *str, char *hash) {
    unsigned char buff[MD5_DIGEST_LENGTH]; 

    // Calculer le hachage MD5
    MD5((unsigned char *)str, strlen(str), buff);

    // Convertir le hachage en une chaîne hexadécimale
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", buff[i]);
    }
    hash[MD5_DIGEST_LENGTH * 2] = '\0';  // Ajouter le caractère de fin de chaîne
    return 0;
}
