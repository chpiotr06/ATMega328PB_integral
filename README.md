# Piotr Chmielowiec and Dominik Budzynski project for ATMega328PB
## 1. Description
Project is aimed to calculate definite integral using numerical algorithm.
Algorithms:
1. [Rectangle Rule](https://en.wikipedia.org/wiki/Riemann_sum)
2. [Trapezoidal Rule](https://en.wikipedia.org/wiki/Trapezoidal_rule)
3. [Simpson's Rule](https://en.wikipedia.org/wiki/Simpson%27s_rule)

Result is displayed on seven segment, 4 digit display in carousel-like style.
Next digits appear in the right display and the rest is shifted to the left.
If result is less than 0, then most left display shows negative sign.
## 2. How to use
In current implementation, to run project you need to put `main.c` in your project directory.
Then provide program with function of your choice. Find this code (comment to make it easier is provided):
```
/* !!! In this place you should write function from which you want to calculate integral !!! */
float calculateFunction(float x) {
	return 2*x*x + x + 1;
}
```
`#include <math.h>` is provided so you can use functionalities from there. [Documentation](https://www.nongnu.org/avr-libc/user-manual/group__avr__math.html)

Then you need to provide parameters of definite integral. 
To do this, you need to find `main()` and inside it's body is this snippet: 
```
/* Add your parameters here */
lowerBound = 5;	  // lower integration limit
upperBound = 10; // upper integration limit
dx = 0.01;		// delta
```
It is self explainatory. dx is just a step. For example in rectangular rule from 0 to 1 and dx 0.01 you will have 100 small rectangles. 
The more rectangles you have. The longer it takes to calculate. However due to implementation limits and floating point error, result will never be exact.

If you want to change the function or parameters you need to push certain buttons on keypad:
- S4 button: Rectangle Rule
- S3 button: Trapezoidal Rule
- S2 button: Simpson's Rule 

## 3. Functions
1. `void initialize()` - initializes ports so port B and D can be outputs.
2. `float trapezoidalIntegral(float lowBound, float highBound, float dx)` - calculates definite integral using Trapezoidal Rule.
3. `float rectangleIntegral(float lowBound, float highBound, float dx)` - calculates definite integral using Rectangle Rule.
4. `parabolicalIntegral(float lowBound, float highBound)` - calculates definite integral using Simpson's Rule.
5. `void displayFloat(float number)` - display given floating point number in carousel-like style. After being called runs in infinite loop. Current implemetation does not allow to display numbers bigger than 99999.9
6. `displayError()` - displays *Err* in infinitloop when called. 
7. `displayOneDigit(int digit, int display)` - interface to display digit on given display.
8. `float calculateFunction(float x)` - calculates function values.
