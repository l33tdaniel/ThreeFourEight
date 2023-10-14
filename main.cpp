#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool isBalancedParanthesis(const string &expression){
    stack <char> stack;
    int count = 0;
    for(int i = 0; i <expression.length();i++){
        if (expression[i] == '(')
        {
            stack.push(expression[i]);
            }
        else if (expression[i] == ')'){
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
    cout<<isBalancedParanthesis(expression)<<endl;
    return 0;
}

