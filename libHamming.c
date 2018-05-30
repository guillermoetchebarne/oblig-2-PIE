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