#include <iostream>


int main(){
    string expression;
    cout << "Enter an expression: " << endl;
    cin >> expression;
    cout<<isBalancedParanthesis(expression)<<endl;
    return 0;
}

int modulo(int operand1, int operand2){
	if (operand2 != 0){
		return operand1 % operand2;
	}else{
		throw std::invalid_argument( "Cannot use modulo with 0" );
	}
}

// Multiplies two numbers
int multiply(int a, int b) {
  return a * b;
}
