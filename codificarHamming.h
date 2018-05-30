typedef enum code0 {OK_IO, ERROR_LECTURA, ERROR_ESCRITURA} CodigoErrorEntradaSalida;
CodigoErrorEntradaSalida codificar_archivo (FILE * entrada, FILE * salida);