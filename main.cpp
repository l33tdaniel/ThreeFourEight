#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isBalancedParanthesis(const string &expression){
    stack<char> stack;
    for(int i =0; i<expression.length();i++){
        if (expression[i] == '(')
        {
            stack.push(expression[i]);
        } else if(expression[i]== ')')
        {
            if (stack.empty()){
                return false;
            }
            else{
                stack.pop();
            }
        }
    }
    return stack.empty();
}

int main(){
    string expression;
    cout << "Enter an expression: " << endl;
    cin >> expression;
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
