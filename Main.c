#include <stdio.h>
#include <stdint.h>
#include "Puertos.h"
#include "Input.h"

int main() {
	int8_t cambios = 0;
	//Variable de los cambios a hacer en los leds.
	//Del 0 al 7, se encienden los leds deseados
	//otros numeros corresponden a casos especiales

	printf("Estado de los leds del Puerto A:\n");
	printall(A);
	//Imprime por pantalla el estado de cada bit
	//del puerto A

	while (cambios != SALIR) {
		/*
		 * Segun la entrada por input
		 * enciende un led,
		 * enciende todos,
		 * apaga todos,
		 * o los conmuta.
		 */
		cambios = input();
		switch (cambios) {
		case ENCENDER:
			maskOn(A, MAX8BITS);
			break;
		case LIMPIAR:
			maskOff(A, MAX8BITS);
			break;
		case CONMUTAR:
			maskToggle(A, MAX8BITS);
			break;
		case SALIR:
			break;
		default:
			bitSet (A, cambios);
		}
		if (cambios != SALIR) {
			printf("Estado de los leds del Puerto A:\n");
			printall(A);
		}
	}

	return 0;
}
