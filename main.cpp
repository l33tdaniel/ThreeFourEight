#include <iostream>
#include <stdexcept>
#include <string>
int main(){
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

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

//This test to ensure that every character is valid
bool validChar(char ch){
	// char validset[] = "+-*/%^()"; This can be used if we don't import string class'
	std::string validset = "+-*/%^()";
	//Tests if character is a digit or if a position exists in validset if not retruns npos.
	if(isdigit(ch) == true || validset.find(ch) != std::string::npos){
		return true;
	}else{
		return false;
			//Could make this void and throw error.
	}
}
