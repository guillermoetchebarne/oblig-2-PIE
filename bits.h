#include <stdio.h>

int bit (unsigned char buffer, int nb);
unsigned char concatena (unsigned char buffer, unsigned char codigo, int nb);
unsigned char set_bit (unsigned char buffer, int nb, int val);
unsigned char crear_mascara (int max, int min);
void ver_binario (unsigned int buffer, int nb);
unsigned char espejar (unsigned int in, int nb);       
int paridad (unsigned int in);
