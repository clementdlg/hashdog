#include <stdio.h>
#include <stdlib.h>
#include <string.h>

short validateCharset(char* line);

int configParser(FILE* config) {
	unsigned short len = 200;
	char line[len];
	char* key = malloc(sizeof(char) * 100);
	char* value = malloc(sizeof(char) * 100);
	char* pDelimiter;
	int delimiter;
	unsigned int n = 0;

	while(fgets(line, len, config)) {
		n++;
		// strcpy(key, "");
		// strcpy(value, "");
		
		// detect comments and empty lines
		if (line[0] == '#' || line[0] == '\n') {
			continue;
		}
		// if (validateCharset(line) == 1) {
		// 	printf("Error: Invalid charset in config file\n");
		// 	return 1;
		// }
		pDelimiter = strchr(line, '=');
		if (pDelimiter == NULL) {
			printf("[Config Error](line %u) No key=value pair found in config\n", n);
			return 1;
		}
		delimiter = pDelimiter - line;
		strncpy(key, line, delimiter);
		key[strlen(key) - 1] = '\0';
		strcpy(value, pDelimiter + 1);


		printf("%u:", n);
		printf("%s=%s\n", key, value);

	}
	return 0;
}

short validateValueCharset(char* line) {
	char charset[] = "0123456789azertyuiopqsdfghjklmwxcvbn\\./\"\n";
	unsigned short len;
	len = strlen(line);

	for(int i = 0; i < len; ++i) {
		if (strchr(charset, line[i]) == NULL) {
			printf("line[i] = %c \n", line[i]);
			return 1;
		}
	}
	return 0;
}
short validateKeyCharset(char* key) {
	char charset[] = "azertyuiopqsdfghjklmwxcvbn.\n";
	unsigned short len;
	len = strlen(key);

	for(int i = 0; i < len; ++i) {
		if (strchr(charset, key[i]) == NULL) {
			printf("key[i] = %c \n", key[i]);
			return 1;
		}
	}
	return 0;
}
