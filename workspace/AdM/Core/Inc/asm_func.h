#pragma once

#include <stdint.h>


void asm_svc (void);
uint32_t asm_sum (uint32_t firstOperand, uint32_t secondOperand);
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
void corrSIMD_asm (int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud);
void eco_asm (int16_t *vectorX,int16_t *vectorY,uint32_t longitud);
void ecoSIMD_asm (int16_t *vectorX,int16_t *vectorY,uint32_t longitud);
