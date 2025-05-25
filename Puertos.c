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

void bitSet (Port c, Bit b){
	if (b>= 0 && b <= 15){
		switch (c){
			case A:
				PA.Byte |= (1 << b);
				break;
			case B:
				PB.Byte |= (1 << b);
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

void bitClr (Port c, Bit b){
	if (b>= 0 && b <= 15){
		switch (c){
			case A:
				PA.Byte &= ~(1 << b);
				break;
			case B:
				PB.Byte &= ~(1 << b);
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

Bit bitGet (Port c, Bit n){
	Bit b;
	if (n >= 0 && n <= 15){
		switch (c){
			case A:
				b = PA.Byte & (1 << n)? 1 : 0;
				break;
			case B:
				b = PB.Byte & (1 << n)? 1 : 0;
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

void bitToggle (Port c, Bit n){
	if ((c == A || c == B || c == D) && n >= 0 && n <= 15){
		if (bitGet (c,n) == 1){
				bitSet (c,n);
		}
		else{
			bitClr (c,n);
		}
	}
	else{
		printf ("Parametro invalido\n");
	}
}

void maskOn(Port c, Mask m){
	Bit b;
	Flag error = 0;
	if (c == A || c == B){
		if (m <= MAX8BITS){
			for (b = 0; b <= (sizeof(Puerto)-1); b ++){
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

