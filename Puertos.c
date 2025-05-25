#include <stdio.h>
#include <stdint.h>
#include "Puertos.h"

static Puerto PA;
static Puerto PB;
static Puerto_D PD = {&PB, &PA};

void printall (Port c){
	Bit b;
	if (c == A){
		for (b = (BYTESIZE-1); b >= 0; b --){
			printf("%d", PA.Byte & (1 << b)? 1 : 0);											//si la entreda es A imprime todos los bits de PA
		}
	}
	else if (c == B){
		for (b = (BYTESIZE-1); b >= 0; b --){
			printf("%d", PB.Byte & (1 << b)? 1 : 0);											//si la entreda es B imprime todos los bits de PB
		}
	}
	else if (c == D){																			//si la entrada es D
		for (b = (BYTESIZE-1); b >= 0; b --){
			printf("%d",PD.PA->Byte & (1 << b)? 1 : 0);											//primero imprime todos los bits de PA
		}
		printf (" ");																			//se imprime una separacion
		for (b = (BYTESIZE-1); b >= 0; b --){
			printf("%d",PD.PB->Byte & (1<<b)? 1 : 0 );											//y luego se imprime todos los bits de PB
		}
	}
	else{
		printf ("Puerto Invalido\n");															//si la entrada no hace referencia a un puerto imprime un error
	}
	printf ("\n");
}

void bitSet (Port c, Bit b){
	if (b>= 0 && b <= 15){																		//se verifica que el bit b este dentro de un rango de 2 bytes
		switch (c){
			case A:
				(b < BYTESIZE)? PA.Byte |= (1 << b) : printf ("Bit Invalido\n");				//si c es A o B se verifica que b este en el rango de un byte
				break;																			//si b se pasa se imprime un error y si no se "prende" el bit b
			case B:
				(b < BYTESIZE)? PB.Byte |= (1 << b) : printf ("Bit Invalido\n");
				break;
			case D:
				if (b < BYTESIZE) PD.PB->Byte |= (1 << b);										//si c es D se busca si b esta en la parte alta o baja del puerto
				else if (b >=  BYTESIZE && b < 2*BYTESIZE) PD.PA->Byte |= (1 << (b-8));			//y luego se enciende el bit correspondiente
				break;
			default:
				printf ("Puerto Invalido\n");													//si c no hace referencia a un puerto imprime un error
			}
	}
	else {
		printf ("Bit Invalido\n");																//si b no hace referencia a un numero de bit valido imprime un error
	}
}

void bitClr (Port c, Bit b){
	if (b>= 0 && b <= 15){																		//se verifica que el bit b este dentro de un rango de 2 bytes
		switch (c){
			case A:
				(b < BYTESIZE)? PA.Byte &= ~(1 << b) : printf ("Bit Invalido\n");				//si c es A o B se verifica que b este en el rango de un byte
				break;																			//si b se pasa se imprime un error y si no se "apaga" el bit b
			case B:
				(b < BYTESIZE)? PB.Byte &= ~(1 << b) : printf ("Bit Invalido\n");
				break;
			case D:
				if (b < BYTESIZE) PD.PB->Byte &= ~(1 << b);										//si c es D se busca si b esta en la parte alta o baja del puerto
				else if (b >= BYTESIZE && b < 2*BYTESIZE) PD.PA->Byte &= ~(1 << (b-8));			//y luego se enciende el bit correspondiente
				break;
			default:
				printf ("Puerto Invalido\n");													//si c no hace referencia a un puerto imprime un error
			}
	}
	else {
		printf ("Bit Invalido\n");																//si b no hace referencia a un numero de bit valido imprime un error
	}
}

int16_t getValue(Port c){
	int16_t x;
	switch (c){
		case A:
			x = PA.Byte;																		//si c es A devuelve el valor de PA
			break;
		case B:
			x = PB.Byte;																		//si c es B devuelve el valor de PB
			break;
		case D:
			x = PB.Byte;																		//si c es D devuelve el valor de PA + PB
			x += (PA.Byte) << 8;
			break;
		default:
			printf("Parametro invalido\n");														//si c no hace referencia a un puerto devuelve -1
			return -1;
	}
	return x;
}

Bit bitGet (Port c, Bit n){
	Bit b;
	if (n >= 0 && n <= 15){																		//se verifica que el bit n este dentro de un rango de 2 bytes
		switch (c){
			case A:
				if (b < BYTESIZE) b = PA.Byte & (1 << n)? 1 : 0;								//si c es A o B se verifica que el bit n este en el rango de un byte
				else {																			//si se cumple devuelve el estado del bit n y si no devuelve -1
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
				if (n <= 7){																	//si c es D se busca si b esta en la parte alta o baja del puerto
					b = PD.PB->Byte & (1 << n)? 1 : 0;											//para asi devolver el estado del bit adecuado
				}
				else if (n > 7 && n <= 15){
					b = PD.PA->Byte & (1 << (n-8))? 1 : 0;
				}
				break;
			default:
				printf ("Puerto Invalido\n");													//si c no es un puerto valido imprime un error y devuelve 1
				b = -1;
		}
	}
	else{
		printf ("Parametro invalido");															//si el bit n no esta en el rango de 2 bytes imprime un error y devulver -1
		b = -1;
	}
	return b;
}

void bitToggle (Port c, Bit n){
	if ((c == A || c == B || c == D) && n >= 0 && n <= 15){										//se verifica que c sea un puerto valido y que el bit n este en un rango de 2 bytes
		if (c == A || c == B){
			if(n<BYTESIZE){																		//verifica que si c es el puerto A o B el bit n debe estar en un rango de 8 bits
				if (bitGet (c,n) == 1){
					bitSet (c,n);
				}																				//se modifica el estado del bit dependiendo de su estado actual	para los puertos A y B
				else{
					bitClr (c,n);
				}
			}
			else{
				printf ("Parametro invalido\n");												//error si n se pasa de los 8 bits para los puertos A y B
			}

		}
		else {
			if (bitGet (c,n) == 1){
					bitSet (c,n);																//se modifica el estado del bit dependiendo de su estado actual	para el puerto D
			}
			else{
				bitClr (c,n);
			}
		}
	}
	else{
		printf ("Parametro invalido\n");														//error por si algun parametro falla la validacion inicial
	}
}

void maskOn(Port c, Mask m){
	Bit b;
	Flag error = 0;
	if (c == A || c == B){																		//se verifica que c se el puerto A o B
		if (m <= MAX8BITS){																		//al ser uno de esos puertos la mascara tiene que ser un numero menor a 256
			for (b = 0; b <= (sizeof(Puerto)-1); b ++){
				if (m & (1 << b)){																//se usa la mascara para modificar bit a bit el puerto indicado
					bitSet(c,b);
				}
			}
		}
		else error = 1;																			//si no cumple alguno de las verificaciones se levanta un flag de error
	}
	else if (c == D){																			//se verifica si c es D
		uint8_t low = (uint8_t) m;
		uint8_t high = (uint8_t) (m >> 8);														//se separan la mascara en la parte alta y la parte baja de la misma
		for (b = 0; b < BYTESIZE; b ++){
			if (low & (1 << b)){
				bitSet(B,b);																	//se usa la mascara low para modificar bit a bit el puerto B
			}
			if (high & (1 << b)){
				bitSet(A,b);																	//se usa la mascara high para modificar bit a bit el puerto A
			}
		}
	}
	else {
		error = 1;																				//si c no es ninguno de los puertos se levanta la flag de error
	}
	if (error == 1){
		printf ("Parametro invalido\n");														//si la flag esta levantada se imprime un error
	}
}

void maskOff(Port c, Mask m){
	Bit b;
	Flag error = 0;
	if (c == A || c == B){																		//se verifica que c se el puerto A o B
		if (m <= MAX8BITS){																		//al ser uno de esos puertos la mascara tiene que ser un numero menor a 256
			for (b = 0; b < BYTESIZE; b ++){
				if (m & (1 << b)){
					bitClr(c,b);																//se usa la mascara para modificar bit a bit el puerto indicado
				}
			}
		}
		else error = 1;																			//si no cumple alguno de las verificaciones se levanta un flag de error
	}
	else if (c == D){																			//se verifica si c es D
		uint8_t low = (uint8_t) m;
		uint8_t high = (uint8_t) (m >> 8);														//se separan la mascara en la parte alta y la parte baja de la misma
		for (b = 0; b < BYTESIZE; b ++){
			if (low & (1 << b)){
				bitClr(B,b);																	//se usa la mascara low para modificar bit a bit el puerto B
			}
			if (high & (1 << b)){
				bitClr(A,b);																	//se usa la mascara high para modificar bit a bit el puerto A
			}
		}
	}
	else {
		error = 1;																				//si c no es ninguno de los puertos se levanta la flag de error
	}
	if (error == 1){
		printf ("Parametro invalido\n");														//si la flag esta levantada imprime un error
	}
}

void maskToggle(Port c, Mask m){
	Bit b;
	Flag error = 0;
	if (c == A || c == B){																		//se verifica que c se el puerto A o B
		if (m <= MAX8BITS){																		//al ser uno de esos puertos la mascara tiene que ser un numero menor a 256
			for (b = 0; b < BYTESIZE; b ++){
				if (m & (1 << b)){
					bitToggle(c,b);																//se usa la mascara para modificar bit a bit el puerto indicado
				}
			}
		}
		else error = 1;																			//si no cumple alguno de las verificaciones se levanta un flag de error
	}
	else if (c == D){																			//se verifica si c es D
		uint8_t low = (uint8_t) m;
		uint8_t high = (uint8_t) (m >> 8);														//se separan la mascara en la parte alta y la parte baja de la misma
		for (b = 0; b < BYTESIZE; b ++){
			if (low & (1 << b)){
				bitToggle(B,b);																	//se usa la mascara low para modificar bit a bit el puerto B
			}
			if (high & (1 << b)){
				bitToggle(A,b);																	//se usa la mascara high para modificar bit a bit el puerto A
			}
		}
	}
	else {
		error = 1;																				//si c no es ninguno de los puertos se levanta la flag de error
	}
	if (error == 1){
		printf ("Parametro invalido\n");														//si la flag esta levantada imprime un error
	}
}

