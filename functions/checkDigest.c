#include <string.h>
/*
 * Input : hashing algorithm and target hash
 * Output: Either  or 0
 */
int checkDigest(char algo[7], char target[255]) {

	unsigned short lenTarget = strlen(target);

	if (strcasecmp(algo, "sha256") == 0 && lenTarget != 64) {
		return lenTarget;
	}
	if (strcasecmp(algo, "md5") == 0 && lenTarget != 32) {
		return lenTarget;
	}
	
	return 0;
}

/*
 * Input : target string
 * Output: Either invalid character or 0
 */
int checkDigestCharset(char target[255]) {

	const char *hashCharset = "0123456789abcdefABCDEF";
	const unsigned short lenHashCharset = 22;
	unsigned short lenTarget = strlen(target);

	// loop over the target
	for (unsigned short i = 0; i < lenTarget; ++i) {
		char isValid = 0;

		// loop over the allowed charset
		for (unsigned short j = 0; j < lenHashCharset; ++j) {
			if (target[i] == hashCharset[j]) {
				isValid = 1;
			}
		}
		if (isValid == 0) {
			return target[i];
		}
	}
	return 0;
}
