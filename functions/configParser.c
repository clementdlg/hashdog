#include <stdio.h>

int configParser(FILE* config) {
	unsigned short maxLineLen = 255;
	char buffer[maxLineLen];

	while (fgets(buffer, maxLineLen, config) != NULL) {
		printf("%s", buffer);
	}
	return 0;
}
