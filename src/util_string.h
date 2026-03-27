#ifndef UTIL_STRING 
#define UTIL_STRING

#include <stdbool.h>

/****************************************************************************** 
 * API de la librairie util_string
 * Déclaration des fonctions pour la manipulation de chaînes de caractères

 * Fonctions :
 *  - length      : calcule la longueur d'une chaîne de caractères
 *  - stcopy      : copie sécurisée d'une chaîne dans un buffer
 *  - scanLine    : lit une ligne depuis l'entrée standard et la stocke dans un buffer
 *  - isNumeric   : vérifie si une chaîne ne contient que des chiffres (optionnellement un '-' au début)
 *  - toInt       : convertit une chaîne représentant un entier en int
 *  - toLowerCase : transforme toutes les lettres majuscules en minuscules
 *  - toUpperCase : transforme toutes les lettres minuscules en majuscules
 *  - equals      : compare deux chaînes pour savoir si elles sont identiques
 *  - stcut       : extrait une portion d'une chaîne dans un buffer
 *  - stfind      : recherche la position d'une sous-chaîne dans une chaîne
 ******************************************************************************/


 /* =============================== length =================================== */
int length(char* texte); 

/* =============================== stcopy =================================== */
bool stcopy(char* ch, char* buff, int size_buff);

/* =============================== scanLine ================================= */
void scanLine(char* buffer, int size);

/* =============================== isNumeric ================================ */
bool isNumeric(char* chaine);

/* =============================== toInt ==================================== */
int toInt(char* ch);

/* =============================== toLowerCase ============================== */
void toLowerCase(char* texte);

/* =============================== toUpperCase ============================== */
void toUpperCase(char* texte);

/* =============================== equals =================================== */
bool equals(char* t1, char* t2);

/* =============================== stcut ==================================== */
void stcut(const char *ch, int start, int size, char *buff);

/* =============================== stfind =================================== */
int stfind(const char *word, int start, const char *ch);


#endif