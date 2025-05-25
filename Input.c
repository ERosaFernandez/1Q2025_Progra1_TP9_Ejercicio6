#include <stdio.h>
#include <stdint.h>
#include "Input.h"

//algo para actualizar el eclipse :(

#define ERRORCHECK (estado = ((input = getchar()) != '\n' && input != 0)? ERROR : estado)

enum flags {
	ERROR, OK, TOGGLE, CLEAR, SET, QUIT
};


int8_t input() {	//Basado en la funcion getciclos del ejercicio 14 del TP4
	int16_t input;
	int8_t num;
	flag estado = ERROR;

	instrucciones ();

	while (estado == ERROR) {
		switch (input = getchar()) {
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
			}
			else estado = ERROR;
		}
		if (estado == ERROR){
			while(getchar()!='\n');
			printf("Valor invalido, ingrese nuevamente:\n");
			instrucciones();
			num = 0;
		}
	}
	switch (estado){
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

void instrucciones (){
	printf("**********Referencia**********\n");
	printf("*                            *\n");
	printf("*0-7: Nro. de led a encender *\n");
	printf("*t,T: Conmutar todos los leds*\n");
	printf("*c,C: Apagar todos los leds  *\n");
	printf("*s,S: Encender todos los leds*\n");
	printf("*q,Q: Salir                  *\n");
	printf("******************************\n");
}


