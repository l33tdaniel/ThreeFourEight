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

//This takes the remainder of two numbers
int modulo(int operand1, int operand2){
	if (operand2 != 0){
		return operand1 % operand2;
	}else{
		throw invalid_argument( "Cannot use modulo with 0" );
	}
}

// Multiplies two numbers.
int multiply(float a, float b) {
  return a * b;
}
int addition(float a, float b) {
    return a + b;
}
int divide(float a, float b){
    if (b != 0) {
        return a/b;
    }
    else {
        // we will have to do error handling here!
        return false;
    }
}
int subtraction(float a, float b){
    return a-b;
}
void delimiter_info(string input) {
/*
start out by thinking of a list of rules. According to Saeidian, a constant can't come before an open parenthesis. here's a few more
no operand should follow another operand unless it's - or (
make sure no number is too big or too small for the program
must do pemdas when adding them to the stack (Parenthesis, Exponents, division, addition, subtraction)

Also, we know that if it got here, it passed the parenthesis test meaning that it has an even number, so that's the first thing that we can split up
*/
    string temp = "";
    int parenthCount = 0;
    int exponentCount = 0;
    int multiplyCount = 0;
    int moduloCount = 0;
    int divideCount = 0;
    int addCount = 0;
    int subtractCount = 0;

    for(int i = 0; i < input.length(); i++) {
        // I figure that we could go through this, hunt for each delimiter, and then add it to a stack
        if(input[i]      == '('){parenthCount  += 1;}
        else if(input[i] == '^'){exponentCount += 1;}
        else if(input[i] == '*'){multiplyCount += 1;}
        else if(input[i] == '/'){divideCount   += 1;}
        else if(input[i] == '%'){moduloCount   += 1;}
        else if(input[i] == '+'){addCount      += 1;}
        else if(input[i] == '-'){subtractCount += 1;}

        cout << input[i];
    }
    cout << "\nParenthesis: " << parenthCount << " Exponent Count: " << exponentCount << " Multiply Count: " << multiplyCount << " Divide Count: " << divideCount << " Modulo Count: " << moduloCount << " Add count: " << addCount << " Subtraction Count " << subtractCount << "\n";
    // now we would go in order of operations, add everything to a stack while the number is not 0, and we'd decrease it with every pass, after that we return the product to the user, and we're done. I don't wanna do the full thing, but that's a great start!

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

void gatherInfo(){
    //string expression;
    //cout << "Enter an expression: ";
    //cin >> expression;
    string expression = "(2+14)*3";
    bool isValidParenthesis = isBalancedParanthesis(expression);
    bool validChars;
    for(int i = 0; i < expression.size(); i++){
        validChars = validChar(expression[i]);
    }
    if(validChars && isValidParenthesis){
        delimiter_info(expression);
        // now we have to start splitting up the code using our delimiters...
        cout << "The input is valid, now calculating" << endl;
    }
    else{
        cout << "The input is not valid" << endl;
    }
}

int main(){
    // could we start adding references to code instead of passing the copy through so that our code is more efficient? This is the difference between lower level vs higher level thinking.
    gatherInfo();
    return 0;
}