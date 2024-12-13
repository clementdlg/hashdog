#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char validateCharset(char* key, char* charset);
char* cleanValue(char* value);
void trim(char* str);

int configParser(FILE* config) {

	unsigned int n = 0;
	unsigned short len = 200;
	int index;

	char line[len];
	char ret; // return value
	char alpha[] = "azertyuiopqsdfghjklmwxcvbn";
	char nums[] = "0123456789";

	char* key = malloc(sizeof(char) * 100);
	char* value = malloc(sizeof(char) * 100);
	char* pDelimiter;
	char* keyChars = malloc(sizeof(char) * 150);
	char* valueChars = malloc(sizeof(char) * 150);

	// creating key charset
	strcpy(keyChars, alpha);
	strcat(keyChars, ".\n");

	// creating value charset
	strcpy(valueChars, alpha);
	strcat(valueChars, nums);
	strcat(valueChars, "\\./\"");

	while(fgets(line, len, config)) {
		n++;
		strcpy(key, "");
		strcpy(value, "");
		
		// detect comments and empty lines
		if (line[0] == '#' || line[0] == '\n') {
			continue;
		}

		// checking for a '='
		pDelimiter = strchr(line, '=');
		if (pDelimiter == NULL) {
			printf("[Config Error](line %u) No key=value pair found in config\n", n);
			return 1;
		}
		// index of the '='
		index = pDelimiter - line;
		strncpy(key, line, index);

		// adding null-byte to end the string
		key[index] = '\0';

		// copy value
		strcpy(value, pDelimiter + 1);

		// removing comments and \n
		value = cleanValue(value);

		printf("%u:%s=%s\n", n, key, value);

		ret = validateCharset(key, keyChars);
		if (ret != -1) {
			printf("[Config Error](line %u) : Invalid char '%c' found in key '%s'\n", n, ret, key);
			return 1;
		}
		ret = validateCharset(value, valueChars);
		if (ret != -1) {
			printf("[Config Error](line %u) : Invalid char '%c' found in value '%s'\n", n, ret, value);
			return 1;
		}


	}
	free(key);
	free(keyChars);
	free(value);
	free(valueChars);
	return 0;
}

char validateCharset(char* key, char* charset) {
	unsigned short len;
	len = strlen(key);

	for(int i = 0; i < len; ++i) {
		if (strchr(charset, key[i]) == NULL) {
			return key[i];
		}
	}
	return -1;
}

char* cleanValue(char* value) {

	int len = strlen(value);
	char* buff = malloc(sizeof(char) * 100);
	int i;

	for (i = 0; i < len; ++i) {
		if (value[i] == '\n' || value[i] == '#') {
			buff[i] = '\0';
			break;
		}
		buff[i] = value[i];
		
	}
	return buff;
}

