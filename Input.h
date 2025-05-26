#ifndef INPUT_H_
#define INPUT_H_


enum results {
	SALIR = -5, ENCENDER, LIMPIAR, CONMUTAR
};
//Lista de posibles resultados de la funcion input.
//Cada uno esta asociado a un numero

typedef int8_t flag;
//asignacion al flag como una variable de 8 bit

int8_t input ();
//funcion input: recibe caracteres para determinar
//la tarea a realizar
void instrucciones();
//funcion instrucciones: imprime por pantalla
//una serie de referencias

#endif /* INPUT_H_ */
