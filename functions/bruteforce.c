#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int bruteforce(char* charset, char* algo, unsigned int maxLength, unsigned int minLength) {
	char* pass = malloc(sizeof(char) * minLength);

	// charsets
	char* special = "¹~#{[|`\\^@]}$£%*µ?,.;/:§!<>";
	char* lower = "azertyuiopqsdfghjklmwxcvbn";
	char* upper = "AZERTYUIOPQSDFGHJKLMWXCVBN";
	char* num = "0123456789";

	char* sumchar = malloc(sizeof(char) * 90);
	char* used = malloc(sizeof(char) * 4);
	int len = strlen(charset);

	for (int i = 0; i < len; ++i) {
		switch(charset[i]) {
			case 's':
				// if 's' is not already used
				if (strchr(used, 's') == NULL) {

					// add special to the charset
					strcat(sumchar, special);

					// add 's' to used
					strcat(used, "s");
				}
				break;
			case 'l':
				// if 's' is not already used
				if (strchr(used, 'l') == NULL) {

					// add lower to the charset
					strcat(sumchar, lower);

					// add 's' to used
					strcat(used, "l");
				}
				break;
			case 'u':
				// if 's' is not already used
				if (strchr(used, 'u') == NULL) {

					// add upper to the charset
					strcat(sumchar, upper);

					// add 's' to used
					strcat(used, "u");
				}
				break;
			case 'n':
				// if 's' is not already used
				if (strchr(used, 'n') == NULL) {

					// add num to the charset
					strcat(sumchar, num);

					// add 's' to used
					strcat(used, "n");
				}
				break;
			default:
				printf("Error: Invalid charset character '%c'\n", charset[i]);
		}
	}

	printf("sumchar = %s\n", sumchar);
	return 1;
}
