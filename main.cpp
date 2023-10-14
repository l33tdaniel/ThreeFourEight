#include <iostream>
#include <stdexcept>
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

