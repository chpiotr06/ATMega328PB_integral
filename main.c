/*
 * integral.c
 *
 * Created: 17.05.2022 13:27:39
 * Author : Piotr
 */ 

#include <avr/io.h>
#include <avr/sleep.h>

void initialize();
float calculateFunction(float);
float rectangleIntegral(float, float, float);
float trapezoidalIntegral(float, float, float);

int main(void){
    initialize();
	float variable;
	variable = rectangleIntegral(0, 2, 0.0001);
	PORTB=0x80;
	PORTD=variable;
	
	
}

float calculateFunction(float x) {
	return 2*x*x + x + 1;
}

void initialize(){
	DDRD=0xff;
	DDRB=0xff;
}

float trapezoidalIntegral(float lowBound, float highBound, float dx){
	float integral, points = (highBound - lowBound)/dx;
	
	return integral;
}

float rectangleIntegral(float lowBound, float highBound, float dx){
	float integral = 0.0, points = (highBound - lowBound)/dx;
	
	for (int i=0; i<points; i++){
		integral += dx * (calculateFunction(lowBound + dx*i));
	}
	
	return integral;
}

