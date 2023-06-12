#include "init.h"
#include "asm_func.h"


/******************************************
Definiciones General para probar
*******************************************/

#define ESCALAR 3
#define M 2

/******************************************
Definiciones saturación
*******************************************/
#define BITSAT 12

/******************************************
Definicines Rutina filtro de Ventana
*******************************************/

#define VENTANA 11
/******************************************
Definiciones Rutina de ECO
*******************************************/
#define RATE 44100 //muestras por mili segundo
#define TIEMPO_ECO 0.02
#define MUESTRA_ECO (uint32_t)(RATE*TIEMPO_ECO) //puedo probarlo con 2



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
void eco_c (int16_t *vectorX,int16_t *vectorY,uint32_t longitud);
static void PrivilegiosSVC (void);

/******************************************
Vectores armados para poder ir probando las funciones en C y Asm
*******************************************/

//32 bits sin signo
uint32_t vectorIn_uint32_t[]={1,2,3,4,5,6,7,8,9,10};
uint32_t vectorInAsm_uint32_t[]={1,2,3,4,5,6,7,8,9,10};

uint32_t vectorOut_uint32_t[]={0,0,0,0,0,0,0,0,0,0};
uint32_t vectorOutAsm_uint32_t[]={0,0,0,0,0,0,0,0,0,0};

//32 bits con signo

int32_t vectorIn_int32_t[]={1,2,3,4,5,6,7,8,9,10};
int32_t vectorInAsm_int32_t[]={1,2,3,4,5,6,7,8,9,10};

int32_t vectorOut_int32_t[]={0,0,0,0,0,0,0,0,0,0};
int32_t vectorOutAsm_int32_t[]={0,0,0,0,0,0,0,0,0,0};

//16 bits sin signo
uint16_t vectorIn_uint16_t[]={1,2,3,4,5,6,7,8,9,10};
uint16_t vectorInAsm_uint16_t[]={1,2,3,4,5,6,7,8,9,10};

uint16_t vectorOut_uint16_t[]={0,0,0,0,0,0,0,0,0,0};
uint16_t vectorOutAsm_uint16_t[]={0,0,0,0,0,0,0,0,0,0};

//16 bits con signo
int16_t vectorOut_int16_t[]={0,0,0,0,0,0,0,0,0,0};
int16_t vectorOutAsm_int16_t[]={0,0,0,0,0,0,0,0,0,0};

int16_t vectorX_int16_t[]={1,2,3,4,5,6,7,8,9,10};
int16_t vectorXAsm_int16_t[]={1,2,3,4,5,6,7,8,9,10};

int16_t vectorY_int16_t[]={1,2,3,4,5,6,7,8,9,10};
int16_t vectorYAsm_int16_t[]={1,2,3,4,5,6,7,8,9,10};



int main(void){
	//int32_t max;
	init();
  	PrivilegiosSVC ();
    //zeros_c(vectorIn_uint32_t,sizeof(vectorIn_uint32_t)/sizeof(uint32_t));
    //zeros_asm(vectorInAsm_uint32_t,sizeof(vectorInAsm_uint32_t)/sizeof(uint32_t));
    //productoEscalar32_c(vectorIn_uint32_t,vectorOut_uint32_t,sizeof(vectorIn_uint32_t)/sizeof(uint32_t),ESCALAR);
	//productoEscalar32_asm(vectorInAsm_uint32_t,vectorOutAsm_uint32_t,sizeof(vectorInAsm_uint32_t)/sizeof(uint32_t),ESCALAR);
  	//productoEscalar16_c(vectorIn_uint16_t,vectorOut_uint16_t,sizeof(vectorIn_uint16_t)/sizeof(uint16_t),ESCALAR);
	//productoEscalar16_asm(vectorInAsm_uint16_t,vectorOutAsm_uint16_t,sizeof(vectorInAsm_uint16_t)/sizeof(uint16_t),ESCALAR);
	//productoEscalar12_c(vectorIn_uint16_t,vectorOut_uint16_t,sizeof(vectorIn_uint16_t)/sizeof(uint16_t),ESCALAR);
	//productoEscalar12_asm(vectorInAsm_uint16_t,vectorOutAsm_uint16_t,sizeof(vectorInAsm_uint16_t)/sizeof(uint16_t),ESCALAR);
	//pack32to16_c (vectorIn_int32_t, vectorOut_int16_t,sizeof(vectorIn_uint32_t)/sizeof(int32_t));
	//pack32to16_asm (vectorInAsm_int32_t, vectorOutAsm_int16_t,sizeof(vectorInAsm_uint32_t)/sizeof(int32_t));
    //max=max_c (vectorIn_int32_t,sizeof(vectorIn_uint32_t)/sizeof(int32_t));

    //max=max_asm (vectorInAsm_int32_t,sizeof(vectorInAsm_uint32_t)/sizeof(int32_t));
    //invertir_c (vectorIn_uint16_t, 10);
    //invertir_asm (vectorInAsm_uint16_t, 10);
  	corr_c(vectorX_int16_t, vectorY_int16_t, vectorOut_int16_t,sizeof(vectorX_int16_t)/sizeof(int16_t));
  	corrSIMD_asm(vectorXAsm_int16_t, vectorYAsm_int16_t, vectorOutAsm_int16_t,sizeof(vectorXAsm_int16_t)/sizeof(int16_t));
  	corr_asm(vectorXAsm_int16_t, vectorYAsm_int16_t, vectorOutAsm_int16_t,sizeof(vectorXAsm_int16_t)/sizeof(int16_t));

    //eco_c(vectorX_int16_t, vectorY_int16_t,sizeof(vectorX_int16_t)/sizeof(int16_t));
  	//eco_asm(vectorXAsm_int16_t, vectorYAsm_int16_t,sizeof(vectorXAsm_int16_t)/sizeof(int16_t));
  	//ecoSIMD_asm(vectorXAsm_int16_t, vectorYAsm_int16_t,sizeof(vectorXAsm_int16_t)/sizeof(int16_t));
  	//downsampleM_c (vectorIn_int32_t, vectorOut_int32_t, sizeof(vectorIn_int32_t)/sizeof(int32_t),M);
  	//downsampleM_asm (vectorInAsm_int32_t, vectorOutAsm_int32_t, sizeof(vectorInAsm_int32_t)/sizeof(int32_t),M);
	//filtroVentana10_c(vectorIn_uint16_t, vectorOut_uint16_t, sizeof(vectorIn_uint16_t)/sizeof(uint16_t));
  	//filtroVentana10_asm(vectorInAsm_uint16_t, vectorOutAsm_uint16_t, sizeof(vectorInAsm_uint16_t)/sizeof(uint16_t));
    for(;;);
}

/**
  * @brief  zeros_c
  * @param  uint32_t vector
  * @param  uint32_t longitud
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 13/05/2023
*/


void zeros_c (uint32_t * vector, uint32_t longitud){
	while(longitud--)*(vector++)=0;
}

/**
  * @brief  productoEscalar32_c
  * @param  uint32_t * vectorIn
  * @param  uint32_t * vectorOut
  * @param  uint32_t longitud
  * @param  uint32_t escalar
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 13/05/2023
*/

void productoEscalar32_c (uint32_t * vectorIn, uint32_t * vectorOut, uint32_t longitud, uint32_t escalar){
	while(longitud--)*(vectorOut++)=(*vectorIn++)*escalar;

}

/**
  * @brief  productoEscalar16_c
  * @param  uint16_t * vectorIn
  * @param  uint16_t * vectorOut
  * @param  uint32_t longitud
  * @param  uint16_t escalar
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 13/05/2023
*/


void productoEscalar16_c (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar){
	while(longitud--)*(vectorOut++)=(*vectorIn++)*escalar;
}

/**
  * @brief  productoEscalar12_c
  * @param  uint16_t * vectorIn
  * @param  uint16_t * vectorOut
  * @param  uint32_t longitud
  * @param  uint16_t escalar
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 13/05/2023
*/
void productoEscalar12_c (uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitud, uint16_t escalar){
	while(longitud--){
		if(((*vectorIn)*escalar)>((1<<BITSAT)-1)){
			*(vectorOut++)=((1<<BITSAT)-1);
			vectorIn++;
		}else *(vectorOut++)=*(vectorIn++);

	}

}


/**
  * @brief  filtroVentana10_c
  * @param  uint16_t * vectorIn
  * @param uint16_t * vectorOut
  * @param  uint32_t longitudVectorIn
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 13/05/2023
*/

void filtroVentana10_c(uint16_t * vectorIn, uint16_t * vectorOut, uint32_t longitudVectorIn){

	for(uint32_t i=0;i<longitudVectorIn;i++){
		uint32_t suma=0;
		int32_t indice=0;
		for(uint32_t j=0;j<(VENTANA);j++){
			indice=i-VENTANA/2+j;
			if(indice>=0 && indice <longitudVectorIn)suma+=vectorIn[indice];
		}
		vectorOut[i]=suma/VENTANA;
	}
}

/**
  * @brief  pack32to16_c
  * @param  int32_t * vectorIn
  * @param  int16_t *vectorOut
  * @param  uint32_t longitud
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 13/05/2023
*/
void pack32to16_c (int32_t * vectorIn, int16_t *vectorOut, uint32_t longitud){

	while(longitud--){
		if(*vectorIn<(1<<16))*(vectorOut++)=(int16_t )(*(vectorIn++));
		else *(vectorOut++)=((1<<16)-1);
	}

}

/**
  * @brief  max_c
  * @param  int32_t * vectorIn
  * @param  uint32_t longitud
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 13/05/2023
*/

int32_t max_c (int32_t * vectorIn, uint32_t longitud){
	int32_t maximo=*vectorIn;
	while(--longitud){
		if(maximo<*(vectorIn))maximo=*vectorIn;
		vectorIn++;
	}
	return maximo;
}

/**
  * @brief  downsampleM_c
  * @param  int32_t * vectorIn
  * @param  int32_t * vectorOut
  * @param  uint32_t longitud
  * @param  uint32_t N
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 13/05/2023
*/

void downsampleM_c (int32_t * vectorIn, int32_t * vectorOut, uint32_t longitud, uint32_t N){
	*(vectorOut++)=*(vectorIn++);
	uint32_t i=1;
	while(i++<longitud){
		if(!((i)%N))vectorIn++;
		else*(vectorOut++)=*(vectorIn++);
	}

}

/**
  * @brief  invertir_c
  * @param  uint16_t * vector
  * @param  uint32_t longitud
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 13/05/2023
*/

void invertir_c (uint16_t * vector, uint32_t longitud){
	uint16_t aux;
	while(longitud--){
		aux=vector[longitud];
		*(vector+longitud)=*vector;
		*(vector++)=aux;
	}
}

/**
  * @brief  invertir_c
  * @param  int16_t *vectorX
  * @param  int16_t *vectorY
  * @param  uint32_t longitud
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 13/05/2023
*/

void eco_c (int16_t *vectorX,int16_t *vectorY,uint32_t longitud){
	for(uint32_t i=0;i<longitud;i++){
		vectorY[i]=vectorX[i];
		if(i>=MUESTRA_ECO)vectorY[i]+=(vectorX[i-MUESTRA_ECO]/2);
	}

}


/**
  * @brief  corr_c
  * @param  int16_t *vectorX
  * @param  int16_t *vectorY
  * @param  int16_t *vectorCorr
  * @param  uint32_t longitud
  * @return void
  * @author Ing. Pavelek Israel
  * @version 1.0
  * @date 13/05/2023
*/

void corr_c (int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud){

	int16_t sxy;
    int32_t demora,i,j;

    for(demora = -longitud + 1; demora < (int32_t)longitud; demora++){
        sxy = 0;
        for(i=0; i<longitud; i++){
            j = i + demora;
            if((j < 0) || (j >= longitud))continue;
            else sxy += (vectorX[i] * vectorY[j]);
        }
        if(demora<1)vectorCorr[demora + longitud - 1] = sxy;
    }
}


static void PrivilegiosSVC (void){
    // Obtiene valor del registro de 32 bits del procesador llamado "control".
    // El registro guarda los siguientes estados:
    // bit 2: Uso de FPU en el contexto actual. Usado=1, no usado=0.
    // bit 1: Mapeo del stack pointer(sp). MSP=0, PSP=1.
    // bit 0: Modo de ejecucion en Thread. Privilegiado=0, No privilegiado=1.
    //        Recordar que este valor solo se usa en modo Thread. Las
    //        interrupciones siempre se ejecutan en modo Handler con total
    //        privilegio.
    uint32_t x = __get_CONTROL ();

    // Actividad de debug: Ver registro "control" y valor de variable "x".
    //__BKPT (0);

    x |= 1;
    // bit 0 a modo No privilegiado.
    __set_CONTROL (x);

    // En este punto se estaria ejecutando en modo No privilegiado.
    // Lectura del registro "control" para confirmar.
    x = __get_CONTROL ();

    // Actividad de debug: Ver registro "control" y valor de variable "x".
    //__BKPT (0);

    x &= ~1u;
    // Se intenta volver a modo Privilegiado (bit 0, valor 0).
    __set_CONTROL (x);

    // Confirma que esta operacion es ignorada por estar ejecutandose en modo
    // Thread no privilegiado.
    x = __get_CONTROL ();

    // Actividad de debug: Ver registro "control" y valor de variable "x".
    //__BKPT (0);

    // En este punto, ejecutando en modo Thread no privilegiado, la unica forma
    // de volver a modo privilegiado o de realizar cualquier cambio que requiera
    // modo privilegiado, es pidiendo ese servicio a un hipotetico sistema
    // opertivo de tiempo real.
    // Para esto se invoca por software a la interrupcion SVC (Supervisor Call)
    // utilizando la instruccion "svc".
    // No hay intrinsics para realizar esta tarea. Para utilizar la instruccion
    // es necesario implementar una funcion en assembler. Ver el archivo
    // asm_func.S.
    asm_svc ();

    // El sistema operativo (el handler de SVC) deberia haber devuelto el modo
    // de ejecucion de Thread a privilegiado (bit 0 en valor 0).
    x = __get_CONTROL ();

    // Fin del ejemplo de SVC
}
