/*
 * Input.c
 *
 *  Created on: May 25, 2025
 *      Author: enzorofer
 */
#include <stdio.h>
#include <stdint.h>
#include "Input.h"

int16_t input (){	//Basado en la funcion getciclos del ejercicio 14 del TP4
	int8_t input;
	int16_t num;
	flag estado = 0;

	while(estado==0){
		input = getchar();
		if (input != '\n' && input != 'q'){
			while (input != '\n'){
				if (input >= '0' && input <= '7'){
					num = (input - '0');
					input = getchar();
					estado=1;
				}
				else{
					if(input!='\n'){
						while(getchar()!='\n');
						input = '\n';
					}
					estado=0;
					printf("Numero invalido, ingrese nuevamente:\t");
					num=0;
				}
			}
		}
		else if (input == '\n'){
			num = 1;
			estado=1;
		}
		else if(input == 'q'){
			input = getchar();
			if(input == '\n'){
				num=-1;
				estado=1;
			}
			else{
				while(getchar()!='\n');
				input = '\n';
				printf("Numero invalido, ingrese nuevamente:\t");
			}
		}
	}
	return num;
}

