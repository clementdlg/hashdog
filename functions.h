int dictAtk(char dict[255], char algo[7], char target[255]);
int bruteforceAtk(char options[255], char algo[7], char target[255]);

int checkDigest(char* algo, char* password);
int checkDigestCharset(char* password);

int sha_hash(char *str, char *hash);
int argParser(int argc, char** argv, char args[], char* values[], unsigned short nbFlag);

char** configParser(FILE* config);
