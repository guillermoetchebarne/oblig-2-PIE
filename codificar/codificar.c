#include <stdio.h>
#include "bits.h"
#include "bits.c"

typedef enum code0 {OK_IO, ERROR_LECTURA, ERROR_ESCRITURA} CodigoErrorEntradaSalida;

unsigned short codificar (unsigned char simbolo) {
	unsigned char codificar_nibble (unsigned char nib) {
		int r0 = !paridad (set_bit (nib, 3, 0));
		int r1 = !paridad (set_bit (nib, 2, 0));
		int r2 = !paridad (set_bit (nib, 1, 0));
		nib = set_bit (nib, 4, bit (nib, 3));
		nib = set_bit (nib, 3, r0);
		nib = set_bit (nib, 5, r1);
		nib = set_bit (nib, 6, r2);
		nib <<= 1;
		nib = set_bit (nib, 0, !paridad (nib));
		return nib;
	}
	unsigned short sim = codificar_nibble (simbolo & crear_mascara (3, 0)) | codificar_nibble (simbolo  >> 4) << 8;
	return sim;
}

CodigoErrorEntradaSalida codificar_archivo (FILE * entrada, FILE * salida) {
	CodigoErrorEntradaSalida aux = OK_IO;
	char c;
	unsigned short code;
	if (entrada == NULL) {
        aux = ERROR_LECTURA;
    } else {
    	while ((c = getc (entrada)) != EOF && aux == OK_IO) {
			code = codificar (c);
			c = putc (code >> 8, salida);
			aux = (c == EOF) ? ERROR_ESCRITURA : OK_IO;
			c = putc (code, salida);
			aux = (c == EOF) ? ERROR_ESCRITURA : OK_IO;
		}
		aux = (c == EOF && ferror (entrada)) ? ERROR_LECTURA : OK_IO;
	}
    fclose (entrada);
    fclose (salida);
    return aux;
}