#include "codificar.c"

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

void main (int argc, char * argv []) {
	if (argc == 3) {
		FILE * fpin;
		FILE * fpout;
		fpin = fopen (argv [1], "rb");
		fpout = fopen (argv [2], "wb");
		CodigoErrorEntradaSalida arch = codificar_archivo (fpin, fpout);
	} else if (argc == 1) {
		CodigoErrorEntradaSalida arch = codificar_archivo (stdin, stdout);
	} else {
		printf ("mandaste cualquiera\n");
	}
}