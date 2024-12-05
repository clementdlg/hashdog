#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int configParser(FILE* config, long start, long end) {
	char c;
	int fBrace = 0;
	long startObj = -1;
	char* object;
	unsigned char startIsSet = 0;

	fseek(config, start, SEEK_SET);
	// printf("end = %ld\n", end); //debug

	// reading char
	while (ftell(config) < end) {
		c = fgetc(config);

		// printf("head = %ld, c = '%c'\n", ftell(config), c); //debug
		switch (c){
			// ignore whitespaces
			case ' ':
				break;
			case '{':
				fBrace++;
				// printf("fBrace++ : %d\n", fBrace);// debug

				// saving the offset from the first '{'
				if (startIsSet == 0) {
					startObj = ftell(config);
					startIsSet = 1;
				}
				break;
			case '}':
				fBrace--;
				// printf("fBrace-- : %d\n", fBrace);// debug
				if (fBrace < 0) {
					printf("Error: fBrace < 0");
					exit(1);
					// when we find the matching '}', we call parseObject
				} else if (fBrace == 0 && startObj != -1) {

					end = ftell(config);

					// debug printing of the object
					fseek(config, startObj, SEEK_SET);
					for (int i = 0; i < (int) (end - startObj) - 1; ++i) {
						printf("%c", fgetc(config));
					}
					printf("//end\n---------------\n");

					return configParser(config, startObj, end - 1);
				}
				break;
		}
	}
	// debug condition
	if (fBrace != 0) {
		printf("Error: %d closing-brace(s) not closed\n", fBrace);
		exit(1);
	}
	return 0;
}

int countC(FILE* pFile) {
	int count = 0;
	fseek(pFile, SEEK_SET, 0);
	while (fgetc(pFile) != EOF) {
		count ++;
	}
	return count;
}
