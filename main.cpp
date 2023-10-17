#include <iostream>
#include <stdexcept>
#include <cmath>
int main(){
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
//This takes the remainder of two numbers
int modulo(int operand1, int operand2){
	if (operand2 != 0){
		return operand1 % operand2;
	}else{
		throw std::invalid_argument( "Cannot use modulo with 0" );
	}
}

//Comment added for practice.
// Multiplies two numbers.
int multiply(int a, int b) {
  return a * b;
}

//This takes a number and raises it to a power
int exponentiation(int base, int power){
	return pow(base,power);
}

