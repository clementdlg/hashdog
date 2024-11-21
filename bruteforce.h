#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

// Définition des caractères possibles pour chaque type
#define LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define SYMBOLS "!@#$%^&*()_+"
#define NUMBERS "0123456789"

void generateCombinations(const char *format, char *current, int position, const char *target);
void bruteForce(const char *format, const char *target);

#endif