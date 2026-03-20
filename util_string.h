#ifndef UTIL_STRING 
#define UTIL_STRING

#include <stdbool.h>

int length(char* texte);

bool stcopy(char* ch, char* buff, int size_buff);

int toInt(char* ch);

void scanLine(char* buffer, int size);

#endif 