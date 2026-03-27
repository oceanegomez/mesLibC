/******************************************************************************
 * util_string.c test
 *
 * Description :
 * Ensemble de fonctions pour la manipulation de chaînes de caractères.
 *
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
 *
 ******************************************************************************/

/* ======================== Bibliothèques utilisées ========================= */
#include "util_string.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* ========================================================================== */


/* =============================== length =================================== */
// Calcul la longueur d'une chaine de caractère ------------------------------
// Note : '\0' (ou 0) : caractère nul indiquant la fin de la chaîne

int length(char* texte){ 

    /* Calcul la longueur d'une chaine de caractère 

    Paramètre : 
        texte : chaine de caractère 

    Retourne : 
        Nombre de caractères présents dans la chaîne, sans inclure '\0' : fin de chaine 
    */

    int pos = 0; 

    while(texte[pos]!='\0') pos++; // '\0' (ou 0) : fin de chaine 
    
    return pos;
}
/* ========================================================================== */


/* =============================== stcopy =================================== */
// Copie une chaîne de caractères dans un buffer 
// Note : "buffer" = zone mémoire (tableau de caractères) de destination pour la copie
// Remarque : le buffer laisse toujours 1 case pour le '\0' final et est terminé par '\0', même si la chaîne est tronquée


bool stcopy(char* ch, char* buff, int size_buff) {

    /* Copie une chaîne de caractères dans un buffer 

    Paramètres :
        ch        : chaîne source à copier
        buff      : buffer de destination (>= size_buff)
        size_buff : taille maximale du buffer
    
    Retour :
        true  -> la copie est complète 
        false -> chaîne a été tronquée (coupée -- buffer trop petit)
    */

    if (size_buff <= 0) return false;

    int i = 0;

    // Copie caractère par caractère tant que la chaîne n'est pas complète et que le buffer a de la place (-1) 

    for (; i < size_buff - 1 && ch[i] != '\0'; i++) {
        buff[i] = ch[i];
    }

    buff[i] = '\0'; // Caractère nul : fin de chaine 

    // Si copie complète de la chaîne : True sinon False 
    return ch[i] == '\0';
}

/* ======================== stcopy (autre version) =========================
bool stcopy(char ch[], char buff[], int size_buff)
{
    int i;
    for (i = 0; ch[i] != '\0' && i < size_buff; i++)
    {
        buff[i] = ch[i];
    }
    buff[i] = '\0'; 
    return ch[i] == '\0';
} */
/* ========================================================================== */


/* ============================== scanLine ================================== */
// Capture une ligne tapée par l'utilisateur et la stocke dans le buffer
// Note : La lecture s'arrête à '\n' (Touche Entrée <==> fin de saisie) ou lorsque le buffer est plein
/* Remarque : Au maximum size-1 caractères sont lus => le buffer laisse toujours 1 case pour le '\0' final 
              si le buffer est plein, le reste de la ligne dans le tampon clavier est ignoré pour ne pas perturber les lectures suivantes
              
              Tampon clavier : stockage temporaire des frappes clavier avant lecture
*/

void scanLine(char* buffer, int size){

    /* Capture une ligne tapée par l'utilisateur et la stocke dans le buffer

    Paramètres : 
        buffer : zone mémoire où stocker la ligne lue
        size   : taille maximale du buffer

    Retour : Aucun 
    */

    int pos=0;     //Index (position d'écriture) du prochain caractère à écrire dans le buffer 
    char letter; 

    // Lecture caractère par caractère (getchar) jusqu'à '\n' ou limite du buffer

    while(pos<(size-1)){ //
        letter = getchar();                // lire le caractère suivant  
        if(letter =='\n') break;           // fin de ligne
            buffer[pos] = letter; 
            pos ++;                        //stocke le caractère et avance l'index
    }

    buffer[pos]=0; // Fin (ou ='\0') 

   // Purge du reste de la ligne si le buffer est plein
    while(letter!='\n') letter = getchar();
}
/* ========================================================================== */


/* ============================= isNumeric =================================== */
// Vérifie si une chaîne ne contient que des chiffres (signe '-' autorisé au début)

bool isNumeric(char* chaine) {
    /* Vérifie si une chaîne ne contient que des chiffres (signe '-' autorisé au début)

    Paramètre :
        chaine : chaîne de caractères à vérifier

    Retour :
        true  : si la chaîne contient uniquement des chiffres (et éventuellement un '-' au début)
        false : si la chaîne est vide ou contient un caractère non numérique
    
    */

    if (chaine[0] == '\0') return false;  // chaîne vide → pas numérique

    int i = 0;

    // Autorise un signe '-' uniquement au début
    if (chaine[0] == '-') i = 1;

    // Vérifie chaque caractère restant
    for (; chaine[i] != '\0'; i++) {
        if (chaine[i] < '0' || chaine[i] > '9') {
            return false;  // caractère non numérique → chaine invalide 
        }
    }

    return true;  // tous les caractères sont numériques
}
/* =========================================================================== */


/* =============================== toInt ==================================== */
// Convertie une chaine de caractère représentant un entier en entier (int)
// Note : chaque chiffre est ajouté de gauche à droite en multipliant le résultat précédent par 10

int toInt(char* ch){
    /* Convertie une chaine de caractère en entier (int)
    
    Paramètre : 
        ch : chaîne de caractères contenant uniquement des chiffres ('0'-'9')

    Retour : 
        int entier correspondant à la chaine, ou -1 si la chaine n'est pas valide     
    */

    int result = 0;
    int n = length(ch);                    // longueur de la chaîne
    
    for(int i = 0; i<n ; i++){

        char c = ch[i];                   // caractère courant

        if (c>= '0' && c<='9'){           // vérifie que c'est un chiffre
            int v = c - '0';              // valeur numérique du caractère
            result = result * 10 + v;     

        } else {
            return -1;                    // caractère non numérique → chaîne invalide
        }
    }
    return result;
}
/* ========================================================================== */


/* ============================ toLowerCase ================================= */
// Remplace toutes les lettres majuscules par des minuscules

void toLowerCase(char *texte){
    /* Remplace totues les lettres majuscules par des minuscules

    Paramètre : 
        texte : chaîne de caractères à modifier

    Retour : Aucun 
    */

    int n = length(texte);

    for (int i = 0; i < n; i++){
        char c = texte[i];

        // Vérifie si le caractère est une majuscule
        if (c >= 'A' && c <= 'Z'){
            texte[i] = c + ('a' - 'A'); // transformation en minuscule
        }
    }
}
/* =========================================================================== */

/* ============================ toUpperCase ================================== */
// Remplace toutes les lettres minuscules par des majuscules

void toUpperCase(char *texte){
    /* Remplace toutes les lettres minuscules par des majuscules 
    
    Paramètre : 
        texte : chaine de caractère à modifier

    Retour : Aucun    
    */

    int n = length(texte);

    for (int i = 0; i < n; i++){
        char c = texte[i];

        // Vérifie si le caractère est une minuscule
        if (c >= 'a' && c <= 'z')
        {
            texte[i] = c - ('a' - 'A'); // transformation en majuscule
        }
    }
}
/* =========================================================================== */

/* =============================== equals ==================================== */
// Comparaison de deux chaines de caractères 
// Retourne true si elles sont identiques false sinon 
// Note : La comparaison est sensible à la casse 

bool equals(char *t1, char *t2){ 
    /* Comparaison de deux chaînes : retourne vrai si elles sont identiques

    Paramètres :
        t1 : première chaîne
        t2 : deuxième chaîne

    Retour : 
        true  : si les deux chaînes ont la même longueur et les mêmes caractères 
        false : sinon

    */

    int n1 = length(t1);
    int n2 = length(t2);

    // Si longueurs différentes, les chaînes sont forcément différentes
    if (n1 != n2)
        return false;

    // Comparaison caractère par caractère
    for (int i = 0; i < n1; i++){
        if (t1[i] != t2[i])
            return false; // un caractère différent → chaînes différentes
    }

    return true; // toutes les lettres sont identiques → chaînes égales
}
/* =========================================================================== */


/* =============================== stcut =================================== */
// Copie une portion de la chaîne source de longueur `size` dans le buffer 
// Note : Le buffer `buff` doit être suffisamment grand (>= size+1 pour le '\0')
// Remarque : Copie caractère par caractère depuis ch à partir de start,  s'arrête si on atteint la taille demandée ou la fin de la chaîne
void stcut(const char *ch, int start, int size, char *buff) {
    
    /* Copie une portion de la chaîne source de longueur `size` [start ; size] 

    Paramètres :
        ch    : chaîne source à partir de laquelle extraire la sous-chaîne
        start : index de départ dans la chaîne source
        size  : nombre maximal de caractères à copier
        buff  : buffer de destination (doit être assez grand pour accueillir size + 1 caractères pour le '\0')

    Retour : Aucun 
    */

    int i;
    for (i = 0; i < size && ch[start + i] != '\0'; i++) { 
        buff[i] = ch[start + i];
    }
    buff[i] = '\0';
}
/* =========================================================================== */


/* =============================== stfind ================================== */
// Recherche la position d'un mot dans une chaîne de caractères, s'il existe
// Note : strlen :c Calcule le nombre de caractères dans une chaîne (sans compter le '\0')

int stfind(const char *word, int start, const char *ch) {
    /* Recherche la position d'un mot dans une chaîne de caractères, s'il existe

    Paramètres :
        word  : sous-chaîne à rechercher
        start : index de départ dans la chaîne principale
        ch    : chaîne principale dans laquelle chercher

    Retour :
        i  : index où la sous-chaîne commence si trouvée
        -1 : si la sous-chaîne n'est pas trouvée
    */

    int i, j;
    int word_len = strlen(word);
    int ch_len = strlen(ch);

    for (i = start; i <= ch_len - word_len; i++) {
        for (j = 0; j < word_len; j++) {
            if (ch[i + j] != word[j])
                break;
        }
        if (j == word_len)
            return i;
    }
    return -1;
}
/* =========================================================================== */
