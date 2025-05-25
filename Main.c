#include <stdio.h>
#include <stdint.h>
#include "Puertos.h"
#include "Input.h"

//algo para actualizar el eclipse >:(

int main() {
	int8_t cambios = 0;

	printf("Estado de los leds del Puerto A:\n");
	printall(A);

	while (cambios != SALIR) {
		cambios = input();
		printf ("%d\n", cambios);
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
