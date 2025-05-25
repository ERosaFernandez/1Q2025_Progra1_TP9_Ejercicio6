#ifndef EJERCICIO5_PUERTOS_H_
#define EJERCICIO5_PUERTOS_H_


#define A 'A'
#define B 'B'
#define D 'D'
#define MAX8BITS 255
#define BYTESIZE 8


typedef struct {
	uint8_t b0		:1	;
	uint8_t b1		:1	;
	uint8_t b2		:1	;
	uint8_t b3		:1	;
	uint8_t b4		:1	;
	uint8_t b5		:1	;
	uint8_t b6		:1	;
	uint8_t b7		:1	;
} Byte;

typedef union {
	uint8_t Byte;
	Byte Puerto;
}Puerto;

typedef struct{
	Puerto * PB;
	Puerto * PA;
}Puerto_D;

typedef uint8_t Port;
typedef int8_t Bit;
typedef uint8_t Flag;
typedef int16_t Mask;


void printall (Port);			//Imprime todos los bits de un puerto
int16_t getValue(Port);			//Devuelve el valor entero de un puerto
void bitSet (Port, Bit);		//Enciende los bits deseados de un puerto
void bitClr (Port, Bit);		//Apaga los biTs deseados de un puerto
Bit bitGet (Port, Bit);			//Devuelve un bit especifico de un puerto
void bitToggle (Port, Bit);		//Conmuta un bit especifico de un puerto
void maskOn(Port, Mask);		//Enciende todos los bits del puerto segun la mascara
void maskOff(Port, Mask);		//Apaga todos los bits del puerto segun la mascara
void maskToggle(Port, Mask);	//Conmuta todos los bits del puerto segun la mascara


#endif /* EJERCICIO5_PUERTOS_H_ */
