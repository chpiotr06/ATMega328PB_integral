/*
 * integral.c
 *
 * Created: 17.05.2022 13:27:39
 * Author : Piotr Chmielowiec, Dominik Budzynsky
 */ 

#include <avr/io.h>
#include <math.h> // optional import if user wants to use more math functions 

#define e 2.71828182846
#define pi 3.14159265359

void initialize();
float calculateFunction(float);
float rectangleIntegral(float, float, float);
float trapezoidalIntegral(float, float, float);
float parabolicalIntegral(float, float, float);

int main(void){
    initialize();
	float trapezoidal, rectanular;
	float lowerBound, upperBound, dx;
	
	/* Add your parameters here */
	lowerBound = 5;   // lower integration limit
	upperBound = 10; // upper integration limit
	dx = 0.01;		// delta
	
	float parab = parabolicalIntegral(lowerBound, upperBound, dx);
	
	PORTB=0x80;
	PORTD=parab;
	
	
}


/* !!! In this place you should write function from which you want to calculate integral!!! */
float calculateFunction(float x) {
	return 2*x*x + x + 1;
}

void initialize(){
	DDRD=0xff;
	DDRB=0xff;
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

float parabolicalIntegral(float lowBound, float highBound, float dx){
	float integral = 0.0;
	
	integral = (highBound-lowBound)/6 * (calculateFunction(lowBound) + 4* calculateFunction((lowBound + highBound)/2) + calculateFunction(highBound));
	
	return integral;
}

