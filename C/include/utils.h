#pragma once
#include <stdbool.h>

// c'est le délimiteur qui sépare les champs lors de la conversion de chaînes en structures
#define delimiter '#'


/**
 * cette fonction coupe une chaîne de caractères à partir d'espaces à gauche et à droite
 * @param str la chaîne de caractères à couper
 */
char *trim(char *str);

/**
 * cette fonction vérifie si une chaîne de caractères est vide ou remplie d'espaces
 * @param str la chaîne de caractères à vérifier
 */
bool check_empty(char *str);

/**
 * cette fonction vérifie si un isbn est valide
 * @param str la chaîne de caractères à vérifier
 */
bool check_isbn(char *str);

/**
 * Cette fonction divise une chaîne de caractères par un délimiteur
 * @param str la chaîne à diviser
 * @param d Le délimiteur
 * @param length l'adresse où stocker la taille de la table résultante
 */
char **split(char *str, char d, int *length);