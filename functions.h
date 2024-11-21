
int bruteforceAtk(char options[255], char algo[7], char target[255]);
int checkDigest(char algo[7], char target[255]);

int checkDigestCharset(char target[255]);
int dictAtk(char dict[255], char algo[7], char target[255]);

int sha_hash(char *str, char *hash);
int argParser(int argc, char** argv, char* used, char** values, unsigned short nbFlag);

//md5
#pragma once
#include <stdint.h>

typedef struct {
	uint32_t a, b, c, d;
} md5_context;

void md5_init(md5_context* ctx);
void md5_digest(md5_context* ctx, void* buffer, size_t size);
void md5_output(md5_context* ctx, uint8_t out[16]);
