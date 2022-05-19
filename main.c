/*
 * integral.c
 *
 * Created: 17.05.2022 13:27:39
 * Author : Piotr Chmielowiec, Dominik Budzynsky
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h> // optional import if user wants to use more math functions 

#define e 2.71828182846
#define pi 3.14159265359

volatile int option = 1;

/* !!! In this place you should write function from which you want to calculate integral!!! */
float calculateFunction(float x) {
	return 2*x*x + x + 1;
}

void initialize();
void displayOneDigit(int, int);
void displayError();
void displayFloat(float);
float calculateFunction(float);
float rectangleIntegral(float, float, float);
float trapezoidalIntegral(float, float, float);
float parabolicalIntegral(float, float);

int main(void){
    initialize();
	float rectangleInt, trapezoidalInt, parabolicalInt;
	float lowerBound, upperBound, dx;
	int oldOption = option;
	
	/* Add your parameters here */
	lowerBound = 5;	  // lower integration limit
	upperBound = 10; // upper integration limit
	dx = 0.01;		// delta
	
	rectangleInt = rectangleIntegral(lowerBound, upperBound, dx);
	trapezoidalInt = trapezoidalIntegral(lowerBound, upperBound, dx);
	parabolicalInt = parabolicalIntegral(lowerBound, upperBound);
	
	
	while (1){
		
		
		displayFloat(1.123);
		/*
		if (oldOption != option)
		{
			oldOption = option;
			
			if(option == 1) {
				integral = rectangleIntegral(lowerBound, upperBound, dx);
			} else if(option == 2) {
				integral = trapezoidalIntegral(lowerBound, upperBound, dx);
			} else if(option == 3) {
				integral = parabolicalIntegral(lowerBound, upperBound);
			}
		}
		displayFloat(integral);*/
	}
	
	
}


void initialize(){
	DDRD=0xff;
	DDRB=0xff;
	DDRC=0x00;
	PORTC=0xff;
}

float trapezoidalIntegral(float lowBound, float highBound, float dx){
	float integral = 0, points = (highBound - lowBound)/dx;
	
	for (int i=0; i<points -1; i++){
		integral += 0.5 * dx * (calculateFunction(lowBound + dx*i) + calculateFunction(lowBound + dx*(i+1)));
	}
	
	return integral;
}

float rectangleIntegral(float lowBound, float highBound, float dx){
	float integral = 0.0, points = (highBound - lowBound)/dx;
	
	for (int i=0; i<points; i++){
		integral += dx * (calculateFunction(lowBound + dx*i));
	}
	
	return integral;
}

float parabolicalIntegral(float lowBound, float highBound){
	float integral = 0.0;
	
	integral = (highBound-lowBound)/6 * (calculateFunction(lowBound) + 4* calculateFunction((lowBound + highBound)/2) + calculateFunction(highBound));
	
	return integral;
}

void displayFloat(float number){
	float numberCpy = number;
	if (number < 0.000){
		number *= -1;
	}
	
	if(number > 9999.9) {
		displayError();
	}
	
	volatile int dispDigits [10] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B};
	volatile int digitsToDisplay[10] = {0,0,0,0,0,0,0,0,0,0};
	volatile int numberOfDigits = 0, currentIter=0;
	volatile int integerPart = (int)number;
	volatile long decimalPart = (long)((number-integerPart)*100000); 

	if(number - integerPart < 0.0999 && number - integerPart > 0.05) decimalPart = 10000;
	if(number - integerPart <= 0.05 && number - integerPart >= 0.0001) {
		integerPart -= 1;
		decimalPart = 99999;
	}
	
	
	for (int i=9; i>0; i--){
		if(decimalPart > 0){
			digitsToDisplay[i] = dispDigits[(int)(decimalPart % 10)];
			numberOfDigits = numberOfDigits + 1;
			decimalPart = decimalPart/10;
		} else if ( integerPart > 0){
			digitsToDisplay[i] = dispDigits[(int)(integerPart % 10)];
			integerPart = integerPart/10;
			numberOfDigits = numberOfDigits + 1;
			if(i==4){
				digitsToDisplay[i] = (0b10000000 | digitsToDisplay[i]);
			}
		}
	}
	
	while(1){
		if (numberCpy > 0.0){
			for (int i=0; i<50; i++){
				displayOneDigit(digitsToDisplay[currentIter], 0b00001000);
				displayOneDigit(digitsToDisplay[currentIter + 1], 0b00000100);
				displayOneDigit(digitsToDisplay[currentIter + 2], 0b00000010);
				displayOneDigit(digitsToDisplay[currentIter + 3], 0b00000001);
			}
			
		} else {
			for (int i=0; i<50; i++){
				displayOneDigit(0x01, 0b00001000);
				displayOneDigit(digitsToDisplay[currentIter], 0b00000100);
				displayOneDigit(digitsToDisplay[currentIter + 1], 0b00000010);
				displayOneDigit(digitsToDisplay[currentIter + 2], 0b00000001);
			}
		}
		
		if(currentIter < 6){
			currentIter ++;
		} else {
			currentIter = 0;
		}
	}
	
}

void displayError(){
	while (1){
		displayOneDigit(0x4F, 0b00001000);
		displayOneDigit(0x05, 0b00000100);
		displayOneDigit(0x05, 0b00000010);
	}
}

void displayOneDigit(int digit, int display){
	PORTB = ~display;
	PORTD = ~digit;
	_delay_ms(10);
}
