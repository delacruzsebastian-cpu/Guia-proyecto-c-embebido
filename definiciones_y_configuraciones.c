#include "display.h"
#include "definiciones_y_configuraciones.h"
#include <avr/io.h>
#define cbi(byte, bit) (byte &= ~(1 << bit)) // Forzar un 0 en el bit (bit) del registro (reg) 
#define sbi(byte, bit) (byte |= (1 << bit)) // Forzar un 1 en el bit (bit) del registro (reg) 


void DyC_Procese_ADC(int8_t *temperatura,int8_t *tempUnidades,int8_t *tempDecenas)
{
    short adcval = leaADC();
    *temperatura = convierta_a_Celsius(adcval);
    *tempUnidades = saqueUnidades(*temperatura);
    *tempDecenas = saqueDecenas(*temperatura);
    *tempUnidades = num2BCD(*tempUnidades);
    *tempDecenas = num2BCD(*tempDecenas);

    //no tengo retun :P
}

void startADC()
{
	sbi(ADCSRA,ADPS2);
	sbi(ADCSRA,ADPS1);
	sbi(ADCSRA,ADPS0);
	//configuro MUX para entrada TEMP "1000"
	cbi(ADMUX,MUX0);
	cbi(ADMUX,MUX1);
	cbi(ADMUX,MUX2);
	sbi(ADMUX,MUX3);
	//configuro referencia de V en 1.1V
	sbi(ADMUX,REFS0);
	sbi(ADMUX,REFS1);
	//Enciendo el ADC
	sbi(ADCSRA,ADEN); 
	
}

short leaADC(void)
{	
	short lectura;
	
	lectura = ADCL;// se leen primero los 2 bits del registro ADCL
	lectura |= ((unsigned long)ADCH) << 8;//se agregan a los anteriores 2 bits, los 8 bits del registro ADCH
	
	return lectura;
	
}
int8_t convierta_a_Celsius(short adcval)
{	
	int8_t tempcel;	
	tempcel = ((((adcval-269)/1.024)-32)/2)+18; // Poner el dato convertido en grados Celcius
	
	return tempcel;
}
int8_t saqueUnidades(int8_t temperatura)
{	
	int8_t unidades;
	unidades = temperatura%10; //Sacar unidad
	
	return unidades;
}
int8_t saqueDecenas(int8_t temperatura)
{	
	int8_t decenas;
	decenas = temperatura/10; //Sacar decena
	
	return decenas;
}