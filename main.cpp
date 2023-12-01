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
    // We check in order of Exponents, modulo, multiplication, division, addition, subtraction
    // Order of Operations: ^*/%-+
    while (expression.size() != 1){
        for (int i = 0; i < expression.size(); i++) {
            bool hasExponent = false;
            bool hasModulo = false;
            bool hasMultiplication = false;
            bool hasDivision = false;
            for (int j = 0; j < expression.size(); j++){
                if (expression[j] == "^") { hasExponent = true; }
                if (expression[j] == "%") { hasModulo = true; }
                if (expression[j] == "/") { hasDivision = true; }
                if (expression[j] == "*") { hasMultiplication = true; }
            }

            if (expression[i] == "^" && i > 0 && i < (expression.size() - 1)) {
                double result = exponentiation(stod(expression[i - 1]), stod(expression[i + 1]));
                expression[i - 1] = to_string(result); // Update the base with the result
                expression.erase(expression.begin() + i, expression.begin() + i + 2); // Erase '^' and exponent elements
                i -= 2; // Adjust the loop counter after erasing two elements
            }
            else if (expression[i] == "%" && i > 0 && i < (expression.size() - 1)) {
                if (!hasExponent) {
                    double result = modulo(stod(expression[i - 1]), stod(expression[i + 1]));
                    expression[i - 1] = to_string(result); // Update the base with the result
                    expression.erase(expression.begin() + i, expression.begin() + i + 2); // Erase '%' and exponent elements
                    //for(int i = 0; i < expression.size(); i++) { cout << expression[i] << " "; } cout << "\n" << endl;
                    i -= 2; // Adjust the loop counter after erasing two elements
                }
            }
            else if (expression[i] == "*" && i > 0 && i < (expression.size() - 1)) {
                if (!hasExponent){
                    double result = multiply(stod(expression[i - 1]), stod(expression[i + 1]));
                    expression[i - 1] = to_string(result); // Update the base with the result
                    expression.erase(expression.begin() + i, expression.begin() + i + 2); // Erase '*' and exponent elements
                    //for(int i = 0; i < expression.size(); i++) { cout << expression[i] << " "; } cout << "\n" << endl;
                    i -= 2; // Adjust the loop counter after erasing two elements
                }
            }
            else if (expression[i] == "/" && i > 0 && i < (expression.size() - 1)) {
                if (!hasExponent){
                    double result = divide(stod(expression[i - 1]), stod(expression[i + 1]));
                    expression[i - 1] = to_string(result); // Update the base with the result
                    expression.erase(expression.begin() + i, expression.begin() + i + 2); // Erase '/' and exponent elements
                    //for(int i = 0; i < expression.size(); i++) { cout << expression[i] << " "; } cout << "\n" << endl;
                    i -= 2; // Adjust the loop counter after erasing two elements
                }
            }
            else if (expression[i] == "-" && i > 0 && i < (expression.size() - 1)) {
                if (!(hasExponent || hasModulo || hasMultiplication || hasDivision)){
                    double result = subtraction(stod(expression[i - 1]), stod(expression[i + 1]));
                    expression[i - 1] = to_string(result); // Update the base with the result
                    expression.erase(expression.begin() + i, expression.begin() + i + 2); // Erase '-' and exponent elements
                    //for(int i = 0; i < expression.size(); i++) { cout << expression[i] << " "; } cout << "\n" << endl;
                    i -= 2; // Adjust the loop counter after erasing two elements
                }
            }
            else if (expression[i] == "+" && i > 0 && i < (expression.size() - 1)) {
                if (!(hasExponent || hasModulo || hasMultiplication || hasDivision)){
                    double result = addition(stod(expression[i - 1]), stod(expression[i + 1]));
                    expression[i - 1] = to_string(result); // Update the base with the result
                    expression.erase(expression.begin() + i, expression.begin() + i + 2); // Erase '+' and exponent elements
                    //for(int i = 0; i < expression.size(); i++) { cout << expression[i] << " "; } cout << "\n" << endl;
                    i -= 2; // Adjust the loop counter after erasing two elements
                }   
            }
        }
    }
    return expression[0]; // this is just a placeholder for now. we must change this later.
}

vector<string> parseFunction(string input){
    cout << "input: " << input << endl; // printing what is passed through
    vector<string> expression;
    vector<double> result;
    string tempStr = "";
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        switch (c) {
            case '+':
                if(i > 0) {
                    if (input[i-1] == '-' || input[i-1] == '/'|| input[i-1] == '*'|| input[i-1] == '%'|| input[i-1] == '^'){
                        tempStr += "+";
                    }
                    
                    else{
                        expression.push_back(tempStr); // adding tempStr onto the stack
                        tempStr = "";
                        expression.push_back("+");
                    }
                }
                else if (i == 0){
                    tempStr += "+";
                }
                break;
            case '-':
                if (i > 0){
                    if (input[i-1] == '+' || input[i-1] == '/'|| input[i-1] == '*'|| input[i-1] == '%'|| input[i-1] == '^'){
                        tempStr+="-";
                    }
                    else{
                        expression.push_back(tempStr);
                        tempStr = "";
                        expression.push_back("-");
                    }
                }
                else if (i == 0){
                    tempStr += "-";
                }
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
                break;
        }
    }

    expression.push_back(tempStr);

    cout << "\n" << endl;
    for(int i = 0; i < expression.size(); i++){
        cout << i << " " << expression[i] << endl;
    }
    return expression;
}

string parenthesisSimplifier(string input, int indexesToRemove[2]) {
    // watch for warnings
    // cout << "input: " << input << " " << input[indexesToRemove[0]] << " " << input[indexesToRemove[1]] << " " << endl;
    try{
        // this is going to work on eliminating everything that was originally in parenthesis and then passing back the original string to the function with the result in place of where the parenthesis were
        string tempStr = "";
        bool containsOperand = false;
        // check to see if any special characters are found, and if not 
        for(int i = 0; i < input.length(); i++){
            if(i > indexesToRemove[0] and i < indexesToRemove[1]){
                tempStr+=input[i];
            }
        }

        //cout <<"front i : " << indexesToRemove[0] << " Front value To remove = " << input[indexesToRemove[0]] << " Back value to remove" << input[indexesToRemove[1]] << endl;
        //cout << "Original input: " << input << " tempStr: " << tempStr << endl;
        //cout << "this is where we got " << endl;
        vector<string> parsed = parseFunction(tempStr);
        
        //cout << "This is the parsed string from parseFunction" << parsed << endl;
        string front = input.substr(0, indexesToRemove[0]);
        string back  = input.substr(indexesToRemove[1]+1, input.length());
        string canPassBack = "";
        /*
        for(int i = 0; i < parsed.size(); i++) {
            cout << parsed[i] << endl;
        }
        */
        // checking if there are two minuses and turning it into a plus
        cout << "\n" << endl;
        for (auto it = parsed.begin(); it != parsed.end(); ++it) {
            // Check if the current and next elements are both "-"
            if (*it == "-" && (it + 1) != parsed.end() && *(it + 1) == "-") {
                // Remove the first index
                it = parsed.erase(it);
                // Change the value of the second index to "+"
                *it = "+";
                // Decrement the iterator to account for the loop increment
                --it;
            }
        }
        // checking if there are 2 plusses and turning it into one plus
        /*
        for (auto it = parsed.begin(); it != parsed.end(); ++it) {
            // Check if the current and next elements are both "-"
            if (*it == "+" && (it + 1) != parsed.end() && *(it + 1) == "+") {
                // Remove the first index
                it = parsed.erase(it);
                // Change the value of the second index to "+"
                *it = "+";
                // Decrement the iterator to account for the loop increment
                --it;
            }
        }
        */
        if (parsed.size() == 2) {
            cout << "The size is two";
        // this means that it's two elements, which I think would only ever be a + or a - and a number, so we just combine them
            if(parsed[0] == "+"){
                return (front + parsed[1] + back);
            }
            else{
                canPassBack = parsed[0] + parsed[1];
                return (front + canPassBack + back);
            }
        }
        if (parsed.size() == 3){
                // I THINK THAT WE HAVE TO LOOP THROUGH _ I DONT THINK THIS WILL WORK LIKE THIS




            // checking for if a number has something like minus minus
        }

        cout << "Front: " << front << " Back: " << back << " Calculate Parsed: " << calculate(parsed) << " returned from ParenthesisSimplifier: " << front + calculate(parsed) + back << endl;
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

    // gatherInfo("2++2"); // should it even take this?
    //gatherInfo("-(-3)");
    gatherInfo("(((((((((5)))))))))");
    //gatherInfo("-(+2) * (+3) - (-4) / (-5)"); // answer should be -6.8
    return 0;
}