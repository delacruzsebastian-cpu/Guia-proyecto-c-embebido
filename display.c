#include "display.h"

int tablaBCD[12]={0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01100111, 0b01000000, 0b01000000};


void D_inicie_display (D_Display *disp,int8_t *tempUnidades,int8_t *tempDecenas)
{
    disp->tempUnidades=tempUnidades;
    disp->tempDecenas=tempDecenas;
    disp->mostrando=UNIDADES;
}


void D_Procese_display (D_Display *disp)
{
    switch(disp->mostrando){
        case UNIDADES://mostramos unidades
            disp->mostrando=DECENAS;// cambiar estado
            //muestro la conversión a unidades leidas por el ADC y convertidas
            muestre_en_display(*disp->tempUnidades,UNIDADES ); 

        break;
        case DECENAS://mostrar decenas
            disp->mostrando=UNIDADES;// cambiar estado
            muestre_en_display(*disp->tempDecenas,DECENAS ); 
        default:
            disp->mostrando=DECENAS;
    }
}

void muestre_en_display(uint8_t digito  , uint8_t display )
{	
	if(digito>=12||digito<0)
	{
		PORTB = ~tablaBCD[11]; 	 
	}
	if (digito<11||digito>0)
	{
		PORTB = ~tablaBCD[digito];
	}
    if(display==UNIDADES)
	{
        PUERTOTRANS &= ~TRANDISPDECENAS;
        PUERTOTRANS |= TRANDISPUNIDADES;
    }
    if(display==DECENAS)
	{
        PUERTOTRANS &= ~TRANDISPUNIDADES;
        PUERTOTRANS |= TRANDISPDECENAS;
    }
}

int8_t num2BCD(int8_t num)
{
    if(num>=12||num<0)
        return ~tablaBCD[11];/*en la pos 11 de la tabla esta el error*/
    return ~tablaBCD[num];
}





