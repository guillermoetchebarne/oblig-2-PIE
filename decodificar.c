#include <stdio.h>
#include "bits.h"
#include "bits.c"

typedef enum code1 {OK_DECO, BIT_CORREGIDO, DOS_ERRORES_DETECTADOS} CodigoErrorDeco;

struct ResultadoDecodificar {
	unsigned char decodificado;
	CodigoErrorDeco error;
};

struct EstadisticasDecodificar {
	unsigned long correctos;
	unsigned long corregidos;
	unsigned long incorrectos;
	int error;
};

struct ResultadoDecodificar decodificar (unsigned short codigo) {
	struct ResultadoDecodificar decodificar_nibble (unsigned char nib) {
		struct ResultadoDecodificar aux = {00000000, OK_DECO};
		aux.error = (!paridad (set_bit (nib, 0, 0)) != bit (nib, 0)) ? BIT_CORREGIDO : OK_DECO;
		int r0 = (bit (nib, 3) ^ bit (nib, 2) ^ bit (nib, 1) != bit (nib, 4)) ? 1 : 0;
		int r1 = (bit (nib, 5) ^ bit (nib, 2) ^ bit (nib, 1) != bit (nib, 6)) ? 1 : 0;
		int r2 = (bit (nib, 5) ^ bit (nib, 3) ^ bit (nib, 1) != bit (nib, 7)) ? 1 : 0;
		int p = r0 * 4 + r1 * 2 + r2;
		if (p !=0) {
			nib = (aux.error == BIT_CORREGIDO) ? nib = set_bit (nib, 8-p, !bit (nib, 8-p)) : nib;
			aux.error = (aux.error != BIT_CORREGIDO) ? DOS_ERRORES_DETECTADOS : aux.error;
		}
		aux.decodificado = (set_bit (nib, 4, bit (nib, 5)) & crear_mascara (4, 1)) >> 1;
		return aux;
	}
	struct ResultadoDecodificar decobajo = decodificar_nibble (codigo & crear_mascara (7, 0));
	struct ResultadoDecodificar decoalto = decodificar_nibble (codigo >> 8);
	struct ResultadoDecodificar sim = {'?', DOS_ERRORES_DETECTADOS};
	if (decobajo.error != DOS_ERRORES_DETECTADOS && decoalto.error != DOS_ERRORES_DETECTADOS) {
		sim.decodificado = decobajo.decodificado | (decoalto.decodificado << 4);
		if (decobajo.error == OK_DECO && decoalto.error == OK_DECO) {
			sim.error = OK_DECO;
		} else {
			sim.error = BIT_CORREGIDO;
		}
	}	
	return sim;
}

struct EstadisticasDecodificar decodificar_archivo (FILE * entrada, FILE * salida) {
	int c;
	unsigned short buffer;
	struct ResultadoDecodificar temp;
	struct EstadisticasDecodificar aux = {0,0,0,1};
	if (entrada == NULL) {
        aux.error = 0;
    } else {
		while ((c = getc (entrada)) != EOF && aux.error == 1) {
			buffer = c << 8;
			c = getc (entrada);
			aux.error = (c == EOF && ferror (entrada)) ? 0 : 1;
			temp = decodificar (buffer | c);
			c = putc (temp.decodificado, salida);
			aux.error = (c == EOF) ? 0 : 1;
			if (temp.error == OK_DECO) {
	  			aux.correctos++;
	  		} else if (temp.error == BIT_CORREGIDO ) {
	  			aux.corregidos++;
	  		} else {
	  			aux.incorrectos++;
	  		}
	  	}
	} 	
  	fclose (entrada);
	fclose (salida);
	return aux;
}