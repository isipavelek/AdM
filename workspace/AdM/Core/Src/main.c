/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  ******************************************************************************
  */


#include "init.h"

/*
 * Prototipos de Funciones en C
  * */
#define BITSAT 12

void zeros_c (uint32_t * vector, uint32_t longitud);
void productoEscalar32_c (uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar);
void productoEscalar16_c (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);
void productoEscalar12_c (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);
void filtroVentana10_c(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn);
void pack32to16_c (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud);
int32_t max_c (int32_t * vectorIn, uint32_t longitud);
void downsampleM_c (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N);
void invertir_c (uint16_t * vector, uint32_t longitud);
void corr_c (int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud);
/*
 * Prototipos de Funciones en Assembly
  * */

void zeros_asm (uint32_t * vector, uint32_t longitud);
void productoEscalar32_asm (uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar);
void productoEscalar16_asm (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);
void productoEscalar12_asm (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar);
void filtroVentana10_asm(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn);
void pack32to16_asm (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud);
int32_t max_asm (int32_t * vectorIn, uint32_t longitud);
void downsampleM_asm (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N);
void invertir_asm (uint16_t * vector, uint32_t longitud);
void corr_asm (int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud);


/**
  * @brief  The application entry point.
  * @retval int
  */

int32_t vector_prueba32_in[]={1,2,3,4,5,6,7,8,9,10};
int32_t vector_prueba32_out[]={0,0,0,0,0,0,0,0,0,0};
uint16_t vector_prueba16_in[]={1,1,1,1,1,1,1,1,1,1};
uint16_t vector_prueba16_out[]={1,1,1,1,1,1,1,1,1,1};

int main(void){
  init();
  //productoEscalar32_asm(vector_prueba32_in,vector_prueba32_out,10,5);
  //productoEscalar32_c(vector_prueba32_in,vector_prueba32_out,10,3);

  downsampleM_asm(vector_prueba32_in,vector_prueba32_out,10,3);

  for (;;){
  }

}


void zeros_c (uint32_t * vector, uint32_t longitud){
	while(longitud--)*(vector++)=0;
}
void productoEscalar32_c (uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar){
	while(longitud--)*(vectorOut++)=(*vectorIn++)*escalar;

}
void productoEscalar16_c (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar){
	while(longitud--)*(vectorOut++)=(*vectorIn++)*escalar;
}
void productoEscalar12_c (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar){
	while(longitud--){
		if(((*vectorIn)*escalar)>((1<<BITSAT)-1)){
			*(vectorOut++)=((1<<BITSAT)-1);
			vectorIn++;
		}else *(vectorOut++)=*(vectorIn++);

	}

}
void filtroVentana10_c(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn){
}
void pack32to16_c (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud){

}

int32_t max_c (int32_t * vectorIn, uint32_t longitud){
	int32_t maximo=*vectorIn;
	while(--longitud){
		if(maximo<*(vectorIn))maximo=*vectorIn;
		vectorIn++;
	}
	return maximo;
}

void downsampleM_c (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N){
	*(vectorOut++)=*(vectorIn++);
	uint32_t i=1;
	while(i++<longitud){
		if(!((i)%N))vectorIn++;
		else*(vectorOut++)=*(vectorIn++);
	}



}
void invertir_c (uint16_t * vector, uint32_t longitud){
	uint16_t aux;
	while(longitud--){
		aux=vector[longitud];
		*(vector+longitud)=*vector;
		*(vector++)=aux;
	}
}
void corr_c (int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud){

	int16_t sxy;
    uint32_t delay,i,j;
    for(delay = -longitud + 1; delay < longitud; delay++){
        sxy = 0;
        for(i=0; i<longitud; i++){
            j = i + delay;
            if((j < 0) || (j >= longitud))continue;
            else sxy += (vectorX[i] * vectorY[j]);
        }
        vectorCorr[delay + longitud - 1] = sxy;
    }
}


void zeros_asm (uint32_t * vector, uint32_t longitud){

	__asm volatile("		MOV R0, %0" :: "r"(longitud));
	__asm volatile("		MOV R1, #0");
	__asm volatile("		MOV R2, %0" :: "r"(vector));
	__asm volatile("\n loop:");
	__asm volatile("		STR R1, [R2],+4");
	__asm volatile("		SUB R0,R0,#1");
	__asm volatile("		CMP R0,#0");
	__asm volatile("		BNE loop");


}
void productoEscalar32_asm (uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar){

	__asm volatile("		MOV R0, %0" :: "r"(longitud));
	__asm volatile("		MOV R1, %0" :: "r"(escalar));
	__asm volatile("		MOV R2, %0" :: "r"(vectorIn));
	__asm volatile("		MOV R3, %0" :: "r"(vectorOut));
	__asm volatile("\n loop2:");
	__asm volatile("		LDR R4,[R2],+4");
	__asm volatile("		MUL R6,R4,R1");
	__asm volatile("		STR R6,[R3],+4");
	__asm volatile("		SUB R0,#1");
	__asm volatile("		CMP R0,#0");
	__asm volatile("		BNE loop2");



}

void productoEscalar16_asm (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar){

	__asm volatile("		MOV R0, %0" :: "r"(longitud));
	__asm volatile("		MOV R1, %0" :: "r"(escalar));
	__asm volatile("		MOV R2, %0" :: "r"(vectorIn));
	__asm volatile("		MOV R3, %0" :: "r"(vectorOut));
	__asm volatile("\n loop3:");
	__asm volatile("		LDR R4,[R2],+4");
	__asm volatile("		MUL R6,R4,R1");
	__asm volatile("		STR R6,[R3],+4");
	__asm volatile("		SUB R0,#1");
	__asm volatile("		CMP R0,#0");
	__asm volatile("		BNE loop3");

}


void productoEscalar12_asm (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar){

	__asm volatile("		MOV R0, %0" :: "r"(longitud));
	__asm volatile("		MOV R1, %0" :: "r"(escalar));
	__asm volatile("		MOV R2, %0" :: "r"(vectorIn));
	__asm volatile("		MOV R3, %0" :: "r"(vectorOut));
	__asm volatile("\n loop4:");
	__asm volatile("		LDR R4,[R2],+4");
	__asm volatile("		MUL R6,R4,R1");
	__asm volatile("		USAT R6,#16,R6");
	/*__asm volatile("		CMP R0,#(1<<12)");
	__asm volatile("		BLO sigo");
	__asm volatile("		MOV R6,#(1<<12)");
	__asm volatile("\n sigo:");*/
	__asm volatile("		STR R6,[R3],+4");
	__asm volatile("		SUB R0,#1");
	__asm volatile("		CMP R0,#0");
	__asm volatile("		BNE loop4");


}
void filtroVentana10_asm(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn){

}
void pack32to16_asm (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud){

}

int32_t max_asm (int32_t * vectorIn, uint32_t longitud){
	int32_t max=0;

	__asm volatile("		MOV R0, %0" :: "r"(longitud));
	__asm volatile("		MOV R1, %0" :: "r"(vectorIn));
	__asm volatile("		LDR R2,[R1],+4");
	__asm volatile("		SUB R0,#1");
	__asm volatile("		CMP R0,#0");
	__asm volatile("		BEQ salgo");
	__asm volatile("\n loop5:");
	__asm volatile("		LDR R3,[R1],+4");
	__asm volatile("		CMP R3,R2");
	__asm volatile("		BLT sigo2");
	__asm volatile("		MOV R2,R3");
	__asm volatile("\n sigo2:");
	__asm volatile("		SUB R0,#1");
	__asm volatile("		CMP R0,#0");
	__asm volatile("		BNE loop5");
	__asm volatile("\n salgo:");

	__asm volatile("		MOV %0,R2": "=r"(max));
	return max;
}
void downsampleM_asm (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N){

		__asm volatile("		MOV R0, %0" :: "r"(longitud));
		__asm volatile("		ADD R0,#1");
		__asm volatile("		MOV R1, %0" :: "r"(N));
		__asm volatile("		MOV R2, %0" :: "r"(vectorIn));
		__asm volatile("		MOV R3, %0" :: "r"(vectorOut));
		__asm volatile("		MOV R4, #1");
		__asm volatile("		CMP R0,R4");
		__asm volatile("		BEq salir");
		__asm volatile("\n loop8:");

		__asm volatile("		MOV R6,R4");
		__asm volatile("\n restando:");
		__asm volatile("		SUB R6,R1");
		__asm volatile("		CMP R6,#0");
		__asm volatile("		BGT restando");
		__asm volatile("		BEQ restocero");
		__asm volatile("		LDR R5,[R2]");
		__asm volatile("		STR R5,[R3],#+4");
		__asm volatile("\n restocero:");
		__asm volatile("		ADD R2,#+4");
		__asm volatile("		ADD R4,#1");
		__asm volatile("		CMP R4,R0");
		__asm volatile("		BNE loop8");
		__asm volatile("\n salir:");



}


void invertir_asm (uint16_t * vector, uint32_t longitud){

	__asm volatile("		MOV R0, %0" :: "r"(longitud));
	__asm volatile("		MOV R2, %0" :: "r"(vector));
	__asm volatile("		MOV R1, #2");
	__asm volatile("		RSB R3,R1,R0,LSL #1");
	__asm volatile("		MOV R0,R0,LSR #1 ");
	__asm volatile("\n loop7:");
	__asm volatile("		LDRH R4, [R2,R3]");
	__asm volatile("		LDRH R1, [R2]");
	__asm volatile("		STRH R1, [R2,R3]");
	__asm volatile("		MOV  R1, R4");
	__asm volatile("		STRH R1, [R2],#+2");
	__asm volatile("		SUB  R3, #4");
	__asm volatile("		SUB R0,R0,#1");
	__asm volatile("		CMP R0,#0");
	__asm volatile("		BNE loop7");


}
void corr_asm (int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud){}

