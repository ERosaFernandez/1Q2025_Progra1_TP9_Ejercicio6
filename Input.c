#include <stdio.h>
#include <stdint.h>
#include "Input.h"


#define ERRORCHECK (estado = ((input = getchar()) != '\n' && input != 0)? ERROR : estado)
//Macro para chequear mas de un caracter presente en el buffer

enum flags {
	ERROR, OK, TOGGLE, CLEAR, SET, QUIT
};
//lista de aliases con sus numeros asociados. no son necesarios
//para el usuario asi que quedan aca

int8_t input() {	//Basado en la funcion getciclos del ejercicio 14 del TP4
	int16_t input;
	int8_t num;
	flag estado = ERROR;
	//3 variables , para determinar el input, el numero a devolver
	// y un flag de control

	instrucciones();
	//Lista de referencias para el usuario

	while (estado == ERROR) {
		switch (input = getchar()) {
		//Chequea el input de la entrada
		//Segun lo recibido, hace una determinada asignacion
		//al numero y al flag
		case 't':
		case 'T':
			estado = TOGGLE;
			ERRORCHECK;
			break;
		case 'c':
		case 'C':
			estado = CLEAR;
			ERRORCHECK;
			break;
		case 's':
		case 'S':
			estado = SET;
			ERRORCHECK;
			break;
		case 'q':
		case 'Q':
			estado = QUIT;
			ERRORCHECK;
			break;
		default:
			if (input >= '0' && input <= '7') {
				if (estado == 0) {
					num = (input - '0');
					estado = OK;
					ERRORCHECK;
				}
			} else
				estado = ERROR;
		}
		if (estado == ERROR) {
			//En caso de error, resetea el numero y vuelve a pedir
			//un caracter
			if (input != '\n') {
				while (getchar() != '\n');
			}
			printf("Valor invalido, ingrese nuevamente:\n");
			instrucciones();
			num = 0;
		}
	}
	switch (estado) {
	//Segun el flag, modifica el numero a devolver
	//sera usado para el main
	case QUIT:
		num = SALIR;
		break;
	case SET:
		num = ENCENDER;
		break;
	case CLEAR:
		num = LIMPIAR;
		break;
	case TOGGLE:
		num = CONMUTAR;
	}
	return num;
}

void instrucciones() {
	printf("\n***********Referencia***********\n");
	printf("*                              *\n");
	printf("* 0-7: Nro. de led a encender  *\n");
	printf("* t,T: Conmutar todos los leds *\n");
	printf("* c,C: Apagar todos los leds   *\n");
	printf("* s,S: Encender todos los leds *\n");
	printf("* q,Q: Salir                   *\n");
	printf("*                              *\n");
	printf("********************************\n");
}

