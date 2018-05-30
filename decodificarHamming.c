#include "decodificar.c"

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

void main (int argc, char * argv []) {
	struct EstadisticasDecodificar pinto;
	if (argc == 3) {
		FILE * fpin;
		FILE * fpout;
		fpin = fopen (argv [1], "rb");
		fpout = fopen (argv [2], "wb");
		pinto = decodificar_archivo (fpin, fpout);
	} else if (argc == 1) {
		pinto = decodificar_archivo (stdin, stdout);
	} else {
		printf ("mandaste cualquiera\n");
	}
	fprintf(stderr, "correctas: %d\ncorregidas: %d\nerroneas: %d\nerror: %d", pinto.correctos, pinto.corregidos, pinto.incorrectos, pinto.error);
}