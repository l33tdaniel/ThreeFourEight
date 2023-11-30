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
    for(int i =0; i < expression.length(); i++){
        if (expression[i] == '('){ 
            stack.push(expression[i]); 
            } 
        else if(expression[i]== ')'){
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
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
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
    // cout << "Input into parseFunction: " << input << endl;
    expression.push_back(tempStr); // we do this because if the last thing in the parenthesis is a number, it wouldn't get pushed back otherwise
    // before we return this, we're now going to want to do all the math that we can do now that we've parsed the string
    return expression;
}

string parenthesisSimplifier(string input, int indexesToRemove[2]) {
    // this is going to work on eliminating everything that was originally in parenthesis and then passing back the original string to the function with the result in place of where the parenthesis were
    string tempStr = "";
    
    bool containsOperand = false;
    for(int i = 0; i < input.length(); i++){
        if (input[i] == '+' || input[i] == '-' || input[i] == '%' || input[i] == '/' || input[i] == '*' || input[i] == '^'){
            containsOperand = true;
            continue;
        }
    }
    /*
    if (!containsOperand){
        return input.substr(0, 5);
    }
    */


    // check to see if any special characters are found, and if not 
    for(int i = 0; i < input.length(); i++){
        if(i > indexesToRemove[0] and i < indexesToRemove[1]){
            tempStr+=input[i];
        }
    }
    cout <<"front i : " << indexesToRemove[0] << " Front value To remove = " << input[indexesToRemove[0]] << " Back value to remove" << input[indexesToRemove[1]] << endl;
    cout << "Original input: " << input << " tempStr: " << tempStr << endl;

    vector<string> parsed = parseFunction(tempStr);
    //cout << "This is the parsed string from parseFunction" << parsed << endl;
    string front = input.substr(0, indexesToRemove[0]);
    string back  = input.substr(indexesToRemove[1]+1, input.length());
    cout << "Front: " << front << " Back: " << back << " Calculate Parsed: " << calculate(parsed) << " returned from ParenthesisSimplifier: " << front + calculate(parsed) + back << endl;

    return (front + calculate(parsed) + back); // taking the front (before the substring) adding in the results from where the parenthesis were, and then throwing on the stuff that was in the back as well.
}

string delimiter_info(string input) {
    string output = input;
    try{
        string temp = "";
        int parenthCount = 0;
        for (int i = 0; i < input.length(); i++) {
            char c = input[i];
            if (c == '(') {
                parenthCount++;
            }
        }
        string parenthesisGroupings;
        int subStringNums[2];
        int leftParenthCount = 0;
        if (parenthCount == 0) {
            return calculate(parseFunction(input));
        }
        else {
            while (parenthCount != 0) {
                for (int i = 0; i < output.length(); i++) {
                    if (output[i] == '(') {
                        leftParenthCount += 1;
                        if (leftParenthCount == parenthCount) {
                            subStringNums[0] = i;  // we might want to rethink this
                            for (int j = i; j < output.length(); j++) {
                                if (output[j] != ')') {
                                    if (output[j] != '(') {
                                        parenthesisGroupings += output[j];
                                    }
                                }
                                else {
                                    subStringNums[1] = j;  // this one is working right
                                    output = parenthesisSimplifier(output, subStringNums);
                                    cout << "This is output: " << output << endl;
                                }
                            }
                        }
                    }
                }
                parenthCount -= 1;
                leftParenthCount = 0;
            }
        }
        return calculate(parseFunction(output));
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid argument: " << e.what() << endl;
        // Handle the error gracefully, e.g., return a default value or log the error.
    }
    cout << "This is the final output" << output << endl;
    return "Something went wrong";
}

bool validChar(char ch){
	// char validset[] = "+-*/%^()"; This can be used if we don't import string class'
	string validset = "+-*/%^()";
	//outputs if character is a digit or if a position exists in validset if not retruns npos.
	if(isdigit(ch) == true || validset.find(ch) != string::npos){
		return true;
	}else{
		return false;
		//Could make this void and throw error.
	}
}

void gatherInfo(string expression){
    // takes info in from user, checks to make sure it's valid input, then starts passing it through to do the necessary operations
    //string expression;
    //cout << "Enter an expression: ";
    //cin >> expression;
    // string expression = "(2+4)-(3+9)-4%2"; 
    bool isValidParenthesis = isBalancedParanthesis(expression);
    bool isValidChars; 
    for(int i = 0; i < expression.size(); i++){
        isValidChars = validChar(expression[i]);
    }
    if(isValidChars && isValidParenthesis){
        // if the characters and both the amount and placement of parenthesis is correct, we proceed
        cout << "\nThe input is valid, now calculating" << endl;
        string output = delimiter_info(expression);
        cout << "Output: " << output;
    }
    else{
        // The input given is invalid, and we will inform the user how it's invalid.
        cout << "\nThe input is not valid" << endl;
        if (!isValidChars) {
            if(!isValidParenthesis){
                cout << "There are invalid characters and invalid parenthesis in your input" << endl;
            }
            else{
                cout << "There are invalid characters in your input" << endl;
            }
        }
        else if (!isValidParenthesis){
            cout << "Your input has invalid parenthesis" << endl;
        }
    }
}

int main(){
    // could we start adding references to code instead of passing the copy through so that our code is more efficient? This is the difference between lower level vs higher level thinking.
    
    //gatherInfo("2+4");
    gatherInfo("(((2+4)))");
	//gatherInfo("(22+14/24*(2*8))"); // this will likely cause an error. We should try and check for this

    // this breaks it (22+14/24*(2*8))^(4/3)
    //gatherInfo("2+4");
    return 0;

    /*
    The process of this program:
    gatherInfo(expression)
    isValidParenthesis(expression) # checking if there parenthesis match each other
    isValidChars(expression) # checking if all characters are valid
    */
}