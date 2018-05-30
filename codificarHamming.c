#include "codificar.c"

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