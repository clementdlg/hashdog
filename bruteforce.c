#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bruteforce.h"


// Fonction récursive pour générer toutes les combinaisons
void generateCombinations(const char *format, char *current, int position, const char *target) {
    // Si on a généré une chaîne complète
    if (position == strlen(format)) {
        current[position] = '\0';  // Terminer la chaîne
        printf("Combinaison actuelle : %s\n", current);  // Afficher la combinaison

        // Vérifier si c'est le mot cible
        if (strcmp(current, target) == 0) {
            printf("Mot trouvé : %s\n", current);
            exit(0);  // Quitter une fois trouvé
        }
        return;
    }

    // Récupérer le type actuel
    char type = format[position];
    const char *charset = NULL;

    // Assigner le bon charset
    switch (type) {
        case 'i': charset = LOWERCASE; break;
        case 'u': charset = UPPERCASE; break;
        case 's': charset = SYMBOLS; break;
        case 'n': charset = NUMBERS; break;
        default:
            printf("Format invalide.\n");
            exit(1);
    }

    // Parcourir toutes les options pour ce type
    for (int i = 0; charset[i] != '\0'; i++) {
        current[position] = charset[i];  // Ajouter un caractère au mot actuel
        generateCombinations(format, current, position + 1, target);  // Rappel récursif
    }
}

// Fonction brute force principale
void bruteForce(const char *format, const char *target) {
    int size = strlen(format);
    char *current = malloc(size + 1);  // Chaîne pour stocker la combinaison actuelle

    if (!current) {
        printf("Erreur d'allocation mémoire.\n");
        exit(1);
    }

    // Lancer la génération récursive
    generateCombinations(format, current, 0, target);

    // Si aucune combinaison n'est trouvée
    printf("Mot non trouvé.\n");
    free(current);  // Libérer la mémoire allouée
}