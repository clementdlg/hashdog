#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char validateValueCharset(char* line);
char validateKey(char* line);
char* cleanValue(char* value);

int configParser(FILE* config) {
	unsigned short len = 200;
	char line[len];
	char* key = malloc(sizeof(char) * 100);
	char* value = malloc(sizeof(char) * 100);
	char* pDelimiter;
	int index;
	char ret;
	unsigned int n = 0;

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
		ret = validateKey(key);
		if (ret != -1) {
			printf("[Config Error](line %u) : Invalid char '%c' found in key '%s'\n", n, ret, key);
			return 1;
		}
		// ret = validateValueCharset(value);
		// if (ret != -1) {
		// 	printf("[Config Error](line %u) : Invalid char '%c' found in value '%s'\n", n, ret, value);
		// 	return 1;
		// }


	}
	return 0;
}

char validateKey(char* key) {
	char charset[] = "azertyuiopqsdfghjklmwxcvbn.\n";
	unsigned short len;
	len = strlen(key);

	for(int i = 0; i < len; ++i) {
		if (strchr(charset, key[i]) == NULL) {
			return key[i];
		}
	}
	return -1;
}
char validateValueCharset(char* value) {
	char charset[] = "0123456789azertyuiopqsdfghjklmwxcvbn\\./\"\n";
	unsigned short len;
	len = strlen(value);

	for(int i = 0; i < len; ++i) {
		if (strchr(charset, value[i]) == NULL) {
			return value[i];
		}
	}
	return -1;
}

char* cleanValue(char* value) {

	int len = strlen(value);
	char* buff = malloc(sizeof(char) * 100);

	for (int i = 0; i < len; ++i) {
		if (value[i] == '\n' || value[i] == '#') {
			break;
		}
		buff[i] = value[i];
		
	}
	return buff;
}
