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

    // Order of Operations: ^*/%-+
    // what happens for negative numbers? We must consider addition of negatives and stuff like that


        for (int i = 0; i < expression.size(); i++) {
            if (expression[i] == "^" && i > 0 && i < (expression.size() - 1)) {
                double result = exponentiation(stod(expression[i - 1]), stod(expression[i + 1]));
                expression[i - 1] = to_string(result); // Update the base with the result
                expression.erase(expression.begin() + i, expression.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
        }
        for (int i = 0; i < expression.size(); i++) {
            if (expression[i] == "*" && i > 0 && i < (expression.size() - 1)) {
                double result = multiply(stod(expression[i - 1]), stod(expression[i + 1]));
                expression[i - 1] = to_string(result); // Update the base with the result
                expression.erase(expression.begin() + i, expression.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
        }
        for (int i = 0; i < expression.size(); i++) {
            if (expression[i] == "/" && i > 0 && i < (expression.size() - 1)) {
                double result = divide(stod(expression[i - 1]), stod(expression[i + 1]));
                expression[i - 1] = to_string(result); // Update the base with the result
                expression.erase(expression.begin() + i, expression.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
        }
        for (int i = 0; i < expression.size(); i++) {
            if (expression[i] == "%" && i > 0 && i < (expression.size() - 1)) {
                double result = modulo(stod(expression[i - 1]), stod(expression[i + 1]));
                expression[i - 1] = to_string(result); // Update the base with the result
                expression.erase(expression.begin() + i, expression.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
        }
        for (int i = 0; i < expression.size(); i++) {
            if (expression[i] == "-" && i > 0 && i < (expression.size() - 1)) {
                double result = subtraction(stod(expression[i - 1]), stod(expression[i + 1]));
                expression[i - 1] = to_string(result); // Update the base with the result
                expression.erase(expression.begin() + i, expression.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
        }
        for (int i = 0; i < expression.size(); i++) {
            if (expression[i] == "+" && i > 0 && i < (expression.size() - 1)) {
                if(expression[i+1] == "-"){
                    cout << "we got to the if line 115";
                }

                // we have to check if the next index is subtraction. I think we will have to do this for all elements



                double result = addition(stod(expression[i - 1]), stod(expression[i + 1]));
                expression[i - 1] = to_string(result); // Update the base with the result
                expression.erase(expression.begin() + i, expression.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
        }
    return expression[0]; // this is just a placeholder for now. we must change this later.
}

vector<string> parseFunction(string input){
    //cout << "input: " << input << endl; // printing what is passed through

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
                /*
                if (i > 0){
                    if (input[i-1] == '+'){
                        tempStr = "";
                        expression.push_back("-");
                    }
                }
                else if (i == 0){
                    tempStr = "";
                    expression.push_back("-");
                }
                else{
                    expression.push_back(tempStr);
                    tempStr = "";
                    expression.push_back("-");
                }
                break;
                */

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
                break;
        }
    }
    expression.push_back(tempStr);
    return expression;
}

string parenthesisSimplifier(string input, int indexesToRemove[2]) {
    // watch for warnings
    try{
        // this is going to work on eliminating everything that was originally in parenthesis and then passing back the original string to the function with the result in place of where the parenthesis were
        string tempStr = "";
        bool containsOperand = false;
        /*
        for(int i = 0; i < input.length(); i++){
            if (input[i] == '+' || input[i] == '-' || input[i] == '%' || input[i] == '/' || input[i] == '*' || input[i] == '^'){
                containsOperand = true;
                continue;
            }
        }
        */

        // check to see if any special characters are found, and if not 
        
        for(int i = 0; i < input.length(); i++){
            if(i > indexesToRemove[0] and i < indexesToRemove[1]){
                tempStr+=input[i];
            }
        }
        
        //cout <<"front i : " << indexesToRemove[0] << " Front value To remove = " << input[indexesToRemove[0]] << " Back value to remove" << input[indexesToRemove[1]] << endl;
        //cout << "Original input: " << input << " tempStr: " << tempStr << endl;

        vector<string> parsed = parseFunction(tempStr);
        //cout << "This is the parsed string from parseFunction" << parsed << endl;
        string front = input.substr(0, indexesToRemove[0]);
        string back  = input.substr(indexesToRemove[1]+1, input.length());
        //cout << "Front: " << front << " Back: " << back << " Calculate Parsed: " << calculate(parsed) << " returned from ParenthesisSimplifier: " << front + calculate(parsed) + back << endl;

        return (front + calculate(parsed) + back); // taking the front (before the substring) adding in the results from where the parenthesis were, and then throwing on the stuff that was in the back as well.
    }
    catch (const invalid_argument& e) {
        cerr << "Error in " << __FILE__ << " at line " << __LINE__ << ": Invalid argument - " << e.what() << endl;
        // Handle the error gracefully, e.g., return a default value or log the error.
    }
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
            // what happens here if we have negative numbers?
            vector<string> testing = parseFunction(input);
            for(int i = 0; i < testing.size(); i++){
                cout << testing[i] << "    " << i << endl;
            }
            cout << "Calculate: " << calculate(parseFunction(input)) << endl;
            // This is what's passed through: [-,7,+,3]












        }
        else {
            while (parenthCount != 0) { // this means there are no parenthesis left
                for (int i = 0; i < output.length(); i++) {
                    if (output[i] == '(') {
                        leftParenthCount += 1;
                        if (leftParenthCount == parenthCount) {
                            // cout << "Leftmost index to remove" << output[i] << endl;
                            subStringNums[0] = i;  // we might want to rethink this. This is grabbing how far through the array it goes before finding parenthesis
                            for (int j = i; j < output.length(); j++) {
                                if (output[j] != ')') {
                                    if (output[j] != '(') {
                                        parenthesisGroupings += output[j];
                                    }
                                }
                                else {
                                    subStringNums[1] = j;  // this one is working right. This is grabbing the index of the last element
                                    output = parenthesisSimplifier(output, subStringNums);
                                    // cout << "This is output: " << output << endl;
                                    break; // this is needed, otherwise it just keeps on running
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
    cerr << "Error in " << __FILE__ << " at line " << __LINE__ << ": Invalid argument - " << e.what() << endl;
    // Handle the error gracefully, e.g., return a default value or log the error.
}
    cout << "This is the final output" << output << endl;
    return "Something went wrong ";
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
        // cout << "\nThe input is valid, now calculating" << endl;
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
    
    //gatherInfo("(2+4)*2");
    //gatherInfo("(((2+4)))");
    //gatherInfo("7+(-3)");
    //gatherInfo("4+1+2+4");
    //gatherInfo("7+-3");
    gatherInfo("-4*3");
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