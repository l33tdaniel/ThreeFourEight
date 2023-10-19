#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>
#include <cmath>
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
//This takes the remainder of two numbers
int modulo(int operand1, int operand2){
	if (operand2 != 0){
		return operand1 % operand2;
	}else{
		throw invalid_argument( "Cannot use modulo with 0" );
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
	string validset = "+-*/%^()";
	//Tests if character is a digit or if a position exists in validset if not retruns npos.
	if(isdigit(ch) == true || validset.find(ch) != string::npos){
		return true;
	}else{
		return false;
			//Could make this void and throw error.
	}
}

//This takes a number and raises it to a power
int exponentiation(int base, int power){
	return pow(base,power);
}

