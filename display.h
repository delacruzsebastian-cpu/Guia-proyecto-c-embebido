
#if !defined(DISPLAY_H)
#define DISPLAY_H
#ifdef __cplusplus
extern "C" {
#endif
#include <avr/io.h>
typedef struct D_Display D_Display;
typedef signed char int8_t;
typedef unsigned char uint8_t;
#define UNIDADES 1// si e estado esta en este muestro unidades
#define DECENAS  2// si el estado esta en este muestro decenas

#define PUERTOTRANS PORTD

/*el transistor que habilita el display de unidades esta en el puerto B bit 2*/
#define TRANDISPUNIDADES 0b00000100

/*el transistor que habilita el display de unidades esta en el puerto C bit 5*/
#define TRANDISPDECENAS 0b00100000

struct D_Display
{
    int8_t *tempUnidades;
    int8_t *tempDecenas;
    int8_t mostrando;
};

//funciones para  procesar display
void D_Procese_display (D_Display *disp);


//funciones de  display
void D_inicie_display (D_Display *disp,int8_t *tempUnidades,int8_t *tempDecenas);
void D_apague_display (D_Display *disp);
void muestre_en_display(uint8_t digito  , uint8_t display );

//lector de tabla de lookup entra numero sale en BCD
int8_t num2BCD(int8_t num);



#ifdef __cplusplus
} // extern "C"
#endif
#endif


