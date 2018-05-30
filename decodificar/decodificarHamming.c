#include "decodificar.c"

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