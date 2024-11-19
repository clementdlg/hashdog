
int bruteforceAtk(char options[255], char algo[7], char target[255]);
int checkDigest(char algo[7], char target[255]);

int checkDigestCharset(char target[255]);
int dictAtk(char dict[255], char algo[7], char target[255]);

int sha_hash(char *str, char *hash);
int argParser(int argc, char** argv);
