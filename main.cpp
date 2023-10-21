#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>
#include <cmath>
#include <vector>
using namespace std;

// what we need to do is take out what's there, replace it with the expression, then we're done

bool isBalancedParanthesis(const string &expression){
    // this goes through to make sure that the amount of parenthesis is even and that everything lines up
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

double modulo(double operand1, double operand2) {
    if (operand2 != 0.0) {
        return fmod(operand1, operand2);
    } else {
        throw invalid_argument("Cannot use modulo with 0");
    }
}
double multiply(float a, float b) {
    // performs multiplication
    return a * b;
}
double addition(float a, float b) {
    // adds two numbesr together
    return a + b;
}
double divide(float a, float b){
    // divides two numbers, BUT DOESNT HAVE ERROR HANDLING YET
    if (b != 0) {
        return a/b;
    }
    else {
        // we will have to do error handling here!
        return false;
    }
}
double subtraction(float a, float b){
    // performs subtraction of two numbers
    return a-b;
}
double exponentiation(double base, double power) {
    // This takes a number and raises it to a power
    return pow(base, power);
}


string calculate(vector<string> expression){
    // We check in order of Exponents, multiplication, division, modulo, addition, subtraction
    // this is going to do the logic of adding things to the stack and then passing it off to the following functions above. Make sure to use PEMDAS!!!

    vector<string> temp = expression;

        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] == "^" && i > 0 && i < (temp.size() - 1)) {
                double result = exponentiation(stod(temp[i - 1]), stod(temp[i + 1]));
                temp[i - 1] = to_string(result); // Update the base with the result
                temp.erase(temp.begin() + i, temp.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
        }
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] == "*" && i > 0 && i < (temp.size() - 1)) {
                double result = multiply(stod(temp[i - 1]), stod(temp[i + 1]));
                temp[i - 1] = to_string(result); // Update the base with the result
                temp.erase(temp.begin() + i, temp.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
        }
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] == "/" && i > 0 && i < (temp.size() - 1)) {
                double result = divide(stod(temp[i - 1]), stod(temp[i + 1]));
                temp[i - 1] = to_string(result); // Update the base with the result
                temp.erase(temp.begin() + i, temp.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
        }
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] == "%" && i > 0 && i < (temp.size() - 1)) {
                double result = modulo(stod(temp[i - 1]), stod(temp[i + 1]));
                temp[i - 1] = to_string(result); // Update the base with the result
                temp.erase(temp.begin() + i, temp.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
        }
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] == "-" && i > 0 && i < (temp.size() - 1)) {
                double result = subtraction(stod(temp[i - 1]), stod(temp[i + 1]));
                temp[i - 1] = to_string(result); // Update the base with the result
                temp.erase(temp.begin() + i, temp.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
        }
        for (int i = 0; i < temp.size(); i++) {
            if (temp[i] == "+" && i > 0 && i < (temp.size() - 1)) {
                double result = addition(stod(temp[i - 1]), stod(temp[i + 1]));
                temp[i - 1] = to_string(result); // Update the base with the result
                temp.erase(temp.begin() + i, temp.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
        }
    return temp[0]; // this is just a placeholder for now. we must change this later.
}

vector<string> parseFunction(string input){
    vector<string> expression;
    vector<double> result;
    string tempStr = "";
    for(char c : input) {
        switch (c) {
            case '+':
                expression.push_back(tempStr);
                tempStr = "";
                expression.push_back("+");
                break;
            case '-':
                expression.push_back(tempStr);
                tempStr = "";
                expression.push_back("-");
                break;
            case '*':
                expression.push_back(tempStr);
                tempStr = "";
                expression.push_back("*");
                break;
            case '/':
                expression.push_back(tempStr);
                tempStr = "";
                expression.push_back("/");
                break;
            case '%':
                expression.push_back(tempStr);
                tempStr = "";
                expression.push_back("%");
                break;
            case '^':
                expression.push_back(tempStr);
                tempStr = "";
                expression.push_back("^");
                break;
            default:
                tempStr += c;
        }
    }

    expression.push_back(tempStr); // we do this because if the last thing in the parenthesis is a number, it wouldn't get pushed back otherwise
    // before we return this, we're now going to want to do all the math that we can do now that we've parsed the string
    return expression;
}

string parenthesisSimplifier(string input, int indexesToRemove[2]) {
    // this is going to work on eliminating everything that was originally in parenthesis and then passing back the original string to the function with the result in place of where the parenthesis were
    string tempStr = "";
    for(int i = 0; i < input.length(); i++){
        if(i > indexesToRemove[0] and i < indexesToRemove[1]){
            tempStr+=input[i];
        }
    }
    // now that we have this tempstring, we want to do the operations in it, and then pass it back to the original function as a string
    vector<string> parsed = parseFunction(tempStr);
    string front = input.substr(0, indexesToRemove[0]);
    string back = input.substr(indexesToRemove[1], input.length());

    return (front + calculate(parsed) + back); // taking the front (before the substring) adding in the results from where the parenthesis were, and then throwing on the stuff that was in the back as well.
}

string delimiter_info(string input) {
    string temp = "";
    int parenthCount = 0;
    for(int i = 0; i < input.length(); i++) {
        if(input[i] == '('){parenthCount += 1;}
    }
    // now we would go in order of operations, add everything to a stack while the number is not 0, and we'd decrease it with every pass, after that we return the product to the user, and we're done. I don't wanna do the full thing, but that's a great start!

    string parenthesisGroupings[parenthCount];
    int totalParenthCount = parenthCount;
    int beginning = 0;
    int subStringNums[2];
    if(parenthCount == 0) {

        return calculate(parseFunction(input));
    }
    else{
        while(parenthCount!=0){
            // we need to take in a string, subtract a smaller part of the string, and then give it back
            int leftParenthCount = 0;
            for(int i = 0; i < input.length(); i++){
                if(input[i] == '(') { // if we hit an open parentheses
                    leftParenthCount += 1; // adding one to the amount of parenthesis that we've passed
                    if(leftParenthCount == parenthCount){
                        subStringNums[0] = i;
                        // if the count is at the total count that we're going for (the last index of it)
                        for(int j = i; j < input.length(); j++){ // for each following letter that is not ')'
                            if(input[j]!=')'){ 
                                if(input[j]!='(') {
                                    parenthesisGroupings[beginning] += input[j];
                                }
                            }
                            else{ // input[j] == ')'
                                // we need to make a new string that doesn't have the parts we removed and then break out
                                subStringNums[1] = j;
                                string test = parenthesisSimplifier(input, subStringNums);
                                break;
                            }
                        }
                    }
                }
            }
            beginning++;
            parenthCount--;
        }
    }
    return "derp";
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

void gatherInfo(){
    // takes info in from user, checks to make sure it's valid input, then starts passing it through to do the necessary operations
    //string expression;
    //cout << "Enter an expression: ";
    //cin >> expression;
    string expression = "45/2+93+7.356*29+((14)+972/41)";
    //string expression = "(2+14*3/4+9^2%7-2)"; // answer is 14.5
    bool isValidParenthesis = isBalancedParanthesis(expression);
    bool validChars; 
    for(int i = 0; i < expression.size(); i++){
        validChars = validChar(expression[i]);
    }
    if(validChars && isValidParenthesis){
        string output = delimiter_info(expression);
        cout << "Output: " << output;
        // now we have to start splitting up the code using our delimiters...
        cout << "\nThe input is valid, now calculating" << endl;
    }
    else{
        cout << "\nThe input is not valid" << endl;
    }
}

int main(){
    // could we start adding references to code instead of passing the copy through so that our code is more efficient? This is the difference between lower level vs higher level thinking.
    gatherInfo();
    return 0;
}