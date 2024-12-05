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

	// if ( // something ) { // break condition }
	// reading char
	while ((c = fgetc(config)) != EOF) {
		// printf("tour n° : %ld\n", ftell(config));
		switch (c){
			// ignore whitespaces
			case ' ':
				break;
			case '{':
				fBrace++;
				// saving the offset from the first '{'
				if (startIsSet == 0) {
					startObj = ftell(config);
					startIsSet = 1;
				}
				break;
			case '}':
				fBrace--;
				if (fBrace < 0) {
					printf("Error: fBrace < 0");
					exit(1);
				// when we find the matching '}', we call parseObject
				} else if (fBrace == 0 && startObj != -1) {

					end = ftell(config);

					// debug printing of the object
					fseek(config, startObj, SEEK_SET);
					for (int i = 0; i < (int) (end - startObj); ++i) {
						printf("%c", fgetc(config));
					}
					return configParser(config, startObj, end);
				break;
			}
		}
	}
	// debug condition
	if (fBrace != 0) {
		printf("Error: %d closing-brace(s) not closed\n", fBrace);
		exit(1);
	} else {
		printf("Info : No JSON object found\n");
	}
	return 0;
}

