#include "util_string.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// ==============================================================================================================
int length(char* texte){ 
    int pos = 0; 
    while(texte[pos]!=0) pos++; //while(texte[pos++]!=0);
    return pos;
}
// ==============================================================================================================


// ==============================================================================================================
// copie ch dans buff
bool stcopy(char* ch, char* buff, int size_buff) { // équivalent à char ch[], char buff[]
    if (size_buff <= 0) return false;
    // retourne true si la copie est complète (il y avait assez de place dans buff)
    int i;
    // Copie tant qu'on n'a pas atteint la fin de ch et la limite du buffer -1 (pour '\0')
    for (i = 0; i < size_buff - 1 && ch[i] != '\0'; i++) {
        buff[i] = ch[i];
    }

    // On termine la chaîne par le caractère nul
    buff[i] = '\0';

    // Si la fin de ch est atteinte → copie complète
    return ch[i] == '\0'; // on a bien réussi à tout copier 
}
// ==============================================================================================================


// ==============================================================================================================
int toInt(char* ch){
    //retourne (sous forme d'entier) la valeur entière représentée dans la chaine ch

    int result = 0;

    //on va ajouter au résultat chacun des chiffres de la gauche vers la droite 
    //en multipliant par 10 à chaque étape 

    int n = length(ch); 
    for(int i = 0; i<n ; i++){
        char c = ch[i];  // on isole le caractère courant(celui de position i)
        if (c>= '0' && c<='9'){ //est-ce que c représente bien un nombre 0 à 9
            int v = c - '0'; //valeur représentée par ce caractère c 
            result = result * 10 + v;
        } else { // erreur ch ne représente pas une valeur entière 
            return -1;
        }
    }
    return result;
}
// ==============================================================================================================



// ==============================================================================================================
void scanLine(char* buffer, int size){ // Capturer une saisie 
    //on va utiliser getchar() pour lire char par char 
    //-> jusqu'au caractère '\n' (touche entrer) <==> fin de saisie 
    //-> on va extraire au maximum (size-1) caractèer (on laisse la place pour le 0 final dans buffer)
    int pos=0; //position d'écriture du prochain caractèere dans le buffer 
    //on doit boucler sur getchar() pour capture chaque caractère et le placer dans buffer[pos]
    //ensuite on augmente pos de 1 
    // -> on continue jusqu'à ce que getchar() returne '\n'
    // ==> bouche while !!! 
    char letter; 
    while(pos<(size-1)){ //
        letter = getchar(); // lecture du prochain caractère 
        if(letter =='\n') break;  // fin de capture 
            buffer[pos] = letter; 
            pos ++; //position suivante 
    }

    buffer[pos]=0; // ou ='\0' c'est la même chose 

    //ICI : si on rempli le buffer (pos == size-1 ici), il reste des caractères potentiel  dans le tampon clavier 
    // ==> ces caractères sont tous ceux écrit jusqu'à ce que l'utilisateur tape sur Entrer 
    // ==> ces caractères ne doivent pas perturber les prochaines extractions !!!
    // ==> on doit donc purger le tampon clavier : 
    while(letter!='\n') letter = getchar();
}
// ==============================================================================================================


// ==============================================================================================================
