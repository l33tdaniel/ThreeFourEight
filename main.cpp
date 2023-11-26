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
    // cout << "Input into parseFunction: " << input << endl;
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
    string back = input.substr(indexesToRemove[1]+1, input.length());
    // cout << "Front: " << front << " Back: " << back << " Calculate Parsed: " << calculate(parsed) << " What would be returned from ParenthesisSimplifier: " << front + calculate(parsed) + back << endl;
    return (front + calculate(parsed) + back); // taking the front (before the substring) adding in the results from where the parenthesis were, and then throwing on the stuff that was in the back as well.
}

string delimiter_info(string input) {
    string test = input;
    try{
        string temp = "";
        int parenthCount = 0;
        for (char c : input) {
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
                for (int i = 0; i < test.length(); i++) {
                    if (test[i] == '(') {
                        leftParenthCount += 1;
                        if (leftParenthCount == parenthCount) {
                            subStringNums[0] = i;  // Use '=' for assignment, not '=='
                            for (int j = i; j < test.length(); j++) {
                                if (test[j] != ')') {
                                    if (test[j] != '(') {
                                        parenthesisGroupings += test[j];
                                    }
                                }
                                else {
                                    subStringNums[1] = j;  // Use '=' for assignment, not '=='
                                    test = parenthesisSimplifier(test, subStringNums);
                                }
                            }
                        }
                    }
                }
                parenthCount -= 1;
                leftParenthCount = 0;
            }
        }
        return calculate(parseFunction(test));
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid argument: " << e.what() << endl;
        // Handle the error gracefully, e.g., return a default value or log the error.
    }
    cout <<"THIS IS TEST" << test << endl;
    return "bleh";
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
    //string expression = "25+(3/2)";
    string expression = "(2+4)-(3+9)-4%2"; 
    bool isValidParenthesis = isBalancedParanthesis(expression);
    bool validChars; 
    for(int i = 0; i < expression.size(); i++){
        validChars = validChar(expression[i]);
    }
    if(validChars && isValidParenthesis){
        cout << "\nThe input is valid, now calculating" << endl;
        string output = delimiter_info(expression);
        cout << "Output: " << output;
    }
    else{
        cout << "\nThe input is not valid" << endl;
        cout << "Valid Characters: " << validChars << '\n'; // 1 is true 0 is false
        cout << "Valid Parenthesis: " << isValidParenthesis << '\n'; // 1 is true 0 is false
    }
}

void testCases(){
    /* Doesn't need to be a function, just an example of different test cases we could use */
    // The top will be a list of the strings, and then the bottom part will be each individual string
    vector<string> tests = {
        "(2+4)-(3+9)-4%2", "(1+2)-(4+5)-2%1", "(2+4)-(5+7)-4%2", "(3+6)-(6+9)-6%3", "(4+8)-(7+11)-8%4",
        "(5+10)-(8+13)-10%5", "(6+12)-(9+15)-12%6", "(7+14)-(10+17)-14%7", "(8+16)-(11+19)-16%8", "(9+18)-(12+21)-18%9",
        "(10+20)-(13+23)-20%10", "(11+22)-(14+25)-22%11", "(12+24)-(15+27)-24%12", "(13+26)-(16+29)-26%13", "(14+28)-(17+31)-28%14",
        "(15+30)-(18+33)-30%15", "(16+32)-(19+35)-32%16", "(17+34)-(20+37)-34%17", "(18+36)-(21+39)-36%18", "(19+38)-(22+41)-38%19",
        "(20+40)-(23+43)-40%20", "(21+42)-(24+45)-42%21", "(22+44)-(25+47)-44%22", "(23+46)-(26+49)-46%23", "(24+48)-(27+51)-48%24",
        "(25+50)-(28+53)-50%25", "(26+52)-(29+55)-52%26", "(27+54)-(30+57)-54%27", "(28+56)-(31+59)-56%28", "(29+58)-(32+61)-58%29",
        "(30+60)-(33+63)-60%30", "(31+62)-(34+65)-62%31", "(32+64)-(35+67)-64%32", "(33+66)-(36+69)-66%33", "(34+68)-(37+71)-68%34",
        "(35+70)-(38+73)-70%35", "(36+72)-(39+75)-72%36", "(37+74)-(40+77)-74%37", "(38+76)-(41+79)-76%38", "(39+78)-(42+81)-78%39",
        "(40+80)-(43+83)-80%40", "(41+82)-(44+85)-82%41", "(42+84)-(45+87)-84%42", "(43+86)-(46+89)-86%43", "(44+88)-(47+91)-88%44",
        "(45+90)-(48+93)-90%45", "(46+92)-(49+95)-92%46", "(47+94)-(50+97)-94%47", "(48+96)-(51+99)-96%48", "(49+98)-(52+101)-98%49",
        "(50+100)-(53+103)-100%50", "(51+102)-(54+105)-102%51", "(52+104)-(55+107)-104%52", "(53+106)-(56+109)-106%53", "(54+108)-(57+111)-108%54",
        "(55+110)-(58+113)-110%55", "(56+112)-(59+115)-112%56", "(57+114)-(60+117)-114%57", "(58+116)-(61+119)-116%58", "(59+118)-(62+121)-118%59",
        "(60+120)-(63+123)-120%60", "(61+122)-(64+125)-122%61", "(62+124)-(65+127)-124%62", "(63+126)-(66+129)-126%63", "(64+128)-(67+131)-128%64",
        "(65+130)-(68+133)-130%65", "(66+132)-(69+135)-132%66", "(67+134)-(70+137)-134%67", "(68+136)-(71+139)-136%68", "(69+138)-(72+141)-138%69",
        "(70+140)-(73+143)-140%70", "(71+142)-(74+145)-142%71", "(72+144)-(75+147)-144%72", "(73+146)-(76+149)-146%73", "(74+148)-(77+151)-148%74",
        "(75+150)-(78+153)-150%75", "(76+152)-(79+155)-152%76", "(77+154)-(80+157)-154%77", "(78+156)-(81+159)-156%78", "(79+158)-(82+161)-158%79",
        "(80+160)-(83+163)-160%80", "(81+162)-(84+165)-162%81", "(82+164)-(85+167)-164%82", "(83+166)-(86+169)-166%83", "(84+168)-(87+171)-168%84",
        "(85+170)-(88+173)-170%85", "(86+172)-(89+175)-172%86", "(87+174)-(90+177)-174%87", "(88+176)-(91+179)-176%88", "(89+178)-(92+181)-178%89",
        "(90+180)-(93+183)-180%90", "(91+182)-(94+185)-182%91", "(92+184)-(95+187)-184%92", "(93+186)-(96+189)-186%93", "(94+188)-(97+191)-188%94",
        "(95+190)-(98+193)-190%95", "(96+192)-(99+195)-192%96", "(97+194)-(100+197)-194%97", "(98+196)-(101+199)-196%98", "(99+198)-(102+201)-198%99",
        "(100+200)-(103+203)-200%100", "40 + 12", "40///3", "25+15*2", "10/2+8", "6*4-5/2", "20%3+7*2", "15+9/3%2", "4*5+12%3", "8+6%3*4",
        "9*7/3-4", "11%4-8/2", "13/3%2*6", "17*3%5-2", "12/4+9*2", "14%3-5*2", "8/2+7*3", "11%4-6/2", "20*3%4-7", "15/5+8%2", "14*2%5-3", "9/3+6*2",
        "18%4-7/2", "25+15%3*2", "10*2%3+8", "6*4%2-5/2", "20%3*2+7", "15%3+9/2*2", "4*5%2+12", "8+6/3%4*4", "9*7%3-4/2", "11%4+8/2-1", "13/3%2*6+1",
        "17*3%5-2+3", "12/4+9*2+2", "14%3-5*2+4", "8/2+7*3+1", "11%4-6/2+2", "20*3%4-7+1", "15/5+8%2+3", "14*2%5-3+4", "9/3+6*2+1", "18%4-7/2+2", "25+15%3*2+3",
        "10*2%3+8+1", "6*4%2-5/2+2", "20%3*2+7+3", "15%3+9/2*2+1", "4*5%2+12+2", "8+6/3%4*4+1", "9*7%3-4/2+3", "11%4+8/2-1+2", "13/3%2*6+1+3", "17*3%5-2+3+4",
        "12/4+9*2+2+1", "14%3-5*2+4+2", "8/2+7*3+1+3", "11%4-6/2+2+4", "20*3%4-7+1+1", "15/5+8%2+3+2", "14*2%5-3+4+1", "9/3+6*2+1+2", "18%4-7/2+2+3", "25+15%3*2+3+1",
        "10*2%3+8+1+2", "6*4%2-5/2+2+3", "20%3*2+7+3+4", "15%3+9/2*2+1+1", "4*5%2+12+2+2", "8+6/3%4*4+1+3", "9*7%3-4/2+3+1", "11%4+8/2-1+2+2", "13/3%2*6+1+3+3",
        "17*3%5-2+3+4+1", "12/4+9*2+2+1+2", "14%3-5*2+4+2+3", "8/2+7*3+1+3+1", "11%4-6/2+2+4+2", "20*3%4-7+1+1+3", "15/5+8%2+3+2+4", "14*2%5-3+4+1+1", "9/3+6*2+1+2+2",
        "18%4-7/2+2+3+3", "25+15%3*2+3+1+1", "10*2%3+8+1+2+2", "6*4%2-5/2+2+3+3", "20%3*2+7+3+4+1", "15%3+9/2*2+1+1+2", "4*5%2+12+2+2+3", "8+6/3%4*4+1+3+1", "9*7%3-4/2+3+1+2",
        "11%4+8/2-1+2+2+3", "13/3%2*6+1+3+3+4", "17*3%5-2+3+4+1+1", "12/4+9*2+2+1+2+2", "14%3-5*2+4+2+3+3", "8/2+7*3+1+3+1+4", "11%4-6/2+2+4+2+1", "20*3%4-7+1+1+3+2", "15/5+8%2+3+2+4+1",
        "14*2%5-3+4+1+1+2", "9/3+6*2+1+2+2+3", "18%4-7/2+2+3+3+4"
    };





    string test1 = "(2+4)-(3+9)-4%2"; // 
    string test2 = "(1+2)-(4+5)-2%1"; //
    string test3 = "(2+4)-(5+7)-4%2"; //
    string test4 = "(3+6)-(6+9)-6%3"; //
    string test5 = "(4+8)-(7+11)-8%4"; //
    string test6 = "(5+10)-(8+13)-10%5"; //
    string test7 = "(6+12)-(9+15)-12%6"; //
    string test8 = "(7+14)-(10+17)-14%7"; //
    string test9 = "(8+16)-(11+19)-16%8"; //
    string test10 = "(9+18)-(12+21)-18%9"; //
    string test11 = "(10+20)-(13+23)-20%10"; //
    string test12 = "(11+22)-(14+25)-22%11"; //
    string test13 = "(12+24)-(15+27)-24%12"; //
    string test14 = "(13+26)-(16+29)-26%13"; //
    string test15 = "(14+28)-(17+31)-28%14"; //
    string test16 = "(15+30)-(18+33)-30%15"; //
    string test17 = "(16+32)-(19+35)-32%16"; //
    string test18 = "(17+34)-(20+37)-34%17"; //
    string test19 = "(18+36)-(21+39)-36%18"; //
    string test20 = "(19+38)-(22+41)-38%19"; //
    string test21 = "(20+40)-(23+43)-40%20"; //
    string test22 = "(21+42)-(24+45)-42%21"; //
    string test23 = "(22+44)-(25+47)-44%22"; //
    string test24 = "(23+46)-(26+49)-46%23"; //
    string test25 = "(24+48)-(27+51)-48%24"; //
    string test26 = "(25+50)-(28+53)-50%25"; //
    string test27 = "(26+52)-(29+55)-52%26"; //
    string test28 = "(27+54)-(30+57)-54%27"; //
    string test29 = "(28+56)-(31+59)-56%28"; //
    string test30 = "(29+58)-(32+61)-58%29"; //
    string test31 = "(30+60)-(33+63)-60%30"; //
    string test32 = "(31+62)-(34+65)-62%31"; //
    string test33 = "(32+64)-(35+67)-64%32"; //
    string test34 = "(33+66)-(36+69)-66%33"; //
    string test35 = "(34+68)-(37+71)-68%34"; //
    string test36 = "(35+70)-(38+73)-70%35"; //
    string test37 = "(36+72)-(39+75)-72%36"; //
    string test38 = "(37+74)-(40+77)-74%37"; //
    string test39 = "(38+76)-(41+79)-76%38"; //
    string test40 = "(39+78)-(42+81)-78%39"; //
    string test41 = "(40+80)-(43+83)-80%40"; //
    string test42 = "(41+82)-(44+85)-82%41"; //
    string test43 = "(42+84)-(45+87)-84%42"; //
    string test44 = "(43+86)-(46+89)-86%43"; //
    string test45 = "(44+88)-(47+91)-88%44"; //
    string test46 = "(45+90)-(48+93)-90%45"; //
    string test47 = "(46+92)-(49+95)-92%46"; //
    string test48 = "(47+94)-(50+97)-94%47"; //
    string test49 = "(48+96)-(51+99)-96%48"; //
    string test50 = "(49+98)-(52+101)-98%49"; //
    string test51 = "(50+100)-(53+103)-100%50"; //
    string test52 = "(51+102)-(54+105)-102%51"; //
    string test53 = "(52+104)-(55+107)-104%52"; //
    string test54 = "(53+106)-(56+109)-106%53"; //
    string test55 = "(54+108)-(57+111)-108%54"; //
    string test56 = "(55+110)-(58+113)-110%55"; //
    string test57 = "(56+112)-(59+115)-112%56"; //
    string test58 = "(57+114)-(60+117)-114%57"; //
    string test59 = "(58+116)-(61+119)-116%58"; //
    string test60 = "(59+118)-(62+121)-118%59"; //
    string test61 = "(60+120)-(63+123)-120%60"; //
    string test62 = "(61+122)-(64+125)-122%61"; //
    string test63 = "(62+124)-(65+127)-124%62"; //
    string test64 = "(63+126)-(66+129)-126%63"; //
    string test65 = "(64+128)-(67+131)-128%64"; //
    string test66 = "(65+130)-(68+133)-130%65"; //
    string test67 = "(66+132)-(69+135)-132%66"; //
    string test68 = "(67+134)-(70+137)-134%67"; //
    string test69 = "(68+136)-(71+139)-136%68"; //
    string test70 = "(69+138)-(72+141)-138%69"; //
    string test71 = "(70+140)-(73+143)-140%70"; //
    string test72 = "(71+142)-(74+145)-142%71"; //
    string test73 = "(72+144)-(75+147)-144%72"; //
    string test74 = "(73+146)-(76+149)-146%73"; //
    string test75 = "(74+148)-(77+151)-148%74"; //
    string test76 = "(75+150)-(78+153)-150%75"; //
    string test77 = "(76+152)-(79+155)-152%76"; //
    string test78 = "(77+154)-(80+157)-154%77"; //
    string test79 = "(78+156)-(81+159)-156%78"; //
    string test80 = "(79+158)-(82+161)-158%79"; //
    string test81 = "(80+160)-(83+163)-160%80"; //
    string test82 = "(81+162)-(84+165)-162%81"; //
    string test83 = "(82+164)-(85+167)-164%82"; //
    string test84 = "(83+166)-(86+169)-166%83"; //
    string test85 = "(84+168)-(87+171)-168%84"; //
    string test86 = "(85+170)-(88+173)-170%85"; //
    string test87 = "(86+172)-(89+175)-172%86"; //
    string test88 = "(87+174)-(90+177)-174%87"; //
    string test89 = "(88+176)-(91+179)-176%88"; //
    string test90 = "(89+178)-(92+181)-178%89"; //
    string test91 = "(90+180)-(93+183)-180%90"; //
    string test92 = "(91+182)-(94+185)-182%91"; //
    string test93 = "(92+184)-(95+187)-184%92"; //
    string test94 = "(93+186)-(96+189)-186%93"; //
    string test95 = "(94+188)-(97+191)-188%94"; //
    string test96 = "(95+190)-(98+193)-190%95"; //
    string test97 = "(96+192)-(99+195)-192%96"; //
    string test98 = "(97+194)-(100+197)-194%97"; //
    string test99 = "(98+196)-(101+199)-196%98"; //
    string test100 = "(99+198)-(102+201)-198%99"; //
    string test101 = "(100+200)-(103+203)-200%100"; //
    string test102 = "40 + 12"; //
    string test103 = "40///3"; //
    string secondcasetest1 = "25+15*2"; //
    string secondcasetest2 = "10/2+8"; //
    string secondcasetest3 = "6*4-5/2"; //
    string secondcasetest4 = "20%3+7*2"; //
    string secondcasetest5 = "15+9/3%2"; //
    string secondcasetest6 = "4*5+12%3"; //
    string secondcasetest7 = "8+6%3*4"; //
    string secondcasetest8 = "9*7/3-4"; //
    string secondcasetest9 = "11%4-8/2"; //
    string secondcasetest10 = "13/3%2*6"; //
    string secondcasetest11 = "17*3%5-2"; //
    string secondcasetest12 = "12/4+9*2"; //
    string secondcasetest13 = "14%3-5*2"; //
    string secondcasetest14 = "8/2+7*3"; //
    string secondcasetest15 = "11%4-6/2"; //
    string secondcasetest16 = "20*3%4-7"; //
    string secondcasetest17 = "15/5+8%2"; //
    string secondcasetest18 = "14*2%5-3"; //
    string secondcasetest19 = "9/3+6*2"; //
    string secondcasetest20 = "18%4-7/2"; //
    string secondcasetest21 = "25+15%3*2"; //
    string secondcasetest22 = "10*2%3+8"; //
    string secondcasetest23 = "6*4%2-5/2"; //
    string secondcasetest24 = "20%3*2+7"; //
    string secondcasetest25 = "15%3+9/2*2"; //
    string secondcasetest26 = "4*5%2+12"; //
    string secondcasetest27 = "8+6/3%4*4"; //
    string secondcasetest28 = "9*7%3-4/2"; //
    string secondcasetest29 = "11%4+8/2-1"; //
    string secondcasetest30 = "13/3%2*6+1"; //
    string secondcasetest31 = "17*3%5-2+3"; //
    string secondcasetest32 = "12/4+9*2+2"; //
    string secondcasetest33 = "14%3-5*2+4"; //
    string secondcasetest34 = "8/2+7*3+1"; //
    string secondcasetest35 = "11%4-6/2+2"; //
    string secondcasetest36 = "20*3%4-7+1"; //
    string secondcasetest37 = "15/5+8%2+3"; //
    string secondcasetest38 = "14*2%5-3+4"; //
    string secondcasetest39 = "9/3+6*2+1"; //
    string secondcasetest40 = "18%4-7/2+2"; //
    string secondcasetest41 = "25+15%3*2+3"; //
    string secondcasetest42 = "10*2%3+8+1"; //
    string secondcasetest43 = "6*4%2-5/2+2"; //
    string secondcasetest44 = "20%3*2+7+3"; //
    string secondcasetest45 = "15%3+9/2*2+1"; //
    string secondcasetest46 = "4*5%2+12+2"; //
    string secondcasetest47 = "8+6/3%4*4+1"; //
    string secondcasetest48 = "9*7%3-4/2+3"; //
    string secondcasetest49 = "11%4+8/2-1+2"; //
    string secondcasetest50 = "13/3%2*6+1+3"; //
    string secondcasetest51 = "17*3%5-2+3+4"; //
    string secondcasetest52 = "12/4+9*2+2+1"; //
    string secondcasetest53 = "14%3-5*2+4+2"; //
    string secondcasetest54 = "8/2+7*3+1+3"; //
    string secondcasetest55 = "11%4-6/2+2+4"; //
    string secondcasetest56 = "20*3%4-7+1+1"; //
    string secondcasetest57 = "15/5+8%2+3+2"; //
    string secondcasetest58 = "14*2%5-3+4+1"; //
    string secondcasetest59 = "9/3+6*2+1+2"; //
    string secondcasetest60 = "18%4-7/2+2+3"; //
    string secondcasetest61 = "25+15%3*2+3+1"; //
    string secondcasetest62 = "10*2%3+8+1+2"; //
    string secondcasetest63 = "6*4%2-5/2+2+3"; //
    string secondcasetest64 = "20%3*2+7+3+4"; //
    string secondcasetest65 = "15%3+9/2*2+1+1"; //
    string secondcasetest66 = "4*5%2+12+2+2"; //
    string secondcasetest67 = "8+6/3%4*4+1+3"; //
    string secondcasetest68 = "9*7%3-4/2+3+1"; //
    string secondcasetest69 = "11%4+8/2-1+2+2"; //
    string secondcasetest70 = "13/3%2*6+1+3+3"; //
    string secondcasetest71 = "17*3%5-2+3+4+1"; //
    string secondcasetest72 = "12/4+9*2+2+1+2"; //
    string secondcasetest73 = "14%3-5*2+4+2+3"; //
    string secondcasetest74 = "8/2+7*3+1+3+1"; //
    string secondcasetest75 = "11%4-6/2+2+4+2"; //
    string secondcasetest76 = "20*3%4-7+1+1+3"; //
    string secondcasetest77 = "15/5+8%2+3+2+4"; //
    string secondcasetest78 = "14*2%5-3+4+1+1"; //
    string secondcasetest79 = "9/3+6*2+1+2+2"; //
    string secondcasetest80 = "18%4-7/2+2+3+3"; //
    string secondcasetest81 = "25+15%3*2+3+1+1"; //
    string secondcasetest82 = "10*2%3+8+1+2+2"; //
    string secondcasetest83 = "6*4%2-5/2+2+3+3"; //
    string secondcasetest84 = "20%3*2+7+3+4+1"; //
    string secondcasetest85 = "15%3+9/2*2+1+1+2"; //
    string secondcasetest86 = "4*5%2+12+2+2+3"; //
    string secondcasetest87 = "8+6/3%4*4+1+3+1"; //
    string secondcasetest88 = "9*7%3-4/2+3+1+2"; //
    string secondcasetest89 = "11%4+8/2-1+2+2+3"; //
    string secondcasetest90 = "13/3%2*6+1+3+3+4"; //
    string secondcasetest91 = "17*3%5-2+3+4+1+1"; //
    string secondcasetest92 = "12/4+9*2+2+1+2+2"; //
    string secondcasetest93 = "14%3-5*2+4+2+3+3"; //
    string secondcasetest94 = "8/2+7*3+1+3+1+4"; //
    string secondcasetest95 = "11%4-6/2+2+4+2+1"; //
    string secondcasetest96 = "20*3%4-7+1+1+3+2"; //
    string secondcasetest97 = "15/5+8%2+3+2+4+1"; //
    string secondcasetest98 = "14*2%5-3+4+1+1+2"; //
    string secondcasetest99 = "9/3+6*2+1+2+2+3"; //
    string secondcasetest100 = "18%4-7/2+2+3+3+4"; //






}

int main(){
    // could we start adding references to code instead of passing the copy through so that our code is more efficient? This is the difference between lower level vs higher level thinking.
    gatherInfo();
    return 0;
}