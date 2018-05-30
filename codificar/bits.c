#include <stdio.h>

int bit (unsigned char buffer, int nb) {
    return ((1<<nb) & buffer)>>nb;
}

unsigned char concatena (unsigned char buffer, unsigned char codigo, int nb) {
    return (buffer<<nb) | codigo;
}

unsigned char set_bit (unsigned char buffer, int nb, int val) {
        if (val == 0) {
            buffer = (~(1<<nb)) & buffer;
           }
        else {
            buffer = buffer | (1<<nb);
        }
    return buffer;
}
      
unsigned char crear_mascara (int max, int min) {
    int i;
    unsigned char mask = 00000000;
    for (i = min ; i <= max ; i++) {
        mask = set_bit (mask, i, 1);
    }
    return mask;
}
    
void ver_binario (unsigned int buffer, int nb) {
    int i;
    unsigned int mask =1<<(nb-1);
    for (i = 1; i<=nb; i++) {
        unsigned int aux = (buffer & mask)>>(nb-i);
        printf("%d",aux);
        mask = mask>>1;
    }
    printf("\n");
}

unsigned char espejar (unsigned int in, int nb) {
    int i;
    unsigned char mask = in & crear_mascara (nb-1, 0);
    unsigned char aux;
    for (i = 0 ; i < nb/2 ; i++) {
        aux = bit (mask, nb-1-i);
        mask = set_bit (mask, (nb-1-i), bit (mask,i));
        mask = set_bit (mask, i, aux);
    }
    return mask ;
}
        
int paridad (unsigned int in) {
    int c = 0;
    int i;
    int bitin (int buffer, int nb) {
        return ((1<<nb) & buffer)>>nb;
    }
    for (i = 1; i <= sizeof (in) * 8 ; i++) {
    	c = (bitin (in, i) == 1) ? c + 1 : c;
    }
    c = (c % 2 == 0) ? 1 : 0;
    return c;
}
