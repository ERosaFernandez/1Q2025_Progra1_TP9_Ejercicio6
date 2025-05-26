#include <stdio.h>
#include <stdint.h>
#include "Puertos.h"

static Puerto PA;
static Puerto PB;
static Puerto_D PD = {&PB, &PA};

/*
 * Función: printall
 * -----------------
 * Imprime el estado de todos los bits de un puerto.
 *
 * Si la entrada es:
 * - A: imprime todos los bits del puerto PA.
 * - B: imprime todos los bits del puerto PB.
 * - D: primero imprime todos los bits de PA, luego una separación,
 *      y después imprime todos los bits de PB.
 * - Cualquier otro valor: imprime un error indicando que el puerto es inválido.
 */

void printall (Port c){
	Bit b;
	if (c == A){
		for (b = (BYTESIZE-1); b >= 0; b --){
			printf("%d", PA.Byte & (1 << b)? 1 : 0);
		}
	}
	else if (c == B){
		for (b = (BYTESIZE-1); b >= 0; b --){
			printf("%d", PB.Byte & (1 << b)? 1 : 0);
		}
	}
	else if (c == D){
		for (b = (BYTESIZE-1); b >= 0; b --){
			printf("%d",PD.PA->Byte & (1 << b)? 1 : 0);
		}
		printf (" ");
		for (b = (BYTESIZE-1); b >= 0; b --){
			printf("%d",PD.PB->Byte & (1<<b)? 1 : 0 );
		}
	}
	else{
		printf ("Puerto Invalido\n");
	}
	printf ("\n");
}

/*
 * Función: bitSet
 * ---------------
 * Enciende (pone en 1) un bit específico del puerto indicado.
 *
 * - Verifica que el bit `b` esté dentro de un rango de 2 bytes (0 a 15).
 * - Si el puerto es A o B, verifica que `b` esté en el rango de un byte (0 a 7).
 *   Si es así, "prende" el bit correspondiente. Si no, imprime un error.
 * - Si el puerto es D, determina si `b` corresponde a la parte alta o baja:
 *     - Si `b < 8`, se modifica PB.
 *     - Si `b >= 8`, se modifica PA.
 * - Si el puerto es inválido, se imprime un mensaje de error.
 */

void bitSet (Port c, Bit b){
	if (b>= 0 && b <= 15){
		switch (c){
			case A:
				(b < BYTESIZE)? PA.Byte |= (1 << b) : printf ("Bit Invalido\n");
				break;
			case B:
				(b < BYTESIZE)? PB.Byte |= (1 << b) : printf ("Bit Invalido\n");
				break;
			case D:
				if (b < BYTESIZE) PD.PB->Byte |= (1 << b);
				else if (b >=  BYTESIZE && b < 2*BYTESIZE) PD.PA->Byte |= (1 << (b-8));
				break;
			default:
				printf ("Puerto Invalido\n");
			}
	}
	else {
		printf ("Bit Invalido\n");
	}
}

/*
 * Función: bitClr
 * ---------------
 * Apaga (pone en 0) un bit específico del puerto indicado.
 *
 * - Verifica que el bit `b` esté dentro del rango de 2 bytes (0 a 15).
 * - Si el puerto es A o B:
 *     - Verifica que `b` esté en el rango de un byte (0 a 7).
 *     - Si es así, "apaga" el bit correspondiente. Si no, imprime un error.
 * - Si el puerto es D, determina si `b` corresponde a la parte alta o baja:
 *     - Si `b < 8`, se modifica PB.
 *     - Si `b >= 8`, se modifica PA
 * - Si el puerto no es válido, imprime un mensaje de error.
 */

void bitClr (Port c, Bit b){
	if (b>= 0 && b <= 15){
		switch (c){
			case A:
				(b < BYTESIZE)? PA.Byte &= ~(1 << b) : printf ("Bit Invalido\n");
				break;
			case B:
				(b < BYTESIZE)? PB.Byte &= ~(1 << b) : printf ("Bit Invalido\n");
				break;
			case D:
				if (b < BYTESIZE) PD.PB->Byte &= ~(1 << b);
				else if (b >= BYTESIZE && b < 2*BYTESIZE) PD.PA->Byte &= ~(1 << (b-8));
				break;
			default:
				printf ("Puerto Invalido\n");
			}
	}
	else {
		printf ("Bit Invalido\n");
	}
}

/*
 * Función: getValue
 * -----------------
 * Devuelve el valor entero actual del puerto indicado.
 *
 * - Si el puerto es A o B, devuelve el valor de PA o PB.
 * - Si el puerto es D, devuelve la suma de PA (parte alta) y PB (parte baja).
 * - Si el puerto no es válido, devuelve -1 y muestra un mensaje de error.
 */

int16_t getValue(Port c){
	int16_t x;
	switch (c){
		case A:
			x = PA.Byte;
			break;
		case B:
			x = PB.Byte;
			break;
		case D:
			x = PB.Byte;
			x += (PA.Byte) << 8;
			break;
		default:
			printf("Parametro invalido\n");
			return -1;
	}
	return x;
}

/*
 * Función: bitGet
 * ---------------
 * Devuelve el estado (0 o 1) del bit `n` del puerto `c`.
 *
 * - Verifica que `n` esté dentro del rango de 2 bytes (0 a 15).
 * - Si el puerto es A o B:
 *     - Verifica que `n` esté dentro del rango de un byte.
 *     - Si es así, devuelve su estado. Si no, devuelve -1.
 * - Si el puerto es D:
 *     - Si `n <= 7`, busca el bit en PB.
 *     - Si `n > 7`, busca el bit en PA.
 * - Si el puerto es inválido, imprime error y devuelve -1.
 */

Bit bitGet (Port c, Bit n){
	Bit b;
	if (n >= 0 && n <= 15){
		switch (c){
			case A:
				if (b < BYTESIZE) b = PA.Byte & (1 << n)? 1 : 0;
				else {
					printf ("Bit Invalido\n");
					b=-1;
				}
				break;
			case B:
				if (b < BYTESIZE) b = PB.Byte & (1 << n)? 1 : 0;
				else {
					printf ("Bit Invalido\n");
					b=-1;
				}
				break;
			case D:
				if (n <= 7){
					b = PD.PB->Byte & (1 << n)? 1 : 0;
				}
				else if (n > 7 && n <= 15){
					b = PD.PA->Byte & (1 << (n-8))? 1 : 0;
				}
				break;
			default:
				printf ("Puerto Invalido\n");
				b = -1;
		}
	}
	else{
		printf ("Parametro invalido");
		b = -1;
	}
	return b;
}

/*
 * Función: bitToggle
 * ------------------
 * Cambia (invierte) el estado del bit `n` del puerto `c`.
 *
 * - Verifica que el puerto sea válido (A, B o D) y que `n` esté entre 0 y 15.
 * - Para los puertos A y B:
 *     - Verifica que `n` esté en el rango de 8 bits.
 *     - Según el estado actual del bit, lo apaga o lo enciende.
 * - Para el puerto D:
 *     - Hace lo mismo considerando la división entre PA y PB.
 * - Si los parámetros no son válidos, muestra un mensaje de error.
 */

void bitToggle (Port c, Bit n){
	if ((c == A || c == B || c == D) && n >= 0 && n <= 15){
		if (c == A || c == B){
			if(n<BYTESIZE){
				if (bitGet (c,n) == 1){
					bitClr (c,n);
				}
				else{
					bitSet (c,n);
				}
			}
			else{
				printf ("Parametro invalido\n");
			}

		}
		else {
			if (bitGet (c,n) == 1){
					bitSet (c,n);
			}
			else{
				bitClr (c,n);
			}
		}
	}
	else{
		printf ("Parametro invalido\n");
	}
}

/*
 * Función: maskOn
 * ---------------
 * Enciende (pone en 1) los bits del puerto `c` que estén establecidos en la máscara `m`.
 *
 * - Si el puerto es A o B:
 *     - Verifica que la máscara `m` sea menor o igual a 255 (máximo 8 bits).
 *     - Recorre bit a bit y, si el bit correspondiente en la máscara está en 1, lo enciende en el puerto.
 * - Si el puerto es D:
 *     - Se separa la máscara en dos partes: baja (low) y alta (high).
 *     - La parte baja se aplica sobre el puerto B.
 *     - La parte alta se aplica sobre el puerto A.
 * - Si el puerto no es válido o la máscara no es válida, se levanta una bandera de error
 *   y se imprime un mensaje de error.
 */

void maskOn(Port c, Mask m){
	Bit b;
	Flag error = 0;
	if (c == A || c == B){
		if (m <= MAX8BITS){
			for (b = 0; b < BYTESIZE; b ++){
				if (m & (1 << b)){
					bitSet(c,b);
				}
			}
		}
		else error = 1;
	}
	else if (c == D){
		uint8_t low = (uint8_t) m;
		uint8_t high = (uint8_t) (m >> 8);
		for (b = 0; b < BYTESIZE; b ++){
			if (low & (1 << b)){
				bitSet(B,b);
			}
			if (high & (1 << b)){
				bitSet(A,b);
			}
		}
	}
	else {
		error = 1;
	}
	if (error == 1){
		printf ("Parametro invalido\n");
	}
}

/*
 * Función: maskOff
 * ----------------
 * Apaga (pone en 0) los bits del puerto `c` que estén establecidos en la máscara `m`.
 *
 * - Si el puerto es A o B:
 *     - Verifica que la máscara `m` sea válida (menor o igual a 255).
 *     - Recorre los bits de la máscara y apaga cada bit correspondiente en el puerto.
 * - Si el puerto es D:
 *     - Divide la máscara en parte baja (para PB) y parte alta (para PA).
 *     - Aplica cada parte al puerto correspondiente.
 * - Si la máscara o el puerto no son válidos, se muestra un mensaje de error.
 */

void maskOff(Port c, Mask m){
	Bit b;
	Flag error = 0;
	if (c == A || c == B){
		if (m <= MAX8BITS){
			for (b = 0; b < BYTESIZE; b ++){
				if (m & (1 << b)){
					bitClr(c,b);
				}
			}
		}
		else error = 1;
	}
	else if (c == D){
		uint8_t low = (uint8_t) m;
		uint8_t high = (uint8_t) (m >> 8);
		for (b = 0; b < BYTESIZE; b ++){
			if (low & (1 << b)){
				bitClr(B,b);
			}
			if (high & (1 << b)){
				bitClr(A,b);
			}
		}
	}
	else {
		error = 1;
	}
	if (error == 1){
		printf ("Parametro invalido\n");
	}
}

/*
 * Función: maskToggle
 * -------------------
 * Invierte (cambia de 1 a 0 o de 0 a 1) los bits del puerto `c` que estén establecidos en la máscara `m`.
 *
 * - Si el puerto es A o B:
 *     - Verifica que la máscara tenga solo 8 bits (menor o igual a 255).
 *     - Recorre bit a bit y aplica la operación toggle si la máscara lo indica.
 * - Si el puerto es D:
 *     - Se separa la máscara en parte baja (aplicada a PB) y parte alta (aplicada a PA).
 *     - Se invierten los bits correspondientes en cada puerto.
 * - Si el puerto o la máscara no son válidos, se muestra un mensaje de error.
 */

void maskToggle(Port c, Mask m){
	Bit b;
	Flag error = 0;
	if (c == A || c == B){
		if (m <= MAX8BITS){
			for (b = 0; b < BYTESIZE; b ++){
				if (m & (1 << b)){
					bitToggle(c,b);
				}
			}
		}
		else error = 1;
	}
	else if (c == D){
		uint8_t low = (uint8_t) m;
		uint8_t high = (uint8_t) (m >> 8);
		for (b = 0; b < BYTESIZE; b ++){
			if (low & (1 << b)){
				bitToggle(B,b);
			}
			if (high & (1 << b)){
				bitToggle(A,b);
			}
		}
	}
	else {
		error = 1;
	}
	if (error == 1){
		printf ("Parametro invalido\n");
	}
}

